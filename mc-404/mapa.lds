SECTIONS {
  . = 0x00000000;
  .text : { * (.text); }
  . = 00010000;
  .data : { * (.data); }
}