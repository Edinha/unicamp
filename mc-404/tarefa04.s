@@ Tarefa 04
@@ William Gonçalves da Cruz, 188671

BUTTON .equ 0x40                             @ Endereço botão

FIRST_SEMAPHORE .equ 0x90
SECOND_SEMAPHORE .equ 0x91                   @ Endereços semáforos

RED .equ 0x04
GREEN .equ 0x01
YELLOW .equ 0x02                             @ Inicializa as cores possíveis para o semáforo

END_MEMORY .equ 0x1000

read_button:
  inb r0, BUTTON
  set r1, 0x01                               @ Espera o botão ser pressionado em loop
  tst r0, r1
  jz read_button                             @ Caso não tenha sido pressionado, volta a ler a entrada

  ret                                        @ Senão, retorna do procedimento

yellow_both_semaphores:
  set r4, YELLOW
  set r5, YELLOW
  call color_semaphores                      @ Marca os dois controladores de cor como amarelos antes de colorí-los
  ret

color_semaphores:
  outb FIRST_SEMAPHORE, r4                   @ Coloca a cor atual dos semáforos na saída
  outb SECOND_SEMAPHORE, r5
  ret

inicio:
  set sp, END_MEMORY                         @ Coloca o ponteiro da pilha para o final da memória

  set r5, RED
  set r4, GREEN                              @ Inicializa a cor dos dois semáforos

loop:
  call color_semaphores                      @ Colore os semáforos com verde e vermelho

  call read_button                           @ Espera o botão ser pressionado

  push r4
  push r5                                    @ Empilha as duas cores atuais para a próxima leitura

  call yellow_both_semaphores                @ Colore os semáforos com amarelho

  call read_button                           @ Espera um clique no botão para inverter as cores verde / vermelho entre os semáforos

  pop r4
  pop r5                                     @ Inverte as cores dos semáforos pela ordem contrária de desempilhamento

  jmp loop                                   @ Continua o loop indefinidamente

end:
  hlt
