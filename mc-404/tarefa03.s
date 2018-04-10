@@ Tarefa 03
@@ William Gonçalves da Cruz, 188671

MEMORY_END   	   .equ 0x1000
EXPECTED_KEY	   .equ 0x0F

DISPLAY_DATA  	 .equ 0x40

KEYBOARD_DATA    .equ 0x80
KEYBOARD_STAT    .equ 0x81
KEYBOARD_READY	 .equ 1

SUM_CODE         .equ 0x0B
END_CODE       	 .equ 0x0A

digits:
  .byte 0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B,0x77,0x1F,0x4E,0x3D,0x4F,0x47

read:
  inb r11, KEYBOARD_STAT
  tst r11, r10                        @ Espera a leitura do primeiro dígito do teclado
  jz read
  inb r0, KEYBOARD_DATA               @ Guarda o valor hexadecimal em r0

read_second:
  inb r11, KEYBOARD_STAT
  tst r11, r10                        @ Espera a leitura do segundo dígito do teclado
  jz read_second
  inb r1, KEYBOARD_DATA               @ Guarda '#' ou '*' em r1
  ret

display:
  set r12, digits
  add r12, r0                         @ Move r12 até a posição do dígito desejado

  ld r11, [r12]
  outb DISPLAY_DATA, r11              @ Carrega em r11 o dígito a ser exibido e mostra no display
  ret

inicio:
  set sp, MEMORY_END                  @ Inicializa pilha para o fim da memória

  set r9, SUM_CODE                    @ Inicializa r9 com o código para mais uma soma desejada
  set r10, KEYBOARD_READY             @ Inicializa r10 com o status de ready do teclado

  set r4, 0                           @ Inicializa r4 para ser o acumulador de soma
  outb DISPLAY_DATA, r4               @ Inicializa o display com a soma atual

loop:
  call read                           @ Lê uma entrada

  add r4, r0
  mov r0, r4                          @ Acumula em r4 e prepara para ser mostrada a soma no display
  call display

  tst r1, r9                          @ Caso o segundo dígito seja '#', continua a soma
  jz loop                             @ Caso o segundo dígito seja '*', termine o programa

end:
	hlt
