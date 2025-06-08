volatile int lock = 0;  // 0 = unlocked, 1 = locked

// Try to acquire lock (spinlock)
void acquire_lock(volatile int *lock_addr) {
    int result;
    do {
        // Load Reserved + Store Conditional sequence in inline asm
        asm volatile (
            "lr.w %[tmp], (%[addr]) \n"      // Load reserved
            "bnez %[tmp], 1f \n"             // If lock != 0, busy wait (skip store)
            "li %[tmp], 1 \n"                // Prepare 1 to store (locked)
            "sc.w %[result], %[tmp], (%[addr]) \n" // Store conditional
            "1: \n"
            : [result] "=&r" (result), [tmp] "=&r" (result)
            : [addr] "r" (lock_addr)
            : "memory"
        );
    } while (result != 0);  // Loop if store conditional failed
}

// Release the lock
void release_lock(volatile int *lock_addr) {
    *lock_addr = 0;  // Unlock by setting to 0
}

// Pseudo thread 1
void thread1() {
    acquire_lock(&lock);
    // Critical section start
    // ... do some work ...
    release_lock(&lock);
}

// Pseudo thread 2
void thread2() {
    acquire_lock(&lock);
    // Critical section start
    // ... do some work ...
    release_lock(&lock);
}

int main() {
    while (1) {
        thread1();
        thread2();
    }
    return 0;
}
