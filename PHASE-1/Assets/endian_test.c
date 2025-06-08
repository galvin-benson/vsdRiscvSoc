#include <stdio.h>
#include <stdint.h>

int main() {
    union {
        uint32_t value;
        uint8_t bytes[4];
    } test;

    test.value = 0x01020304;

    printf("Byte 0: 0x%02x\n", test.bytes[0]);
    printf("Byte 1: 0x%02x\n", test.bytes[1]);
    printf("Byte 2: 0x%02x\n", test.bytes[2]);
    printf("Byte 3: 0x%02x\n", test.bytes[3]);

    while (1);
    return 0;
}
