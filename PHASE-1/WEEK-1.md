<img width="793" alt="Screenshot 2025-06-06 at 11 22 58 PM" src="https://github.com/user-attachments/assets/cc826d56-86bf-4f37-b1ca-9ca6d04247d6" /><details>
    <summary><h3>Task:1 Setup/Install & Sanity-Check of RISCV toolchain</h3></summary>

### Extraction of the toolchain
  
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
