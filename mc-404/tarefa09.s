@@ Tarefa 08
@@ William Gonçalves da Cruz, 188671

  .global _start

  .set IRQ, 0x6
  .set FIQ, 0x7
  .set STACK, 0x80000               @ Posição inicial da pilha
  .set INTERVAL, 1000               @ Intervalo da interrupção de timer

  .org IRQ*4
  b stop_button_press               @ Configura as interupções

stop_button_press:
  movs pc, lr

_start:
  mov r0, #0x12                     @ IRQ Mode
  msr cpsr, r0
  mov sp, #0x72000                  @ Configura pilha modo IRQ

  mov r0, #0x11                     @ FIQ mode
  msr cpsr, r0
  mov sp, #0x70000                  @ Configura pilha modo FIQ

  mov r0, #0x10
  bic r0, r0, #(IRQ)                @ Habilita interrupções
  msr cpsr,r0                       @ Move processador para modo usuário
  mov sp, #STACK                    @ Inicializa a pilha

  @ Teste escrever cadeia
  mov r0, #STDOUT
  ldr r1, =test
  mov r2, #3
  mov r7, #WRITE_FLAG
  swi #0x55

  mov r0, #0                @ status -> 0
  mov r7, #1                @ exit is syscall #1
  swi #0x55                 @ invoke syscall

digits:
  .byte 0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B,0x0

test:
  .byte 0x41,0x42,0x43

.equ STDOUT, 1
.equ WRITE_FLAG, 4                  @ Flags para configurar saída no console

.equ FIRST_STOP_ARRIVAL,  0xa00001
.equ SECOND_STOP_ARRIVAL, 0xa00003
.equ THIRD_STOP_ARRIVAL,  0xa00005  @ Botões que indicam as paradas do trajeto
