@@ Teste 01
@@ William Gonçalves da Cruz, 188671

  vetor: .skip 4 * 64           @ O vetor tem no máximo 64 elementos

  divisor: .word 1
  num_elem: .word 1             @ Reserva espaço para as palavras divisor e número de elementos

inicio:
  set r0, 0                     @ Iniciliza o contador para as somas

  ld r1, num_elem               @ Carrega em r1 o número de elementos
  ld r3, divisor                @ Carrega em r3 o valor para as divisões

  set r2, vetor                 @ Carrega em r2 a posição da primeira palavra do vetor

loop_principal:
  ld r4, [r2]                   @ Carrega o valor apontado em r4 e r5, afim de separar
  mov r5, r4                    @ os dois números contidos nesta palavra

  set r6, 0x0ffff
  and r4, r6                    @ Isola os primeiros 16 bits em r4 (o primeiro número)

  set r6, 0xffff0000            @ Isola os últimos 16 bits em r5 (o segundo número)
  and r5, r6                    @ e também zera os bits menos significativos

  ror r5, 16                    @ Rotaciona r5 a direita a fim de ter o valor do segundo número

div_primeiro:
  set r6, 0                     @ Iniciliza r6 para contar o valor da divisão

  cmp r4, 0
  jl  div_primeiro_negativo     @ Caso r4 seja negativo, faz outro loop

loop_div_primeiro:
  sub r4, r3                    @ Subtrai o valor de divisor (r3) do número

  cmp r4, 0
  jle div_segundo               @ Passa para a próxima divisão caso tenha passado do limite zero

  add r6, 1
  jmp loop_div_primeiro         @ Senão, é possível contar mais uma vez o número para a divisão

div_primeiro_negativo:
  add r4, r3
  cmp r4, 0
  jge div_segundo               @ Passa para a próxima divisão caso tenha passado do limite zero

  sub r6, 1
  jmp div_primeiro_negativo     @ Senão, é possível contar mais uma vez o número para a divisão

div_segundo:
  set r7, 0                     @ Iniciliza r7 para contar o valor da divisão

  cmp r4, 0
  jl  div_segundo_negativo      @ Caso r5 seja negativo, faz outro loop

loop_div_segundo:
  sub r5, r3                    @ Subtrai o valor de divisor (r3) do número

  cmp r5, 0
  jle contagem                  @ Passa para a próxima divisão caso tenha passado do limite zero

  add r7, 1
  jmp loop_div_segundo          @ Senão, é possível contar mais uma vez o número para a divisão

div_segundo_negativo:
  add r5, r3
  cmp r5, 0
  jge contagem                  @ Passa para a próxima divisão caso tenha passado do limite zero

  sub r7, 1
  jmp div_segundo_negativo      @ Senão, é possível contar mais uma vez o número para a divisão

contagem:

  add r0, r6
  add r0, r7                    @ Soma as divisões salvas em r6 e r7

  add r2, 4                     @ Move r2 para a próxima palavra do vetor

  sub r1, 1
  jz fim

  jmp loop_principal            @ Reitera sobre loop enquanto r1 náo chegar a zero

fim:
  hlt
