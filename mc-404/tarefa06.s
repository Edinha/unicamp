@@ Tarefa 06
@@ William Gonçalves da Cruz, 188671

INTERRUPTION .equ 0x10                        @ Tipo de interrupção
  .org INTERRUPTION*4
  .word tick_time                             @ Aloca a função a ser chamada pela interrupção
  .org  0x200                                 @ Pula os endereços da interrupção

TIMER .equ 0x50                               @ Endereço do timer
FIRST_SEMAPHORE .equ 0x90
SECOND_SEMAPHORE .equ 0x91                    @ Endereços semáforos

TIMER_COUNT_FINAL .equ 0x1E                   @ Valor para contagem de 30 interrupções
TIMER_COUNT_YELLOW .equ 0x19                  @ Valor para trocar os semáforos para amarelo (25 segundos)

FIRST_DISPLAY .equ 0x40
SECOND_DISPLAY .equ 0x41                      @ Endereços displays

RED .equ 0x04
GREEN .equ 0x01
YELLOW .equ 0x02                              @ Inicializa as cores possíveis para o semáforo

END_MEMORY .equ 0x8000

intervalo: .skip 32                           @ Endereço do intervalo em ms do temporizador
first_color: .skip 4
second_color: .skip 4                         @ Endereço para guardar as cores usada nas iteração passada

@ Ideia dos dígitos: Temos uma lista dos possíveis valores para os dígitos em todos os 30 ticks de interrupção contados

@ Digitos unários do contador
UNIT_DIGITS:
  .byte 0x7E,0x7B,0x7F,0x70,0x5F,0x5B,0x33,0x79,0x6D,0x30,0x7E,0x7B,0x7F,0x70,0x5F,0x5B,0x33,0x79,0x6D,0x30,0x7E,0x7B,0x7F,0x70,0x5F,0x5B,0x33,0x79,0x6D,0x30

@ Digitos de dezena do contador
TENTH_DIGITS:
  .byte 0x79,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E

tick_time:
  set r13, TIMER_COUNT_YELLOW
  sub r13, r0                                 @ Compara a contagem de ticks para saber se é o momento de trocar para amarelo
  jnz final_timer_count                       @ Caso não seja o exato momento, pula para o final

  call yellow_both_semaphores                 @ Caso seja o momento, colore de amarelo

final_timer_count:
  set r13, TIMER_COUNT_FINAL
  sub r13, r0
  jnz end_tick_time                           @ Pula para o final caso não tenha chego a zero

  set r0, 0                                   @ Reinicializa r12 para ser o contador de ticks
  call invert_colors                          @ Inverte as cores ao final da contagem

end_tick_time:
  set r13, TENTH_DIGITS                       @ Chamada do display para dígito mais significativo
  set r12, FIRST_DISPLAY
  call display_digit

  set r13, UNIT_DIGITS                        @ Chamada do display para dígito menos significativo
  set r12, SECOND_DISPLAY
  call display_digit

  add r0, 1                                   @ Adiciona um ao contador de tick
  iret

display_digit:
  add r13, r0                                 @ Adiciona ao valor de r13 o contador de ticks r0
  ld r13, [r13]                               @ Carrega o valor do dígito desejado
  outb r12, r13                               @ Escreve na porta de saida o dígito atual
  ret

invert_colors:
  ld r5, first_color                          @ Recupera as cores gravadas da penúltima interrupção
  ld r4, second_color                         @ Inverte as cores dos semáforos, carregando second em r4 e first em r5

  call color_semaphores

  st first_color, r4
  st second_color, r5                         @ Guarda o valor para a próxima iteração
  ret

yellow_both_semaphores:
  set r4, YELLOW
  set r5, YELLOW
  call color_semaphores                       @ Marca os dois controladores de cor como amarelos antes de colorí-los
  ret

color_semaphores:
  outb FIRST_SEMAPHORE, r4                    @ Coloca a cor atual dos semáforos na saída
  outb SECOND_SEMAPHORE, r5
  ret

inicio:
  set sp, END_MEMORY                          @ Coloca o ponteiro da pilha para o final da memória
  sti                                         @ Habilita interrupções

  set r0, 0                                   @ Reinicializa r0 para ser o contador de ticks

  set r5, RED
  set r4, GREEN                               @ Inicializa a cor dos dois semáforos
  call color_semaphores

  st first_color, r4
  st second_color, r5                         @ Guarda o valor para a próxima iteração

  ld r1, intervalo
  out TIMER, r1                               @ Escreve o intervalo no temporizador

loop:
  jmp loop                                    @ Espera a interrupção acontecer
