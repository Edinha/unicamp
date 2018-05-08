@@ Teste 2
@@ William Gonçalves da Cruz, 188671

.global _start
.org 0x1000                 @ Pula para endereço necessário

strncpy:
  mov r3, r0                @ Copia o endereço de começo da cadeia para r3
  mov r0, #0                @ Inicializa o contador de chars copiados

loop:
  ldrb r4, [r3], #1         @ Pega o char atual da cadeia

  cmp r4, #0
  beq final                 @ Caso r4 seja o char 0 (final da cadeia), termina o loop

  strb r4, [r1], #1         @ Guarda o char no endeço da nova cadeia

  add r0, #1
  sub r2, #1                @ Aumenta o contador de cópia e dimunui a contagem de chars copiados

  cmp r2, #0
  bne loop                  @ Caso a contagem não tenha chego a 0, continua o loop

final:
  mov r4, #0
  strb r4, [r1], #1         @ Coloca o char 0 ao final da nova cadeia

  bx lr

_start:
  ldr r0, test              @ Carrega endereço para cadeia de teste
  ldr r1, copy
  mov r2, #3

  bl strncpy                @ Chama a função de copiar strings

  mov r0, #0
  mov r7, #1
  swi #0x55                 @ Retorno ARM

msg_copy: .skip 0x100
          .byte 0

copy: .word msg_copy        @ Endereço cópias teste

msg:
    .ascii      "Uma mensagem muito boa de testes para copias"
    .byte       0

test: .word msg             @ Mensagem de testes
