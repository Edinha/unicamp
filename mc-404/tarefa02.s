@@ Tarefa 02
@@ William Gonçalves da Cruz, 188671

  vetor: .skip 4 * 64           @ O vetor tem no máximo 64 elementos

  divisor: .word 1
  num_elem: .word 1             @ Reserva espaço para as palavras divisor e número de elementos

inicio:
  set r0, 0                     @ Iniciliza o contador para as somas

  ld r1, num_elem               @ Carrega em r1 o número de elementos
  ld r3, divisor                @ Carrega em r3 o valor para as divisões

  set r2, vetor                 @ Carrega em r2 a posição da primeira palavra do vetor
  set r11, 0x8000               @ Divisor entre valores positivos e negativos de 16 bits
  set r12, 0xffff               @ Valor usado no xor para encontrar o complemento de 2 de um número
  set r10, 0x0fffffff           @ Máscara para remover bit de sinal

loop_principal:
  ld r4, [r2]                   @ Carrega o valor apontado em r2 para r4 e r5,
  mov r5, r4                    @ afim de separar os dois números contidos nesta palavra

  set r6, 0x0ffff
  and r4, r6                    @ Isola os primeiros 16 bits em r4 (o primeiro número)

  set r6, 0xffff0000            @ Isola os últimos 16 bits em r5 (o segundo número)
  and r5, r6                    @ e também zera os bits menos significativos

  ror r5, 16                    @ Rotaciona r5 a direita a fim de ter o valor do segundo número

div_primeiro:
  set r6, 0                     @ Iniciliza r6 para contar o valor da divisão
  set r13, 1                    @ Coloca o passo da divisão como 1 positivo

  cmp r4, r11
  jl loop_div_primeiro          @ Pula para o loop caso a inicialização seja positiva

primeiro_negativo:
  xor r4, r12
  add r4, 1                     @ Caso seja um número negativo, pega o complemento de 2
  set r13, -1                   @ Coloca o passo da divisão como 1 negativo

  and r4, r10                   @ Remove o bit de sinal do número

loop_div_primeiro:
  sub r4, r3                    @ Subtrai o valor de divisor (r3) do número

  cmp r4, 0
  jl div_segundo                @ Sai do loop caso tenha passado para baixo do limite inferior

  add r6, r13                   @ Adiciona o passo ao contador de divisão
  jmp loop_div_primeiro

div_segundo:
  set r7, 0                     @ Iniciliza r7 para contar o valor da divisão
  set r13, 1                    @ Coloca o passo da divisão como 1 positivo

  cmp r5, r11
  jl loop_div_segundo           @ Pula para o loop caso a inicialização seja positiva

segundo_negativo:
  xor r5, r12
  add r5, 1                     @ Caso seja um número negativo, pega o complemento de 2
  set r13, -1                   @ Coloca o passo da divisão como 1 negativo

  and r5, r10                   @ Remove o bit de sinal do número

loop_div_segundo:
  sub r5, r3                    @ Subtrai o divisor em r3 para continuar o loop

  cmp r5, 0
  jl contagem                   @ Sai do loop caso tenha passado para baixo do limite inferior

  add r7, r13                   @ Adiciona o passo ao contador de divisão
  jmp loop_div_segundo

contagem:
  add r0, r6
  add r0, r7                    @ Soma as divisões salvas em r6 e r7 para r0

  add r2, 4                     @ Move r2 para a próxima palavra do vetor

  sub r1, 2
  cmp r1, 0
  jle fim                       @ Como cada palavra possui 2 números, subtrai 2 da contagem

  jmp loop_principal            @ Reitera sobre loop enquanto r1 náo chegar a zero

fim:
  hlt
