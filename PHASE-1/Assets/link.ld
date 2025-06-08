SECTIONS
{
  .text 0x00000000 : 
  {
    *(.text*)       /* All .text sections from all input files */
  }

  .data 0x10000000 :
  {
    *(.data*)       /* All .data sections */
  }

  .bss (NOLOAD) :
  {
    *(.bss*)
  }
}
