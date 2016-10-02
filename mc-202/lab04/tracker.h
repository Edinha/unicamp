/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef TRACKER_H
#define TRACKER_H

#include "reading.h"

/* Esse arquivo conterá as definições do algoritmo de backtracking para definir se
 * há solução no tabuleiro passado por parâmetro
 */

/* Estrutura para um elemento posicionado para a solução */
typedef
	struct {
		int index;
		char letter;
	} Element;

/* Define a função que retorna o valor absoluto de x */
#define ABS(x) ((x) > 0 ? (x) : -(x))

/* Definição dos padrões para erro e sucesso do retorno da função */
#define SUCESS 1
#define ERROR 0

/* Verifica se há solução para o programa e retorna */
int checkBoardSolution(Board*);

/* A partir de um prefixo e um tamanho, verifica se a disposição é válida */
int isPossiblePrefix(Element*, int);

/* Passa, por backtracking, avaliando as possibilidades e retorna se há solução ou não */
int tracePossibilities(Element*, Board*, int);

/* A partir do tabuleiro recebido, realiza os preparativos para o backtracking e retorna seu valor */
int checkBoardSolution(Board*);

/* Printa a mensagem respectiva ao resultado encontrado pelo algoritmo */
void printResult(int);

#endif