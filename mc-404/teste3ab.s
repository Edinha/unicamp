@@ Teste 3 AB
@@ William Gonçalves da Cruz, 188671

  .org 0x1000
  .global _start

sequencia:
  ldr r1, =greatest_sequence
  mov r2, #0
  str r2, [r1]                      @ Inicializa a maior sequência com o número 0 (zero)

  mov r4, #0                        @ Inicializa contador de sequência atual

  mov r9, #0x01                     @ Máscara de início para extrair bits
  mov r2, #32                       @ Número de vezes que é preciso checar os bits

sequencia_loop:
  mov r1, r0                        @ Cópia

  and r1, r1, r9                    @ Máscara para remover todos os bits menos o desejado

  mov r3, #0
  cmp r3, r1
  addne r4, #1                      @ Adiciona ao contador mais um caso tenha encontrado um novo bit 1
  bne sequencia_tick

  ldr r1, greatest_sequence         @ Caso contrário, realiza a lógica ao encontrar um zero
  cmp r1, r4
  movges r4, #0                     @ Reseta contador caso a contagem seja menor, para não salvá-la
  bge sequencia_tick                @ Caso contrário, compara com a maior sequência salva, pula para o final se for menor

  ldr r1, =greatest_sequence
  str r4, [r1]                      @ Assim, salva r4 em maior sequência se for maior do que a já existente
  mov r4, #0                        @ Reseta contador também nesse caso, após ser salvo

sequencia_tick:
  mov r9, r9, LSL #1                @ Rotaciona a máscara para pegar o próximo bit

  mov r3, #0                        @ Comparador de final
  sub r2, #1
  cmp r3, r2
  bne sequencia_loop                @ Continua o loop caso não tenham sido testados 32 bits

  ldr r0, greatest_sequence
  cmp r4, r0
  movgt r0, r4                      @ Para o último caso, a maior sequência vai até o final

  bx lr                             @ Retorna em r0 o comprimento da maior sequência

_start:
  bl sequencia

end:
  mov r0, #0
  mov r7, #1
  swi #0x55                         @ Finaliza o programa

greatest_sequence: .skip 4
