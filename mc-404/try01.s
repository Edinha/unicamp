@@ Teste 01
@@ William Gonçalves da Cruz, 188671

  .org 0x100
  cadeia: .skip 4 * 32		@ Reserva espaço para cadeia começando em 0x100

inicio:
  set r0, cadeia
  mov r1, r0							@ Coloca r0 e r1 no começo da cadeia

busca:
	ld r2, [r1]							@ Carrega o caracter atual da cadeia em r2

	cmp r2, 0x00
	jz	inverter						@ Se chegou ao final da cadeia, começa o processo de inverter

	add r1, 4								@ Move r1 até o final da cadeia em um loop
	jmp busca

inverter:
	sub r1, 4								@ Volta a posição de r1 pra o último char da cadeia que não é o final

loop_inverter:

	ld r10, [r0]
	ld r11, [r1]						@ Carrega os caracteres a serem invertidos em auxiliares (r10 e r11)

	st [r0], r11
	st [r1], r10						@ Inverte na própria cadeia os caracteres

	cmp r0, r1
	jge fim									@ Caso r0 e r1 tenham se encontrado ou passado um pelo outro (r0 tenha passado r1), chegou ao final da inversão

	add r0, 4
	sub r1, 4								@ Move r0 para o próximo e r1 para o anterior, a fim de invertê-los na próxima iteração

	jmp loop_inverter

fim:
	hlt
