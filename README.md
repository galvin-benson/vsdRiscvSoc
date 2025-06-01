# vsdRiscvSoc
<details>
  <summary><big><b>Click Me😊</b></big></summary>
  <p>Hiii! I'm Galvin Benson<br>Email ID: galvin.benson@gmail.com<br>GitHub Profile: https://github.com/galvin-benson<br>LinkedIn Profile: www.linkedin.com/in/galvin-benson
</p>
</details>

SoC Labs: End-to-End System-on-Chip Design and Verification with RISC-V and open-source EDA tools. Building a processor from scratch.

<img width="686" alt="Screenshot 2025-06-01 at 11 09 31 PM" src="https://github.com/user-attachments/assets/962be1d5-f35c-418c-86d5-de274dd52047" />
<details>
  <summary><big><b>PHASE-1: </b></big>Validate the existing RISC-V SoC design using Synopsys tools and SCL180 PDK. </summary>
  <details>
    <summary><big><b>WEEK-1: </b></big>Tasks </summary>
    <h3>Task:1 Setup/Install & Sanity-Check of RISCV toolchain</h3>
<p>Extract the toolchain</p>
  
![image](https://github.com/user-attachments/assets/ce30157a-4a39-4574-80df-b674314f8d67)

![image](https://github.com/user-attachments/assets/5a7f5595-db06-48ae-bce2-1955123ab8f4)

<p>Add the path</p>

```plaintext
$ echo 'export PATH=/opt/riscv/bin:$PATH' >> ~/.zshrc
$ source ~/.zshrc
```

![image](https://github.com/user-attachments/assets/ffad5d86-e5ed-4280-9c62-d651ac65d3e5)

<p>Verification Commands</p>

```plaintext
$ riscv32-unknown-elf-gcc --version
$ riscv32-unknown-elf-objdump --version
$ riscv32-unknown-elf-gdb --version
```

![image](https://github.com/user-attachments/assets/99c60cae-404c-4224-aabc-330e38aa9f75)

<h3>Task:2 Compile “Hello, RISC-V”</h3>
<p>Create a new C file and write a basic code for compilation</p>

```plaintext
$ nano hello.c
```

![image](https://github.com/user-attachments/assets/abdaa2bc-7f55-4369-b0a0-7d87ec3537bb)

<p>Compilation of the C code using RISC-V compiler:</p>

```plaintext
$ riscv32-unknown-elf-gcc -o hello_riscv.elf hello.c
$ spike --isa=rv32imac /opt/riscv/riscv32-unknown-elf/bin/pk  sum1ton_riscv.elf
```
![image](https://github.com/user-attachments/assets/e0aa8571-48cb-4332-a289-80f686763a61)

• Run riscv32-unknown-elf-gcc -march=rv32imc -mabi=ilp32 -o hello.elf hello.c.<br>
• Use file hello.elf to confirm it’s 32-bit RISC-V.
![image](https://github.com/user-attachments/assets/2424cdb5-5610-4e3f-aa1d-3f788570173c)

  </details>
</details>
