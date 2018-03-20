@@ Tarefa 00
@@ William Gonçalves da Cruz, 188671

  .org 0x100 @ go to 0x100 to reserve space for 3 variables of 4 bytes in 0x100, 0x104, 0x108
init:
  first: .skip 4
  second: .skip 4
  third: .skip 4

  .org 0x200 @ Move to program acessible position

  set r0, 0x1000 @ init r0 for all sums

sums:
  @ Add to r0 the values of all variables, using r1 as auxiliar
  ld  r1, first
  add r0, r1

  ld  r1, second
  add r0, r1

  ld  r1, third
  add r0, r1

  hlt
