/**************************************************
 * *	Universidade Estadual de Campinas             *
 * *	Instituto de Computação                       *
 * *	MC102 - TURMA: WY                             *
 * *	labSala06 - 08/06/2016                        *
 * *	ARQUIVO DE SUPORTE - IMPRIMIR HIERARQUIA      *
 * ***************************************************/

/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : W
 */

#include <stdio.h>
#include <math.h>

// Calcula o tamanho do vetor como 2^k - 1
int tamanhoVetor (int k) {
	return pow(2, k) - 1;
}

// Faz a leitura das letras de entrada do vetor
void lerVetor (char letras[], int tamanho) {
	for (int i = 0; i < tamanho; i++) {
		scanf("%c ", &letras[i]);
	}
}

// Calcula a hierarquia a partir de uma recursão
void hierarquia (char letras[], int nivel, int pos, int tamanho) {
	// pega o centro do vetor
	int centro = tamanho / 2;

	// Caso seja uma vetor menor que o singular
	if (tamanho <= 0)
		return;

	// passa o vetor a direita do atual
	// A partir da soma do centro + 1 para o novo começo do vetor
	hierarquia ((letras + centro + 1), nivel + 1, centro, centro);

	// Monta o vetor a esquerda da posicao atual
	char vetEsq[centro];
	for (int i = 0; i < centro; i++) {
		vetEsq[i] = letras[i];
	}

	// Imprime os traços de acordo com o nivel
	for (int i = 0; i <= nivel-1; i++) {
                printf("-----");
        }

	// Printa o elementro do centro do vetor atual
	printf ("%c\n", letras[centro]);
	
	// Chama para a esquerda do vetor montado acima
	hierarquia (vetEsq, nivel + 1, centro, centro);
}

int main(void) {
	int k,
	    tamanho,
	    posInicial;
	
	/*leitura da variavel k*/
	scanf("%d ", &k);
	/*encontrar o tamanho do vetor*/	
	tamanho = tamanhoVetor(k);

	char letras[tamanho];
	/*leitura do vetor*/
	lerVetor(letras, tamanho);	

	/*chamada da funcao, com a posição inicial como seu meio*/
	posInicial = tamanho / 2;
	hierarquia (letras, 0, posInicial, tamanho);
	return 0;
}
