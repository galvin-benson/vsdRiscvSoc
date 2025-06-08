.section .text
.global _start
_start:
    la sp, stack_top        # Set stack pointer to top of stack
    call main               # Call main()
    j .                     # Infinite loop if main returns
