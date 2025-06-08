#include <stdint.h>
#include "uart.h"   // Your UART helper header (for uart_puts, etc.)

#define CLINT_BASE      0x2000000
#define MTIMECMP        ((volatile uint64_t*)(CLINT_BASE + 0x4000))
#define MTIME           ((volatile uint64_t*)(CLINT_BASE + 0xBFF8))

volatile int interrupt_counter = 0;

// CSRs access macros
#define write_csr(reg, val) ({ __asm__ volatile ("csrw " #reg ", %0" :: "r"(val)); })
#define read_csr(reg) ({ unsigned int __tmp; __asm__ volatile ("csrr %0, " #reg : "=r"(__tmp)); __tmp; })

// Timer interrupt handler
void __attribute__((interrupt)) timer_handler(void) {
    *MTIMECMP = *MTIME + 100000;  // Schedule next timer interrupt
    interrupt_counter++;
    uart_puts("Timer fired: ");
    uart_putint(interrupt_counter);
    uart_putc('\n');
}

// Main setup
int main() {
    uart_init();  // optional UART init, depends on your UART setup
    uart_puts("Starting MTIP...\n");

    *MTIMECMP = *MTIME + 100000;

    // Enable machine-timer interrupt
    write_csr(mtvec, (uint32_t)timer_handler);           // Set trap vector base
    write_csr(mie, read_csr(mie) | (1 << 7));            // Enable MTIE
    write_csr(mstatus, read_csr(mstatus) | (1 << 3));    // Enable MIE (global)

    while (1);  // Idle loop, interrupts will fire
}
