<details>
    <summary><h3>Prerequisite</h3></summary>

### Synopsys VCS & Design Compiler available and its PATH

```plaintext
$ which vcs
$ which dc_shell
```
<img width="397" alt="Screenshot 2025-06-13 at 10 15 09 AM" src="https://github.com/user-attachments/assets/d85eed37-3976-4c3c-a646-ae202ebdec3a" />


### The vsdRiscvScl180 project cloned locally

```plaintext
$ git clone https://github.com/vsdip/vsdRiscvScl180.git
$ cd vsdRiscvScl180
$ ls
```
<img width="625" alt="Screenshot 2025-06-13 at 10 15 47 AM" src="https://github.com/user-attachments/assets/526f705b-e5f8-4e0b-a6a5-21e20460b2d0" />

</details>
<details>
    <summary><h3>Task:1 Update My Working Copy</h3></summary>

<img width="721" alt="Screenshot 2025-06-13 at 10 28 49 AM" src="https://github.com/user-attachments/assets/28e0c25a-e31b-4f61-a162-efa756cbc98e" />

</details>
<details>
    <summary><h3>Task:2 Top-Level Orientation</h3></summary>
    
### Four major sub-modules instantiated inside caravel.v

- `chip_io padframe`
- `caravel_core chip_core`
- `include "copyright_block.v"`
- `include "caravel_logo.v"`
### Signals that cross the “Management Protect” boundary

- `mprj_io`
- `mprj_ena`
- `user_irq`
- `mprj_wb_host`

### First reset/clock synchroniser

<b>From `caravel.v`, the reset and clock (`clk, resetb`) are passed into `caravel_core`.</b>

So inside `caravel_core.v`:
- Clock goes into `clocking`
- Reset may go through a synchronizer chain (`reset_sync` module)

<b>`caravel_clocking.v` :</b>

<img width="705" alt="Screenshot 2025-06-13 at 10 42 46 AM" src="https://github.com/user-attachments/assets/eb7bc8c3-829d-404c-89ae-66b3bf5b3dab" />

</details>
<details>
    <summary><h3>Task:3 Generate a Module Hierarchy (Automated)</h3></summary>
</details>
