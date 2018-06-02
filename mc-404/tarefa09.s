@@ Tarefa 09
@@ William Gonçalves da Cruz, 188671

  .global _start

  .set IRQ, 0x6
  .set FIQ, 0x7
  .set STACK, 0x80000               @ Posição inicial da pilha
  .set INTERVAL, 1000               @ Intervalo da interrupção de timer

  .org IRQ*4
  b stop_button_press               @ Configura as interupções

stop_button_press:
  mov r10, #0x66
  movs pc, lr

msg_size:                           @ Descobre o tamanho da mensagem cujo endreço inicial está em r1
  push { r0, r1 }
  mov r2, #0                        @ Inicializa o contador de tamanho

msg_size_loop:
  ldrb r0, [r1]
  cmp r0, #0x0                      @ Carrega o char atual, caso seja nulo (0x0), termina o loop
  addne r2, #1                      @ Caso contrário, soma 1 ao tamanho e continua
  addne r1, #1
  bne msg_size_loop

  pop { r0, r1 }
  bx lr

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

nana:
  ldr r0, =FIRST_STOP_ARRIVAL
  ldr r0, [r0]
  cmp r0, #1
  bne nana                          @ Exemplo de como ler botão sem interrupção

  @ Teste escrever cadeia
  ldr r0, =STDOUT
  ldr r1, =request_stop_msg
  ldr r7, =WRITE_FLAG
  bl msg_size
  swi #0x55

end:
  b end

  mov r0, #0
  mov r7, #1
  swi #0x55                         @ Finaliza o programa

digits:
  .byte 0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B,0x0

next_stop_msg:                      @ "Proxima parada"
  .byte 0x50, 0x72, 0x6F, 0x78, 0x69, 0x6D, 0x61, 0x20, 0x70, 0x61, 0x72, 0x61, 0x64, 0x61, 0x0

request_stop_msg:                   @ "Parada solicitada"
  .byte 0x50, 0x61, 0x72, 0x61, 0x64, 0x61, 0x20, 0x73, 0x6F, 0x6C, 0x69, 0x6C, 0x63, 0x74, 0x61, 0x64, 0x61, 0x0

on_ride_state: .skip 1              @ Estado para saber se está em trânsito ou não

.equ STDOUT, 1
.equ WRITE_FLAG, 4                  @ Flags para configurar saída no console

.equ STOPPED,   0x01
.equ ON_TRAVEL, 0x02                @ Estados para

.equ FIRST_STOP_ARRIVAL,  0xa0001
.equ SECOND_STOP_ARRIVAL, 0xa0003
.equ THIRD_STOP_ARRIVAL,  0xa0005   @ Botões que indicam as paradas do trajeto
