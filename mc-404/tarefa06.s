@@ Tarefa 06
@@ William Gonçalves da Cruz, 188671

INTERRUPTION .equ 0x10                        @ Tipo de interrupção
  .org INTERRUPTION*4
  .word tick_time                             @ Aloca a função a ser chamada pela interrupção
  .org  0x200                                 @ Pula os endereços da interrupção

TIMER .equ 0x50                               @ Endereço do timer
FIRST_SEMAPHORE .equ 0x90
SECOND_SEMAPHORE .equ 0x91                    @ Endereços semáforos

FIRST_DISPLAY .equ 0x40
SECOND_DISPLAY .equ 0x41                      @ Endereços displays

RED .equ 0x04
GREEN .equ 0x01
YELLOW .equ 0x02                              @ Inicializa as cores possíveis para o semáforo

END_MEMORY .equ 0x8000

intervalo: .skip 32                           @ Endereço do intervalo em ms do temporizador
first_color: .skip 4
second_color: .skip 4                         @ Endereço para guardar as cores usada nas iteração passada

DIGITS: .byte 0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B,0x77,0x1F,0x4E,0x3D,0x4F,0x47

@ Digitos unários do contador
UNIT_DIGITS:
  .byte 0x7E,0x7B,0x7F,0x70,0x5F,0x5B,0x33,0x79,0x6D,0x30,0x7E,0x7B,0x7F,0x70,0x5F,0x5B,0x33,0x79,0x6D,0x30,0x7E,0x7B,0x7F,0x70,0x5F,0x5B,0x33,0x79,0x6D,0x30

@ Digitos de dezena do contador
TENTH_DIGITS:
  .byte 0x79,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E

tick_time:
  set r13, UNIT_DIGITS
  add r13, r12
  ld r13, [r13]
  outb SECOND_DISPLAY, r13

  set r13, TENTH_DIGITS
  add r13, r12
  ld r13, [r13]
  outb FIRST_DISPLAY, r13

  add r12, 1

end_tick_time:
  iret

recolor_semaphores:
  set r2, YELLOW
  tst r4, r2
  jnz invert_colors                           @ Caso as cores atuais não sejam amarelos, inverte as cores

  call yellow_both_semaphores                 @ Senão, colore os dois de amarelo para a próxima iteração
  jmp end_recolor_semaphores                  @ Pula para o final da interrupção

invert_colors:
  ld r5, first_color                          @ Recupera as cores gravadas da penúltima interrupção
  ld r4, second_color                         @ Inverte as cores dos semáforos, carregando second em r4 e first em r5

  call color_semaphores

  st first_color, r4
  st second_color, r5                         @ Guarda o valor para a próxima iteração

end_recolor_semaphores:
  ret                                        @ Retorna da interrupção ao final

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

  set r5, RED
  set r4, GREEN                               @ Inicializa a cor dos dois semáforos
  call color_semaphores

  st first_color, r4
  st second_color, r5                         @ Guarda o valor para a próxima iteração

  ld r0, intervalo
  out TIMER, r0                               @ Escreve o intervalo no temporizador

  set r12, 0                                  @ Reinicializa r0 para ser o contador de ticks

loop:
  jmp loop                                    @ Espera a interrupção acontecer
