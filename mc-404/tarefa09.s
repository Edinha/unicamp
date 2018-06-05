@@ Tarefa 09
@@ William Gonçalves da Cruz, 188671

  .global _start

  .set IRQ, 0x6
  .set FIQ, 0x7
  .set STACK, 0x80000               @ Posição inicial da pilha

  .org IRQ*4
  b stop_button_press               @ Configura as interupções

stop_button_press:
  push { r0, r1, lr }

  ldrb r1, on_ride_state

  cmp r1, #ON_TRAVEL                @ Apenas executa caso esteja em trânsito, e não parado
  ldreq r1, =request_stop_msg
  bleq write_console                @ Escreve a mensagem de parada solicitada

  ldreq r0, =on_ride_state
  ldreq r1, =CALLED
  streqb r1, [r0]                   @ Muda o estado para não poder mais solicitar paradas após a primeira

  pop { r0, r1, lr }
  movs pc, lr

write_console:
  push { lr }

  bl msg_size                       @ Descobre o tamanho da mensagem em r1

  ldr r0, =STDOUT
  ldr r7, =WRITE_FLAG               @ Carrega as flags necessárias
  swi #0x55                         @ Faz a chamada de sistema

  pop { lr }
  bx lr

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

change_ride_state:                  @ Muda o estado do transporte baseado no valor de r1
  ldr r0, =on_ride_state
  strb r1, [r0]
  bx lr

wait_departure_buttons:             @ Esse método espera um clique no botão de partida e retorna o endereço do clicado
  ldr r0, arrival_button_address
  ldr r0, [r0, #1]
  cmp r0, #1
  bne wait_departure_buttons        @ Espera em loop até que o botão levante a flag de clicado

  bx lr

wait_arrival_buttons:               @ Esse método espera um clique no botão de chegada e retorna o endereço do clicado
  ldr r0, arrival_button_address
  ldr r0, [r0]
  cmp r0, #1
  bne wait_arrival_buttons          @ Espera em loop até que o botão levante a flag de clicado

  bx lr

invert_ways:                        @ Esse método inverte os caminhos que os transportes farão para continuar em loop
  @@ TODO make circular way here
  pop { r0, r1 }
  mov r5, r0
  mov r6, r1                        @ Desempilha informações inicializadas

  ldr r0, stop_name_address
  ldr r1, arrival_button_address
  push { r0, r1 }                   @ Coloca as atuais na própria pilha para próxima inversão

  ldr r0, =stop_name_address
  ldr r1, =arrival_button_address
  str r5, [r0]
  str r6, [r1]                      @ Salva as informações da pilha nos lugares relevantes

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
  msr cpsr, r0                      @ Move processador para modo usuário
  mov sp, #STACK                    @ Inicializa a pilha

  ldr r0, =stop_name_address
  ldr r1, =first_stop_name
  str r1, [r0]                      @ Inicializa o nome da parada atual na variável

  ldr r0, =arrival_button_address
  ldr r1, =FIRST_STOP_ARRIVAL
  str r1, [r0]                      @ Inicializa o endereço atual do botão de parada

  ldr r0, =third_stop_name
  ldr r1, =THIRD_STOP_ARRIVAL
  push { r0, r1 }                   @ Salva as informações para a troca no loop

main_loop:
  ldr r1, =ON_TRAVEL
  bl change_ride_state              @ Muda o estado para andando

  ldr r1, =next_stop_msg
  bl write_console                  @ Escreve próximia parada no console

  ldr r1, stop_name_address
  bl write_console                  @ Nome da próxima parada

  bl wait_arrival_buttons           @ Espera o clique de um botão de arrival

  ldr r1, =STOPPED
  bl change_ride_state              @ Muda o estado para parado

  ldr r1, =arrival_msg
  bl write_console                  @ Mensagem de chegada ao ponto

  ldr r1, stop_name_address
  bl write_console

  bl wait_departure_buttons         @ Espera o clique de um botão de departure

  ldr r1, =ON_TRAVEL
  bl change_ride_state              @ Muda o estado para andando novamente

  ldr r3, arrival_button_address
  ldr r0, =arrival_button_address
  ldr r1, =SECOND_STOP_ARRIVAL
  str r1, [r0]                      @ Muda o valor da variável apenas para o loop do meio

main_loop_middle_stop:              @ Parte específica do loop para o ponto do meio
  ldr r1, =next_stop_msg            @ Executa as mesmas ações porém tendo certeza de que é o meio
  bl write_console

  ldr r1, =second_stop_name
  bl write_console

  bl wait_arrival_buttons

  ldr r1, =STOPPED
  bl change_ride_state              @ Muda o estado para parado

  ldr r1, =arrival_msg
  bl write_console                  @ Mensagem de chegada ao ponto

  ldr r1, =second_stop_name
  bl write_console

  bl wait_departure_buttons         @ Espera o clique de um botão de departure

  ldr r0, =arrival_button_address
  str r3, [r0]                      @ Volta ao valor anterior

  bl invert_ways                    @ Inverte o caminho para o próximo loop
  b main_loop                       @ Continua em loop eterno

end:
  mov r0, #0
  mov r7, #1
  swi #0x55                         @ Finaliza o programa


next_stop_msg:                      @ Começo constantes para mensagens do console
  .ascii "Proxima parada "
  .byte 0

request_stop_msg:
  .ascii "Parada solicitada "
  .byte 0xA, 0x0

arrival_msg:
  .ascii "Chegamos a "
  .byte 0

first_stop_name:
  .ascii "Unimart"
  .byte 0x0A, 0x0

second_stop_name:
  .ascii "Cambui"
  .byte 0x0A, 0x0

third_stop_name:
  .ascii "Centro"
  .byte 0x0A, 0x0

on_ride_state: .skip 1              @ Estado para saber se está em trânsito ou não
stop_name_address: .skip 4          @ Variável para guardar o endreço do nome da próxima parada
arrival_button_address: .skip 4     @ Variável para guardar o endreço do botão da próxima parada

.equ STDOUT, 1
.equ WRITE_FLAG, 4                  @ Flags para configurar saída no console

.equ STOPPED,   0x01
.equ CALLED,    0x02
.equ ON_TRAVEL, 0x03                @ Estados para controlar o transporte

.equ FIRST_STOP_ARRIVAL,  0xa0001
.equ SECOND_STOP_ARRIVAL, 0xa0003
.equ THIRD_STOP_ARRIVAL,  0xa0005   @ Botões que indicam as paradas do trajeto

.equ FIRST_STOP_DEPARTURE,  0xa0002
.equ SECOND_STOP_DEPARTURE, 0xa0004
.equ THIRD_STOP_DEPARTURE,  0xa0006 @ Botões que indicam as sáidas do trajeto
