@@ Tarefa 07
@@ William Gonçalves da Cruz, 188671

.global _start
.org 0x1000                 @ Pula para endereço necessário

linhas:
  mov r1, r0                @ Carrega em r1 o endereço da cadeia de caractéres
  mov r0, #0                @ Inicializa a contagem de linhas

loop:
  ldrb r2, [r1], #1         @ Carrega o char atual da cadeia

  cmp r2, #0x0a
  addeq r0, #1              @ Compara o char com \n, caso igual adiciona 1 ao contador

  cmp r2, #0
  bne loop                  @ Continua o loop caso o char não seja 0

  bx lr                     @ Retorna do procedimento

_start:
  ldr r0, test              @ Carrega endereço para cadeia de teste
  bl linhas                 @ Chama a função de contar linhas

  mov r0, #0                @ status -> 0
  mov r7, #1                @ exit is syscall #1
  swi #0x55                 @ invoke syscall


msg:
    .ascii      "Um teste\nsimples\n\n"
    .byte       0

test: .word msg             @ Mensagem de testes
