#include <stdio.h>

int main() {
    printf("Hello from printf over UART!\n");
    while(1) {
    asm volatile ("wfi");  // wait-for-interrupt (low power)
}
}
