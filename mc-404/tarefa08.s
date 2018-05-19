@@ Tarefa 08
@@ William Gonçalves da Cruz, 188671

  .global _start

  .set IRQ, 0x6
  .set FIQ, 0x7
  .set STACK, 0x80000               @ Posição inicial da pilha
  .set INTERVAL, 1000               @ Intervalo da interrupção de timer

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
  push { lr }                       @ Guarda o endereço de retorno da função

  ldr r1, =actual_digit
  ldr r0, =THOUSAND_DIGIT
  strb r0, [r1]                     @ Move para a primeira posição do display

  mov r1, #10                       @ Dígito que apaga o display
  bl write_next_digit
  bl write_next_digit
  bl write_next_digit
  bl write_next_digit               @ Escreve o dígito vazio no display 4 vezes para limpá-lo

  pop { lr }
  bx lr                             @ Retorna da função

disable_previous_keyboard:
  ldr r1, =KEYBOARD_DATA
  ldr r1, [r1]                      @ Desabilita cliques do teclado que vieram antes desse ponto

  bx lr

button_press:
  push { r8, r9 }

  ldr r8, =safe_state
  ldr r9, =SAFE_CLOSED_WAITING
  strb r9, [r8]                     @ Fecha o cofre no clique do botao

  pop { r8, r9 }
  movs pc, lr

timer_tick:
  push { r8, r9 }

  ldrb r8, safe_state
  ldr r9, =SAFE_TIMER_WAITING
  cmp r8, r9
  beq timer_tick_reset_display      @ Caso seja o estado de timer para reset de display, desvia o fluxo

  ldr r9, =SAFE_CLOSED_WAITING      @ Caso esteja configurando a senha, espera de tempo demais
  cmp r8, r9
  beq timer_tick_too_long_password

  ldr r9, =SAFE_UNLOCK_FLOW         @ Caso esteja desbloqueando a senha, espera de tempo demais
  cmp r8, r9
  beq timer_tick_too_long_password

  b timer_tick_final                @ Náo faz nada caso não seja nenhum dos casos de timer

timer_tick_too_long_password:
  add r5, #1                        @ Adiciona 1 ao contador de tempo
  cmp r5, #10
  bcc timer_tick_final              @ Caso não tenha chego a 10, não faz nada

  mov r5, #0
  bl reset_display                  @ Reseta o display por completo

  ldr r9, =SAFE_CLOSED_WAITING      @ Caso seja configuração de senha, move para configure_password_process
  cmp r8, r9
  ldreq lr, =configure_password_process

  ldr r9, =SAFE_UNLOCK_FLOW         @ Caso seja desbloqueamento de senha, move para unlock_safe_process
  cmp r8, r9
  ldreq lr, =unlock_safe_process

  b timer_tick_final                @ Move o endereço de retorno para o começo da configuração de senha

timer_tick_reset_display:
  add r5, #1                        @ Adiciona 1 ao contador de tempo
  cmp r5, #5
  bcc timer_tick_final              @ Caso não tenha chego em 5, não faz nada

  mov r5, #0                        @ Caso contrário, chegou ao final de seu timer
  ldr r8, =safe_state
  ldr r9, =SAFE_TIMER_FINISHED
  strb r9, [r8]                     @ Escreve o estado em que o cofre pode avançar, o timer de reset acabou

timer_tick_final:
  pop { r8, r9 }
  movs pc, lr

_start:
  ldr r0, =THOUSAND_DIGIT
  ldr r1, =actual_digit
  str r0, [r1]                      @ Iniciliza a posição de dígito atual do mostrador

  ldr r0, =safe_state
  ldr r1, =SAFE_OPEN
  strb r1, [r0]                     @ Inicializa estado do cofre

  ldr r0, =password_tries
  mov r1, #0
  strb r1, [r0]                     @ Inicializa o contador de senhas erradas

  mov r0, #0x12                     @ IRQ Mode
  msr cpsr, r0
  mov sp, #0x72000                  @ Configura pilha modo IRQ

  mov r0, #0x11                     @ FIQ mode
  msr cpsr, r0
  mov sp, #0x70000                  @ Configura pilha modo FIQ

  mov r0, #0x10
  bic r0, r0, #(IRQ+FIQ)            @ Habilita interrupções
  msr cpsr,r0                       @ Move processador para modo usuário
  mov sp, #STACK                    @ Inicializa a pilha

  mov r5, #0                        @ Inicializa contador timer
  ldr r0, =TIMER
  ldr r1, =INTERVAL
  str r1, [r0]                      @ Inicializa intervalo timer

waiting_close_safe_loop:
  ldr r1, =SAFE_OPEN
  ldrb r0, safe_state
  cmp r0, r1
  beq waiting_close_safe_loop       @ Continua em loop enquanto o estado do cofre é aberto

  ldr r8, =LEDS
  ldr r9, =GREEN
  str r9, [r8]                      @ Muda o led para verde, mostrar que espera uma senha

configure_password_process:
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

  mov r5, #0                        @ Reinicializa o timer
  ldr r0, =safe_state
  ldr r1, =SAFE_TIMER_WAITING
  strb r1, [r0]                     @ Configura espera pelo timer para apagar display

waiting_timer_loop:
  ldr r1, =SAFE_TIMER_WAITING
  ldrb r0, safe_state
  cmp r0, r1
  beq waiting_timer_loop            @ Espera em loop o timer contar 5 vezes antes de apagar o display

  mov r5, #0                        @ Reinicializa o timer
  ldr r0, =safe_state
  ldr r1, =SAFE_UNLOCK_FLOW
  strb r1, [r0]                     @ Configura cofre no estado de desbloquear cofre

unlock_safe_process:
  bl disable_previous_keyboard
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

  cmp r1, r2                        @ Compara as duas senhas
  beq correct_password              @ Caso sejam iguais, desvia para o final

  ldr r3, =password_tries           @ Caso sejam diferentes, aumenta o contador de senhas erradas em 1
  ldrb r4, password_tries
  add r4, #1
  cmp r4, #3
  bcs end                           @ Caso tenha chego em 3, trava o cofre para sempre

  strb r4, [r3]                     @ Senão, salva o novo número
  b unlock_safe_process             @ Para senhas diferentes, retorna ao fluxo de desbloquear

correct_password:
  ldr r0, =LEDS
  ldr r1, =GREEN
  strb r1, [r0]                     @ Entra no estado fechado

waiting_button_restart_flow:
  ldrb r0, safe_state
  ldr r1, =SAFE_CLOSED_WAITING
  cmp r0, r1
  bne waiting_button_restart_flow   @ Espera o botão ser clicado para resetar tudo

  ldr r0, =LEDS
  mov r1, #0x00
  strb r1, [r0]                     @ Reseta os leds

  bl reset_display
  b _start                          @ Volta ao começo de tudo

end:
  mov r0, #0                        @ status -> 0
  mov r7, #1                        @ exit is syscall #1
  swi #0x55                         @ invoke syscall

safe_state: .skip 1                 @ Estado do cofre salvo
actual_digit: .skip 4               @ Próximo display dos dígitos da senha

password_tries: .skip 1             @ Tentativas de salvar senha
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

.equ SAFE_OPEN, 0x00                @ Estados do cofre para controle de desvios
.equ SAFE_TIMER_WAITING, 0x01
.equ SAFE_TIMER_FINISHED, 0x02
.equ SAFE_CLOSED_WAITING, 0x03
.equ SAFE_UNLOCK_FLOW,    0x04
