@@ Tarefa 10
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
  cmp r1, #ON_TRAVEL
  bne stop_button_press_end         @ Caso não esteja em trânsito, não executa a lógica de parada solicitada

  mov r0, #LCD_THIRD_LINE
  bl config_lcd                     @ Muda para a linha do lcd onde pode escrever a mensagem

  ldr r1, =request_stop_msg
  bl write_msg_lcd                  @ Escreve a mensagem de parada solicitada

  ldr r0, =on_ride_state
  ldr r1, =CALLED
  strb r1, [r0]                     @ Muda o estado para não poder mais solicitar paradas após a primeira

stop_button_press_end:
  pop { r0, r1, lr }
  movs pc, lr

config_lcd:
  ldr r6, =LCD_DISPLAYPORT
  ldrb r6, [r6]
  tst r6, #LCD_BUSY
  beq config_lcd                    @ Espera o LCD não estar ocupado para escrever

  ldr r6, =LCD_DISPLAYPORT
  strb r0, [r6]                     @ Configura o LCD com o valor das flag rm r0
  bx lr

write_byte_lcd:                     @ Escreve um byte na porta de dados do lcd
  ldr r6, =LCD_DISPLAYPORT
  ldrb r6, [r6]
  tst r6, #LCD_BUSY
  beq write_byte_lcd                @ Espera o LCD não estar ocupado para escrever

  ldr r6, =LCD_DATAPORT             @ Escreve o byte salvo em r0 no lcd
  strb r0, [r6]
  bx lr

write_msg_lcd:                      @ Função para escrever no LCD mensagem em loop no lcd
  push { r0, lr }

write_msg_loop:
  ldrb r0, [r1]
  cmp r0, #0
  beq write_msg_end                 @ Caso seja um byte 0, chegou ao final

  bl write_byte_lcd
  add r1, #1                        @ Vai para o próximo endereço da cadeia
  b write_msg_loop                  @ Continua a loop de escrever a mensagem

write_msg_end:
  pop { r0, lr }
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

unable_previous_button_clicks:      @ Desabilita os cliques prévios para todos os botões disponíveis que não são de interrupção
  ldr r0, =FIRST_STOP_ARRIVAL
  ldr r1, =THIRD_STOP_DEPARTURE     @ Carrega as constantes para loop e comparação

unable_previous_buttons_loop:
  ldr r2, [r0]                      @ Lê o endereço do botão para desabilitar um clique prévio

  cmp r0, r1
  addnes r0, #1
  bne unable_previous_buttons_loop  @ Continua em loop enquanto não chega ao final

  bx lr                             @ Retorna do método

invert_ways:                        @ Esse método mantém os caminhos em loop
  ldr r2, stop_name_address
  ldr r1, =THIRD_STOP_ARRIVAL
  ldr r0, arrival_button_address    @ Carrega as posições do último nome para mudá-las

  cmp r0, r1                        @ Compara o ponto atual com o último

  ldreq r2, =first_stop_name_ref
  ldreq r0, =FIRST_STOP_ARRIVAL     @ Caso seja igual, volta ao primeiro

  addnes r2, #4
  addnes r0, #2                     @ Senão, avança ao próximo

  ldr r1, =arrival_button_address
  str r0, [r1]                      @ Salva o próximo endereço

  ldr r1, =stop_name_address
  str r2, [r1]                      @ Salva o nome do próximo ponto

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

  mov r0, #LCD_FUNCTIONSET+LCD_8BIT+LCD_TWOLINE+LCD_8DOTS
  bl config_lcd

  mov r0, #LCD_DISPLAYON+LCD_DISPLAYCONTROL+LCD_BLINKOFF
  bl config_lcd

  mov r0, #LCD_CLEAR
  bl config_lcd

  ldr r0, =stop_name_address
  ldr r1, =first_stop_name_ref
  str r1, [r0]                      @ Inicializa o nome da parada atual na variável

  ldr r0, =arrival_button_address
  ldr r1, =FIRST_STOP_ARRIVAL
  str r1, [r0]                      @ Inicializa o endereço atual do botão de parada

main_loop:
  ldr r1, =ON_TRAVEL
  bl change_ride_state              @ Muda o estado para andando

  ldr r1, =next_stop_msg
  bl write_msg_lcd                  @ Escreve próxima parada no lcd

  mov r0, #LCD_SECOND_LINE          @ Pula para a segunda linha
  bl config_lcd

  ldr r1, stop_name_address
  ldr r1, [r1]
  bl write_msg_lcd                  @ Nome da próxima parada

  bl wait_arrival_buttons           @ Espera o clique de um botão de arrival
  bl unable_previous_button_clicks

  mov r0, #LCD_CLEAR
  bl config_lcd                     @ Limpa o lcd para o estado de chegada

  ldr r1, =STOPPED
  bl change_ride_state              @ Muda o estado para parado

  ldr r1, =arrival_msg
  bl write_msg_lcd                  @ Mensagem de chegada ao ponto

  mov r0, #LCD_SECOND_LINE          @ Pula para a segunda linha
  bl config_lcd

  ldr r1, stop_name_address
  ldr r1, [r1]
  bl write_msg_lcd                  @ Nome da próxima parada

  bl wait_departure_buttons         @ Espera o clique de um botão de departure
  bl unable_previous_button_clicks

  mov r0, #LCD_CLEAR
  bl config_lcd                     @ Limpa o lcd para a saida da próxima viagem

  bl invert_ways
  b main_loop                       @ Continua em loop eterno

end:
  mov r0, #0
  mov r7, #1
  swi #0x55                         @ Finaliza o programa

next_stop_msg:                      @ Começo constantes para mensagens do console
  .asciz "Proxima parada "

request_stop_msg:
  .asciz "Parada solicitada "

arrival_msg:
  .asciz "Chegamos a parada "

first_stop_name:
  .asciz "Unimart"

second_stop_name:
  .asciz "Cambui"

third_stop_name:
  .asciz "Centro"

first_stop_name_ref:
  .word first_stop_name

second_stop_name_ref:
  .word second_stop_name

third_stop_name_ref:
  .word third_stop_name             @ Referências para os endereços das constantes de nome

on_ride_state: .skip 1              @ Estado para saber se está em trânsito ou não
stop_name_address: .skip 4          @ Variável para guardar o endreço do nome da próxima parada
arrival_button_address: .skip 4     @ Variável para guardar o endreço do botão da próxima parada

.equ STOPPED,   0x01
.equ CALLED,    0x02
.equ ON_TRAVEL, 0x03                @ Estados para controlar o transporte

.equ FIRST_STOP_ARRIVAL,  0xa0001
.equ SECOND_STOP_ARRIVAL, 0xa0003
.equ THIRD_STOP_ARRIVAL,  0xa0005   @ Botões que indicam as paradas do trajeto

.equ FIRST_STOP_DEPARTURE,  0xa0002
.equ SECOND_STOP_DEPARTURE, 0xa0004
.equ THIRD_STOP_DEPARTURE,  0xa0006 @ Botões que indicam as sáidas do trajeto

.equ LCD_DATAPORT, 0xb0001          @ Portas de acesso ao LCD
.equ LCD_DISPLAYPORT, 0xb0000

.equ LCD_DISPLAYON, 0x04            @ Constantes para controle display LCD
.equ LCD_BLINKOFF, 0x00
.equ LCD_CLEAR, 0x01
.equ LCD_DISPLAYCONTROL, 0x08
.equ LCD_BUSY, 0x80
.equ LCD_FUNCTIONSET, 0x20

.equ LCD_TWOLINE, 0x08
.equ LCD_8BIT, 0x10
.equ LCD_8DOTS, 0x00
.equ LCD_THIRD_LINE, 0x94
.equ LCD_SECOND_LINE, 0xC0
