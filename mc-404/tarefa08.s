@@ Tarefa 08
@@ William Gonçalves da Cruz, 188671

  .global _start

  .set IRQ, 0x6
  .set FIQ, 0x7
  .set STACK, 0x8000000             @ Posição inicial da pilha

  .org IRQ*4
  b button_press
  b timer_tick                      @ Configura as interupções

read_keyboard:
  mov r1, #KEYBOARD_STATE
  ldr r1, [r1]
  cmp r1, #0
  beq read_keyboard                 @ Espera um clique do teclado acontecer

  mov r1, #KEYBOARD_DATA            @ Devolve em r1 o valor digitado
  ldr r1, [r1]
  bx lr                             @ Retorna do procedimento

  .align 2
button_press:
  movs pc, lr

  .align 2
timer_tick:
  movs pc, lr

_start:
  mov sp, #STACK                    @ Inicializa a pilha

  bl read_keyboard

  mov r0, #digits
  ldrb r0, [r0, r1]

  mov r1, #UNIT_DIGIT
  str r0, [r1]

  mov r0, #0                        @ status -> 0
  mov r7, #1                        @ exit is syscall #1
  swi #0x55                         @ invoke syscall

digits:
  .byte 0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B

.equ RED, 0x02
.equ GREEN, 0x01                    @ Cores para os leds

.equ LEDS, 0x090000                 @ Endereço para os LEDS
.equ UNIT_DIGIT, 0xa0000            @ Endereço do dígito das unidades

.equ KEYBOARD_DATA, 0xb0001
.equ KEYBOARD_STATE, 0xb0000        @ Dados teclado

.equ TIMER, 0xc0000                 @ Endereço timer
.equ BUTTON, 0xd0000                @ Endereço botão
