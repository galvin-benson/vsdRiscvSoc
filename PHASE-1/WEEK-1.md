<details>
    <summary><h3>Task:1 Setup/Install & Sanity-Check of RISCV toolchain</h3></summary>

### Extraction of the toolchain

```plaintext
$ tar -xzf riscv-toolchain-rv32imac-aarch64-2025-02-27.tar.gz
```
  
![image](https://github.com/user-attachments/assets/ce30157a-4a39-4574-80df-b674314f8d67)

![image](https://github.com/user-attachments/assets/5a7f5595-db06-48ae-bce2-1955123ab8f4)

### Adding the path to avoid calling it by full directory path every time

```plaintext
$ echo 'export PATH=/opt/riscv/bin:$PATH' >> ~/.zshrc
$ source ~/.zshrc
```

![image](https://github.com/user-attachments/assets/ffad5d86-e5ed-4280-9c62-d651ac65d3e5)

### Verification Commands to check the installed tools

```plaintext
$ riscv32-unknown-elf-gcc --version
$ riscv32-unknown-elf-objdump --version
$ riscv32-unknown-elf-gdb --version
```

![image](https://github.com/user-attachments/assets/99c60cae-404c-4224-aabc-330e38aa9f75)
</details>
<details>
<summary><h3>Task:2 Compile “Hello, RISC-V”</h3></summary>

### Create a new C file and write a basic code for compilation

```plaintext
$ nano hello.c
```
👉 [`hello.c`](https://github.com/galvin-benson/vsdRiscvSoc/blob/main/PHASE-1/Assets/hello.c)

![image](https://github.com/user-attachments/assets/abdaa2bc-7f55-4369-b0a0-7d87ec3537bb)

### Compilation of the C code using RISC-V compiler

```plaintext
$ riscv32-unknown-elf-gcc -o hello_riscv.elf hello.c
$ spike --isa=rv32imac /opt/riscv/riscv32-unknown-elf/bin/pk  hello_riscv.elf
```

![image](https://github.com/user-attachments/assets/e0aa8571-48cb-4332-a289-80f686763a61)

• Run riscv32-unknown-elf-gcc -march=rv32imc -mabi=ilp32 -o hello.elf hello.c.<br>
• Use file hello.elf to confirm it’s 32-bit RISC-V.
![image](https://github.com/user-attachments/assets/2424cdb5-5610-4e3f-aa1d-3f788570173c)
</details>
<details>
<summary><h3>Task:3 From C to Assembly</h3></summary>

### Generate a .s file (assembly code) from the C code and Open it

```plaintext
$ riscv32-unknown-elf-gcc -S -O0 hello.c
$ nano hello.s
```

![image](https://github.com/user-attachments/assets/f43e2219-66bd-4f47-9d90-09891f2b88f5)

• Basic Tabulation of the keywords

<img width="793" alt="Screenshot 2025-06-06 at 11 22 58 PM" src="https://github.com/user-attachments/assets/394648fa-3132-460f-8d12-1ce09f21c07c" />

</details>
<details>
<summary><h3>Task:4 Hex Dump & Disassembly</h3></summary>

### Disassembly of the RISC-V ELF file and generate a hex dump.

```plaintext
$ riscv32-unknown-elf-objdump -d hello_riscv.elf > hello.dump
$ nano hello.dump
```
![image](https://github.com/user-attachments/assets/4be5696e-d828-4aea-860a-6a00280753c1)

### Use objcopy to convert the ELF file into Intel HEX format

```plaintext
$ riscv32-unknown-elf-objcopy -O ihex hello_riscv.elf hello.hex
$ nano hello.hex
```
• This generates a hex file useful for flashing into memory
![image](https://github.com/user-attachments/assets/2966a49b-2a1e-4338-a02d-8171266eb946)

</details>

<details>
<summary><h3>Task:5 ABI & Register Cheat-Sheet </h3></summary>

• Understanding and Listing of all 32 general-purpose registers in RV32, their ABI names, and their roles in the calling convention.

| Register | ABI Name | Typical Role                      |
|----------|----------|---------------------------------|
| x0       | zero     | Hard-wired zero (always 0)      |
| x1       | ra       | Return address                  |
| x2       | sp       | Stack pointer                  |
| x3       | gp       | Global pointer                 |
| x4       | tp       | Thread pointer                 |
| x5–x7       | t0–t2       | Temporary / caller-saved       |
| x8       | s0/fp    | Saved register / frame pointer |
| x9       | s1       | Saved register                 |
| x10-x11      | a0–a1       | Function argument / return     |
| x12–x17      | a2–a7       | Function argument              |
| x18–x27      | s2–s11       | Saved register                 |
| x28–x31      | t3–t6       | Temporary / caller-saved       |

### RISC-V Calling Convention Summary

| **Category**        | **Registers**                   | **Saved By**        | **Purpose**                                |
|---------------------|----------------------------------|----------------------|---------------------------------------------|
| Return address    | `ra (x1)`                        | Caller               | Where to return after function call         |
| Arguments         | `a0–a7 (x10–x17)`                | Caller               | Function parameters / return values         |
| Temporaries      | `t0–t6 (x5–x7, x28–x31)`         | Caller               | Scratch registers for temporary use         |
| Saved registers   | `s0–s11 (x8–x9, x18–x27)`        | Callee               | Preserved across function calls             |
| Stack pointer     | `sp (x2)`                        | Callee (indirect)    | Points to the top of the stack              |

</details>
<details>
<summary><h3>Task:6 Stepping with GDB </h3></summary>

### QEMU Set-up

• This will install qemu-system-riscv32 along with other miscellaneous QEMU system emulators.

```plaintext
$ sudo apt update
$ sudo apt install qemu-system-misc
```
• After Installation run, 
```plaintext
$ qemu-system-riscv32 -nographic -machine sifive_e -kernel hello_riscv.elf -S -gdb tcp::1234
```
• This will start QEMU in paused mode, waiting for GDB.<br>
• Then in another terminal, run:
```plaintext
$ riscv32-unknown-elf-gdb hello_riscv.elf
```

![image](https://github.com/user-attachments/assets/de08fa57-6983-4cfb-a6a0-1b86fa08e936)

• Then Inside **GDB**:
```plaintext
target remote :1234
break main
continue
info registers
disassemble
stepi
quit
```

![image](https://github.com/user-attachments/assets/98d11dd5-8e5b-46c4-9984-864c9c81e263)
![image](https://github.com/user-attachments/assets/d14da19f-e838-4099-9cf8-b4413e8c101c)

</details>
<details>
<summary><h3>Task:7 Running Under an Emulator </h3></summary>

### Create and Run a bare-metal RISC-V ELF program using an emulator (Spike or QEMU)

![image](https://github.com/user-attachments/assets/c6edb6a9-5350-4a77-b21a-c7244993d5fe)

### Compile the C program (baremetal.c) with the linker script (linker.ld) and include debug info:
👉 [`baremetal.c`](https://github.com/galvin-benson/vsdRiscvSoc/blob/main/PHASE-1/Assets/baremetal.c)  👉 [`linker.ld`](https://github.com/galvin-benson/vsdRiscvSoc/blob/main/PHASE-1/Assets/linker.ld)
```plaintext
$ riscv32-unknown-elf-gcc -g -nostdlib -nostartfiles -T linker.ld -o baremetal.elf baremetal.c
```
### Use QEMU's RISC-V system emulator to run the ELF program
```plaintext
$ qemu-system-riscv32 -nographic -machine sifive_e -kernel baremetal.elf
```
### Debugging using GDB with QEMU
```plaintext
$ qemu-system-riscv32 -nographic -machine sifive_e -kernel baremetal.elf -S -gdb tcp::1234
```
• This will start QEMU in paused mode, waiting for GDB. <br>
• Then in another terminal, run:
```plaintext
$ riscv32-unknown-elf-gdb baremetal.elf
```
• Then Inside **GDB**:
```plaintext
target remote :1234
info registers
disassemble _start
quit
```
![image](https://github.com/user-attachments/assets/71763faa-18e2-476f-9ccb-643509dae046)
![image](https://github.com/user-attachments/assets/91c09f34-d1a7-44b8-adef-8c84a473e539)

</details>
<details>
<summary><h3>Task:8 Exploring GCC Optimisation </h3></summary>

Comparing two compiler optimization levels to observe how GCC optimizations affect assembly output:  
- `-O0` (no optimization)  
- `-O2` (aggressive optimizations)

👉 [`sum1ton.c`](https://github.com/galvin-benson/vsdRiscvSoc/blob/main/PHASE-1/Assets/sum1ton.c) 

![image](https://github.com/user-attachments/assets/05ec5ad9-502b-4964-bd7c-2d2f25b90608)

Compile to assembly with no optimization(-O0):
```plaintext
$ riscv32-unknown-elf-gcc -march=rv32imac -mabi=ilp32 -O0 -S -o sum1ton_O0.s sum1ton.c
```
Compile to assembly with high optimization(-O2):
```plaintext
$ riscv32-unknown-elf-gcc -march=rv32imac -mabi=ilp32 -O2 -S -o sum1ton_O2.s sum1ton.c
```
Compare the Output codes:
```plaintext
$ diff sum1ton_O0.s sum1ton_O2.s
```
![image](https://github.com/user-attachments/assets/3ed27748-36f7-4eb9-9a2f-7fe312b81eda)

### Explanation of Key Differences
| Feature               | `-O0` (Debug Build)                 | `-O2` (Optimized Build)                  | Why it Matters                                                               |
| --------------------- | ----------------------------------- | ---------------------------------------- | ---------------------------------------------------------------------------- |
| **.rodata**           | `.rodata`                           | `.rodata.str1.4`                         | Optimized version uses string section with alignment for better performance. |
| **.text**             | `.text`                             | `.text.startup`                          | Tells linker this is startup code (may be placed early in binary).           |
| **Loop logic**        | Explicit `i=0; i<n; i++` in full    | May use tight loop, registers only       | Saves cycles by avoiding stack.                                              |
| **Variables**         | `sum`, `i`, `n` all stored in stack | Some in registers, some constants folded | Compiler avoids unnecessary memory use.                                      |
| **Printf args**       | Built during runtime                | May precompute and pass directly         | Less runtime work.                                                           |
| **Instruction Count** | Higher                              | Lower                                    | Optimized for speed and size.                                                |

### `-O2` Optimized:
| Optimization              | What it Does                                           | Effect                |
| ------------------------- | ------------------------------------------------------ | --------------------- |
| **Dead Code Elimination** | Removes unused variables or logic                      | Smaller binary        |
| **Register Allocation**   | Keeps variables in CPU registers instead of RAM        | Faster access         |
| **Instruction Combining** | Combines multiple C statements into fewer instructions | Performance boost     |
| **Loop Optimization**     | Simplifies or unrolls loops                            | Speeds up iteration   |
| **Inlining Functions**    | Calls to small functions are replaced with their body  | Removes call overhead |

</details>
<details>
<summary><h3>Task:9 Inline Assembly Basics </h3></summary>

Function in C that returns the current value of the RISC-V cycle counter by accessing CSR register 0xC00 using inline assembly.
<br>
👉 [`rdcycle.c`](https://github.com/galvin-benson/vsdRiscvSoc/blob/main/PHASE-1/Assets/rdcycle.c)

![image](https://github.com/user-attachments/assets/9a90d703-8379-49d6-bf79-c12804b53c5a)

### => static inline uint32_t rdcycle(void)

`static inline`: Suggests inlining the function — avoids function call overhead.<br>
`uint32_t`: 32-bit return value, matches the CSR data width on RV32.

### => asm volatile ("csrr %0, cycle" : "=r"(c));

<h3>Breaking Down: csrr %0, cycle </h3>

`csrr`: Reads from a CSR (Control and Status Register).<br>
`cycle`: CSR number 0xC00 – holds the number of cycles executed.
`%0`: Placeholder for the output register (filled by GCC).

<h3> =r"(c) – Operand Constraint</h3>

| Part   | Meaning                                                          |
| ------ | ---------------------------------------------------------------- |
| `"=r"` | `"="` → it's an output; `"r"` → use any general-purpose register |
| `(c)`  | Output value is stored in C variable `c`                         |

</details>
<details>
<summary><h3>Task:10 Memory-Mapped I/O Demo </h3></summary>

### Bare-metal C snippet to toggle a GPIO register located at 0x10012000
👉 [`gpio.c`](https://github.com/galvin-benson/vsdRiscvSoc/blob/main/PHASE-1/Assets/gpio.c)

![image](https://github.com/user-attachments/assets/872d7e5a-41aa-4675-806f-60e81bf09b1d)

### Explanation:
- `volatile`<br>
Tells the compiler not to optimize away this access, even if it looks unused.<br>

- Memory-Mapped I/O<br>
`0x10012000` is assumed to be the base address of a GPIO register.<br>
Writing to it sends data directly to hardware.<br>

- `uint32_t` ensures 4-byte alignment (32-bit wide register).<br>
Mismatched types (like `uint8_t*` or `uint64_t*`) could lead to:<br>
Unaligned access, Wrong register write, Unexpected hardware behavior

| Element       | Purpose                                    |
| ------------- | ------------------------------------------ |
| `volatile`    | Prevent compiler from optimizing the write |
| `uint32_t*`   | Ensures proper 32-bit aligned access       |
| `0x10012000`  | Example GPIO memory-mapped address         |
| `*gpio = 0x1` | Writes a value to hardware directly        |

</details>
<details>
<summary><h3>Task:11 Linker Script 101 </h3></summary>

### Create a minimal linker script that places:
- text section at address 0x00000000
  - This is where Flash memory starts.
  - Flash is non-volatile, so instructions (program code) are stored here to persist after reset.
- data section at address 0x10000000
  - This is usually the start of SRAM in many microcontrollers.
  - SRAM is volatile, so it's used for variables that your program will read/write during execution.<br>
  
For the RV32IMC RISC-V target (bare-metal, no OS).

👉 [`link.ld`](https://github.com/galvin-benson/vsdRiscvSoc/blob/main/PHASE-1/Assets/link.ld)

![image](https://github.com/user-attachments/assets/a8a577e2-e61a-43b0-a4d4-a9e75bb2b401)

Compile with the Custom Linker Script:
```plaintext
$ riscv32-unknown-elf-gcc -nostdlib -march=rv32imac -mabi=ilp32 -T link.ld -o baremetal.elf baremetal.c
```
Then inspect the result:
```plaintext
$ riscv32-unknown-elf-objdump -d baremetal.elf
$ riscv32-unknown-elf-readelf -S baremetal.elf
```
![image](https://github.com/user-attachments/assets/4d871315-9e57-4479-ad65-c75acaf667e0)
![image](https://github.com/user-attachments/assets/f8a3d970-21b8-4190-9af7-d0d6a231533c)

| Feature               | **Flash Memory**                                 | **SRAM (Static RAM)**                                       |
| --------------------- | ------------------------------------------------ | ----------------------------------------------------------- |
| **Used For**          | Storing program code (`.text`)                   | Storing variables at runtime (`.data`, `.bss`, stack, heap) |
| **Volatility**        | ❌ Non-volatile                                   | ✅ Volatile                                                  |
| **Access**            | Read-only (during normal execution)              | Read-write                                                  |
| **Speed**             | Slower than SRAM                                 | Faster access                                               |
| **Typical Address**   | `0x00000000` (low memory region)                 | `0x10000000` or `0x80000000` (higher memory)                |
| **Persistence**       | Retains contents after power off                 | Loses contents when power is off                            |
| **Why This Address?** | Start address for processor reset (reset vector) | Mapped separately by memory controller                      |
| **Physical Memory**   | Separate chip or flash section                   | Separate physical SRAM                                      |


</details>
<details>
<summary><h3>Task:12 Start-up Code & crt0 </h3></summary>

### What is `crt0.S`?
- `crt0.S` (also called "C runtime zero") is a startup assembly file that runs before main() in any C program on bare-metal systems (like embedded RISC-V). It’s the first code executed after a system reset or power-on.

### What does `crt0.S` do in a bare-metal RISC-V program?
| Step | Purpose                                  | Description                                                                                          |
| ---- | ---------------------------------------- | ---------------------------------------------------------------------------------------------------- |
| 1    | **Set up the Stack Pointer (`sp`)**      | Initializes the `sp` to the top of available RAM so that functions and variables can use the stack.  |
| 2    | **Zero out the `.bss` section**          | `.bss` holds uninitialized global/static variables. This section is cleared to zero (as per C spec). |
| 3    | **Initialize `.data` (optional)**        | If needed, copies initialized variables from Flash to SRAM.                                          |
| 4    | **Call `main()`**                        | Transfers control to the C program's `main()` function.                                              |
| 5    | **Infinite loop after `main()` returns** | Prevents execution from running into garbage memory if `main()` returns (since there's no OS).       |

### Where do I get a `crt0.S` file?
| Source                     | Description                                                                                                                                                 |
| -------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Newlib**                 | Comes with basic startup files for RISC-V, including `crt0.S`. Often used in embedded toolchains.                                                           |
| **Platform-specific SDKs** | E.g., SiFive, ESP32-C3, Kendryte, etc. provide their own `crt0.S` tailored for their chips.                                                                 |
| **Bare-metal examples**    | Projects like [riscv-boilerplate](https://github.com/sifive/freedom-e-sdk) or [RISC-V examples](https://github.com/riscv/riscv-pk) often have startup code. |
| **Write your own**         | You can write a simple one based on your memory map (minimal for simulation/emulators).                                                                     |

</details>
<details>
<summary><h3>Task:13 Interrupt Primer </h3></summary>

### Enable the machine-timer interrupt (MTIP) and write a simple handler in C/assembly.
**Steps to do:**
1. Set `mtime` and `mtimecmp` via CLINT (memory-mapped)
2. Enable MTIE in `mie` CSR
3. Enable MIE in `mstatus` CSR
4. Set `mtvec` to point to your ISR
5. Write a timer ISR using `__attribute__((interrupt))`
6. Add UART prints for visibility in QEMU

👉 [`mtip.c`](https://github.com/galvin-benson/vsdRiscvSoc/blob/main/PHASE-1/Assets/mtip.c) <br>
    
    void __attribute__((interrupt)) timer_handler(void) {
    *mtimecmp = *mtime + 100000;
    interrupt_counter++;
    uart_puts("Timer fired: ");
    uart_putint(interrupt_counter);
    uart_putc('\n');
    }

    write_csr(mtvec, (uint32_t)timer_handler);               // Set trap vector
    write_csr(mie, read_csr(mie) | (1 << 7));                // Enable MTIE
    write_csr(mstatus, read_csr(mstatus) | (1 << 3));        // Enable global interrupts

👉 [`crt0.S`](https://github.com/galvin-benson/vsdRiscvSoc/blob/main/PHASE-1/Assets/crt0.S) <br>

    .section .text
    .globl _start
    _start:
    la sp, stack_top
    call main
    j .

👉 `link.ld`

    SECTIONS {
    . = 0x80000000;
    .text : { *(.text*) }
    .data : { *(.data*) }
    .bss  : { *(.bss*) }
    }

### Build Command
```plaintext
$ riscv32-unknown-elf-gcc -Wall -O2 -ffreestanding -nostdlib -mabi=ilp32 -march=rv32imac \
  -o mtip.elf mtip.c crt0.S -T link.ld
$ qemu-system-riscv32 -nographic -machine virt -bios none -kernel mtip.elf -serial mon:stdio
```

### Why It Matters
| Purpose                  | Benefit                                         |
| ------------------------ | ----------------------------------------------- |
| **Real-time interrupts** | Enables timer-based task scheduling             |
| **OS Development**       | Foundation for context switching and preemption |
| **CSR & Trap Mastery**   | Core skill in low-level embedded systems        |

Expected Output:
    
    Timer fired: 1
    Timer fired: 2
    Timer fired: 3
    ...
    
![image](https://github.com/user-attachments/assets/c962d7ab-387f-4bf5-acc7-7adfc56d58e3)

</details>
<details>
<summary><h3>Task:14 rv32imac vs rv32imc – What’s the “A”? </h3></summary>

The `‘A’` atomic extension enhances the RISC-V ISA with hardware atomic instructions, enabling safe concurrent programming by supporting atomic read-modify-write memory operations. This is critical for modern OS kernels and multithreaded applications.
| Aspect                    | Description                                                                                                    |
| ------------------------- | -------------------------------------------------------------------------------------------------------------- |
| **‘A’ Extension**         | Stands for **Atomic** instructions.                                                                            |
| **Included Instructions** | Adds instructions like:                                                                                        |
|                           | - `lr.w` (Load-Reserved Word)                                                                                  |
|                           | - `sc.w` (Store-Conditional Word)                                                                              |
|                           | - `amoadd.w` (Atomic Memory Operation Add Word)                                                                |
|                           | - and other AMO instructions like `amoswap.w`, `amoxor.w`, `amoand.w`, `amoor.w`, `amomin.w`, `amomax.w`       |
| **Purpose**               | Enables **atomic read-modify-write** operations on memory without interference from other cores or interrupts. |
| **Why Useful?**           | Essential for implementing:                                                                                    |
|                           | - Lock-free data structures (like atomic counters, queues)                                                     |
|                           | - Synchronization primitives (mutexes, spinlocks)                                                              |
|                           | - Operating system kernels and multi-threading support                                                         |
| **Difference**            | `rv32imc` = base + multiply + compressed; `rv32imac` = adds atomic instructions to this set.                   |

### Use Cases:
**Lock-Free Data Structures:**
<br>Implement atomic counters, queues, or stacks where multiple threads or cores can safely update shared data without corrupting it.
<br>
<br>**Synchronization Primitives:**
<br>Build mutexes, spinlocks, semaphores, and other synchronization mechanisms that require safe, exclusive access to shared resources.
<br>
<br>**Operating System Kernels:**
<br>Essential for managing concurrency, scheduling, and interrupt handling in a multi-core environment.
<br>
<br>**Multithreaded Applications:**
<br>Ensures safe communication and coordination between threads without performance-heavy locking.
<br>

## Analogy:

| Instruction                                  | Analogy Explanation                                                                                                                                                                                  |
| -------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **`lr.w` (Load Reserved)**                   | You **reserve a spot** on the whiteboard to write something. It marks your intention to change that spot.                                                                                            |
| **`sc.w` (Store Conditional)**               | You try to **write your message** on that spot, but only succeed **if no one else has changed it since you reserved it**. If someone else wrote there first, your write fails, so you can try again. |
| **`amoadd.w` (Atomic Memory Operation Add)** | You **add a number** to the existing value on the whiteboard **in one uninterruptible step**, ensuring no one else can mess with it while you’re adding.                                             |

</details>
<details>
<summary><h3>Task:15 Atomic Test Program </h3></summary>

### Approach: Spinlock using `lr.w` / `sc.w`
The lock is implemented as a spinlock using RISC-V's `lr.w` (load-reserved) and `sc.w` (store-conditional) instructions.<br>
Only one "pseudo-thread" (loop block in `main`) can enter the critical section at a time, ensuring mutual exclusion.

👉 [`spinlock.c`](https://github.com/galvin-benson/vsdRiscvSoc/blob/main/PHASE-1/Assets/spinlock.c)

![image](https://github.com/user-attachments/assets/10ef1a82-971c-4c3b-aace-c5e850b2b03e)

**Why It Matters**

- Demonstrates the use of atomic primitives (lr.w, sc.w) for mutual exclusion in bare-metal systems.
- Helps understand synchronization and concurrency without OS support.
- Foundation for multi-core safe programming and OS kernel-level locking mechanisms.
- Use UART prints in QEMU or hardware to observe that increments never overlap or skip values.

![image](https://github.com/user-attachments/assets/600898e6-6d3f-4e8f-804d-b4c1f9a6a715)

</details>
<details>
<summary><h3>Task:16 Using Newlib printf Without an OS </h3></summary>

Enable the use of printf() in a bare-metal RISC-V environment by retargeting the _write syscall to send characters to a memory-mapped UART.
<br>

### Essential Components

- Memory-mapped UART address (e.g., `0x10000000`) — where you send chars.
- syscalls.c — implements `_write` and `_sbrk` for minimal libc support.
- link.ld — linker script defining `_end` symbol to mark heap start.
- crt0.S — startup code to set stack pointer and call main.
- main.c — `calls` printf.
- Compile with Newlib libc (`-lc`) and GCC builtins (`-lgcc`) but no OS.

### Code Snippets

👉 [`syscalls.c`](https://github.com/galvin-benson/vsdRiscvSoc/blob/main/PHASE-1/Assets/syscalls.c)

![image](https://github.com/user-attachments/assets/2e5439de-671e-498f-9efe-e3d33f276142)

👉 [`main.c`](https://github.com/galvin-benson/vsdRiscvSoc/blob/main/PHASE-1/Assets/main.c)

![image](https://github.com/user-attachments/assets/09e9d4e9-5bf3-44e5-9230-0a6ac1ac7cf7)

👉 `crt0.S`

![image](https://github.com/user-attachments/assets/412927af-76ca-4f0a-97f4-7479a1d517be)

👉 `link.ld`

![image](https://github.com/user-attachments/assets/d9066233-0615-45dc-be8f-5f0fc132f781)

### Build and run command:
```plaintext
$ riscv32-unknown-elf-gcc -Wall -O2 -ffreestanding -nostdlib   -mabi=ilp32 -march=rv32imac   -o printf.elf main.c syscalls.c crt0.S -T link.ld -lc -lgcc
$ qemu-system-riscv32 -machine virt -nographic   -bios /usr/lib/riscv64-linux-gnu/opensbi/generic/fw_dynamic.bin   -device loader,file=printf.elf,addr=0x80200000   -serial mon:stdio
```
![image](https://github.com/user-attachments/assets/1811a110-c16b-4868-91e7-76c2dd9d414e)

### Expected UART Output

    Hello from printf over UART!

This confirms that printf() is internally using _write(), and it's been redirected to the UART peripheral.
</details>
<details>
<summary><h3>Task:17 Endianness & Struct Packing </h3></summary>

### Is RV32 Little-Endian by Default?
Yes, the RV32 (RISC-V 32-bit) architecture is little-endian by default.
- Little-endian means the least significant byte (LSB) is stored at the lowest memory address.
- So, if you store 0x01020304 (4 bytes), in memory it will be:<br>
    Address+0: 0x04  (LSB)<br>
    Address+1: 0x03<br>
    Address+2: 0x02<br>
    Address+3: 0x01  (MSB)<br>

### Verify Byte Ordering with a Union Trick in C
The classic way is to use a union that lets you store a 32-bit integer but access its individual bytes:

👉 [`endian_test.c`](https://github.com/galvin-benson/vsdRiscvSoc/blob/main/PHASE-1/Assets/endian_test.c)

![image](https://github.com/user-attachments/assets/05a89494-f927-4b05-bc9f-7dd92b91e5db)

👉 `syscalls.c`

![image](https://github.com/user-attachments/assets/fc01980c-e5a8-4b5b-b96f-b7ba1f5a041d)

👉 `crt0.S`

![image](https://github.com/user-attachments/assets/f3be7680-cd56-4e2c-a157-06720167e483)

👉 `link.ld`

![image](https://github.com/user-attachments/assets/6929830d-8903-4af4-a026-07338faff963)

### Compile everything together

```plaintext
$ riscv32-unknown-elf-gcc -o endian_test.elf endian_test.c syscalls.c crt0.S -T link.ld -Wall -O2 -ffreestanding -nostdlib -march=rv32imac -mabi=ilp32 -lgcc
$ qemu-system-riscv32 -machine virt -nographic   -bios /usr/lib/riscv64-linux-gnu/opensbi/generic/fw_dynamic.bin   -kernel endian_test.elf -serial mon:stdio
```

![image](https://github.com/user-attachments/assets/4418fa83-872c-4f58-931a-72d1072b049e)

### Expected output if RV32 is little-endian

    Byte 0: 0x04
    Byte 1: 0x03
    Byte 2: 0x02
    Byte 3: 0x01

**Explanation:**

Little-endian means the least significant byte (LSB) is stored at the lowest memory address.<br>
So 0x01020304 is stored as bytes in memory like this (from low to high address):

| Address | Byte Value (hex) |
| ------- | ---------------- |
| addr    | 0x04 (LSB)       |
| addr+1  | 0x03             |
| addr+2  | 0x02             |
| addr+3  | 0x01 (MSB)       |

If it were big-endian, the output would show the bytes reversed, starting from 0x01 at Byte 0.
<br> <br>
**Summary:** 

union trick reveals the byte order used by the processor by showing the memory layout of the 32-bit integer.
</details>
