@@ Teste 01
@@ William Gonçalves da Cruz, 188671

  carac: .skip 1
  cadeia: .skip 33          @ Guarda espaço para as entradas do programa

  index: .skip 4
  rindex: .skip 4

inicio:
  set r0, -1
  set r1, -1                @ Inicializa r0 e r1 como os contadores do indices de aparição

  set r11, 0                @ Posição atual da cadeia

  set r2, cadeia            @ Coloca r2 no começo da cadeia
  ldb r10, carac            @ Carrega r10 com o caracter desejado

loop:
  ldb r3, [r2]              @ Carrega em r3 o caracter atual da cadeia

  cmp r3, 0x0
  jz  fim                   @ Chegou ao fim da cadeia

  sub r3, r10
  jnz continua_loop         @ Caso r3 não seja o caracter desejado, continua o loop

  cmp r0, -1
  jg index_final            @ Caso o índice inicial já tenha valor, não o sobreescreve

  mov r0, r11               @ Caso contrário, marca o primeira indice onde carac aparece

index_final:
  mov r1, r11               @ Sempre sobreescreve o índice final com o último valor encontrado

continua_loop:
  add r2, 1                 @ Passa r2 para o próximo byte a ser lido
  add r11, 1                @ Aumenta a contagem de posições de r11
  jmp loop                  @ Para continuar o loop

fim:
  st index, r0
  st rindex, r1             @ Guarda os valores de r0 e r11 (posições) nas palavras designadas

  hlt
