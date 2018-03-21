@@ Tarefa 01
@@ William Gonçalves da Cruz, 188671

  compr: .word 1         @ Reserva espaço para o tamanho
  sequencia: .skip 4*100 @ Reserva até 100 espaços para números inteiros

inicio:

  value: .word 1     @ Reserva espaço para o contador atual em memória
  resultado: .word 1 @ Reserva espaço para o resultado

  lesser .equ -100
  greater .equ 100 @ Inicializa os extremos necessários

  set r1, 0    @ Inicializa o registrador de contagem
  ld r0, compr @ Carrega no registrador a quantidade de iterações do programa

  set r3, sequencia - 4 @ Inicializa r3 para apontar para antes do começo da sequência

countdown:

  add r3, 4   @ Pula 4 bytes para o próximo elemento da lista
  ld r2, [r3] @ Carrega r2 com o valor do endereço salvo em r3

comparisons:
  cmp r2, greater
  jg tick         @ Compara r2 com 100 (greater) e pula a contagem de resultado caso seja maior

  cmp r2, lesser
  jl tick         @ Compara r2 com -100 (lesser) e pula a contagem de resultado caso seja menor

  add r1, 1       @ Aumenta a contagem em r1 caso as condições de intervalo sejam cumpridas

tick:
  sub r0, 1     @ Conta em ordem decrescente o valor de r0 até 0
  jnz countdown @ a fim de realizar [cmpr] iterações no programa

  st resultado, r1 @ Salva o valor da contagem de r1 finalmente
  hlt
