@@ Tarefa 08
@@ William Gonçalves da Cruz, 188671

  .global _start

  .set IRQ, 0x6
  .set FIQ, 0x7

  .org IRQ*4
  b button_press
  b timer_tick                      @ Configura as interupções

_start:

  mov r0, #0                        @ status -> 0
  mov r7, #1                        @ exit is syscall #1
  swi #0x55                         @ invoke syscall


  .align 2
button_press:

  movs pc, lr

  .align 2
timer_tick:

  movs pc, lr

digits:
  .0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B,0x77,0x1F,0x4E,0x3D,0x4F,0x47

.set LEDS, 0x090000                 @ Endereço para os LEDS
.set UNIT_DIGIT, 0xa0000            @ Endereço do dígito das unidades

.set KEYBOARD_DATA, 0xb0001
.set KEYBOARD_STATE, 0xb0000        @ Dados teclado

.set TIMER, 0xc0000                 @ Endereço timer
.set BUTTON, 0xd0000                @ Endereço botão