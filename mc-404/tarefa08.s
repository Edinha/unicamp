@@ Tarefa 08
@@ William Gonçalves da Cruz, 188671

  .global _start

  .set IRQ, 0x6
  .set FIQ, 0x7
  .set STACK, 0x8000                @ Posição inicial da pilha

  .org IRQ*4
  b button_press
  b timer_tick                      @ Configura as interupções

  .align 2
read_keyboard:
  ldr r1, =KEYBOARD_STATE
  ldr r1, [r1]
  cmp r1, #0
  beq read_keyboard                 @ Espera um clique do teclado acontecer

  ldr r1, =KEYBOARD_DATA            @ Devolve em r1 o valor digitado
  ldr r1, [r1]
  bx lr                             @ Retorna do procedimento

write_next_digit:
  ldr r2, =digits
  ldrb r2, [r2, r1]                 @ Salva em r2 o dígito representativo do número teclado

  ldr r0, actual_digit              @ Descobre a casa decimal na qual se deve escrever
  str r2, [r0]                      @ Escreve no mostrador da casa decimal o dígito

  sub r0, #1                        @ Diminue o valor para o mostrador da próxima casa

  ldr r2, =UNIT_DIGIT
  cmp r0, r2                        @ Compara a casa decimal atual com as das unidades
  ldrcc r0, =THOUSAND_DIGIT         @ Caso seja menor, volta para milhares

  ldr r2, =actual_digit
  str r0, [r2]                      @ Salva a próxima casa decimal
  bx lr

reset_display:
  mov r1, #10                       @ Dígito que apaga o display
  mov r9, lr                        @ Guarda o endereço de retorno da função

  bl write_next_digit
  bl write_next_digit
  bl write_next_digit
  bl write_next_digit               @ Escreve o dígito vazio no display 4 vezes para limpá-lo

  mov lr, r9
  bx lr                             @ Retorna da função

disable_previous_keyboard:
  ldr r1, =KEYBOARD_DATA
  ldr r1, [r1]                      @ Desabilita cliques do teclado que vieram antes desse ponto

  bx lr

button_press:
  ldr r8, =safe_state
  ldr r9, =SAFE_CLOSED_WAITING
  strb r9, [r8]                     @ Fecha o cofre no clique do botao

  ldr r8, =LEDS
  ldr r9, =GREEN
  str r9, [r8]                      @ Muda o led para verde, mostrar que espera uma senha

  movs pc, lr

timer_tick:
  movs pc, lr

_start:
  mov sp, #STACK                    @ Inicializa a pilha

  ldr r0, =THOUSAND_DIGIT
  ldr r1, =actual_digit
  str r0, [r1]                      @ Iniciliza a posição de dígito atual do mostrador

  ldr r0, =safe_state
  ldr r1, =SAFE_OPEN
  strb r1, [r0]                     @ Inicializa estado do cofre

  mov r0, #0x10
  bic r0, r0, #(IRQ+FIQ)            @ Habilita interrupções
  msr cpsr,r0                       @ Move processador para modo usuário

waiting_close_safe_loop:
  ldr r1, =SAFE_OPEN
  ldrb r0, safe_state
  cmp r0, r1
  beq waiting_close_safe_loop       @ Continua em loop enquanto o estado do cofre é aberto

  bl disable_previous_keyboard

  ldr r3, =password_save            @ Coloca em r3 a posição para salvar a senha

configure_password_loop:
  bl read_keyboard
  bl write_next_digit               @ Espera e escreve próximo dígito de configuração da senha

  strb r1, [r3], #1                 @ Guarda o valor do dígito de senha atual em password_save

  ldr r4, =THOUSAND_DIGIT
  cmp r0, r4
  bne configure_password_loop       @ Espera a senha ser digitada até resetar novamente para o dígito de milhar (ciclo completo)

  ldr r0, =LEDS
  ldr r1, =RED
  strb r1, [r0]                     @ Entra no estado travado

  @@ TODO change safe_state variable for further compares

  bl reset_display                  @ Reseta o display após configuração da senha

  ldr r3, =password_unblock         @ Coloca em r3 a posição de memória para variável de desbloquear cofre

unlock_safe_loop:
  bl read_keyboard
  bl write_next_digit               @ Espera e escreve próximo dígito de desbloqueio

  strb r1, [r3], #1                 @ Guarda o valor do dígito de senha atual em password_unblock

  ldr r4, =THOUSAND_DIGIT
  cmp r0, r4
  bne unlock_safe_loop              @ Espera a senha ser digitada antes de testar a igualdade

  ldr r1, password_save
  ldr r2, password_unblock          @ Ao final do loop, deve comparar as senhas para desbloquear cofre

  cmp r1, r2
  moveq r10, #0x66                  @ Compara as duas senhas para desviar o fluxo

  mov r0, #0                        @ status -> 0
  mov r7, #1                        @ exit is syscall #1
  swi #0x55                         @ invoke syscall

safe_state: .skip 1                 @ Estado do cofre salvo
actual_digit: .skip 4               @ Próximo display dos dígitos da senha

password_save: .skip 4              @ Variável para salvar a senha
password_unblock: .skip 4           @ Variável para salvar a tentativa de desbloquear o cofre

digits:
  .byte 0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B,0x0

.equ RED, 0x02
.equ GREEN, 0x01                    @ Cores para os leds

.equ LEDS, 0x090000                 @ Endereço para os LEDS

.equ UNIT_DIGIT, 0xa0000            @ Endereço do dígito das unidades
.equ THOUSAND_DIGIT, 0xa0003        @ Endereço do dígito dos milhares

.equ KEYBOARD_DATA, 0xb0001
.equ KEYBOARD_STATE, 0xb0000        @ Dados teclado

.equ TIMER, 0xc0000                 @ Endereço timer
.equ BUTTON, 0xd0000                @ Endereço botão

.equ SAFE_OPEN, 0x00
.equ SAFE_CLOSED_LOCKED, 0x01
.equ SAFE_CLOSED_WAITING, 0x02      @ Estados do cofre para controle de desvios
