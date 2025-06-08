#include <stdint.h>

extern int _write(int file, char *ptr, int len);

void print_byte_hex(uint8_t byte) {
    const char hex_chars[] = "0123456789ABCDEF";
    char str[2];
    str[0] = hex_chars[(byte >> 4) & 0xF];
    str[1] = hex_chars[byte & 0xF];
    _write(1, str, 2);
}

void print_str(const char *str) {
    while (*str) {
        _write(1, (char *)str, 1);
        str++;
    }
}

int main() {
    union {
        uint32_t i;
        uint8_t c[4];
    } test = {0x01020304};

    print_str("Byte order: ");
    for (int idx = 0; idx < 4; idx++) {
        print_byte_hex(test.c[idx]);
        print_str(" ");
    }
    print_str("\n");

    while (1) { } // infinite loop

    return 0;
}
