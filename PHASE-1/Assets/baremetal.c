volatile unsigned int *const UART0 = (unsigned int *)0x10000000;

void put_char(char c) {
    *UART0 = c;
}

void put_string(const char *s) {
    while (*s) {
        put_char(*s++);
    }
}

void _start() {
    put_string("Hello from bare-metal RISC-V on QEMU virt!\n");

    // Hang forever
    while (1) {}
}
