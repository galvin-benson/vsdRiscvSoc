<details>
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
