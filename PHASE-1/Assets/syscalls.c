#define UART0_ADDR 0x10000000UL

int _write(int fd, char *buf, int len) {
    volatile char *uart = (char *)UART0_ADDR;
    for (int i = 0; i < len; i++) {
        uart[0] = buf[i];
    }
    return len;
}

void* _sbrk(int incr) {
    extern char _end;
    static char *heap_end = &_end;
    char *prev_heap_end = heap_end;
    heap_end += incr;
    return (void *)prev_heap_end;
}

// Minimal syscall stubs for newlib bare-metal

int _close(int file) { return -1; }
int _fstat(int file, void *st) { return 0; }
int _isatty(int file) { return 1; }
int _lseek(int file, int ptr, int dir) { return 0; }
int _read(int file, char *ptr, int len) { return 0; }

int _kill(int pid, int sig) {
    return -1;
}

int _getpid(void) {
    return 1;
}

void _exit(int status) {
    while(1) { }
}
