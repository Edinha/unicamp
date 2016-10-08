/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef FILE_H
#define FILE_H

#include <stdlib.h>
#include <string.h>

/* Esse arquivo conterá as definições para a estrutura de um arquivo de entrada
 * a ser controlado pelo programa
*/

/* Constantes númericas para retorno booleano e inicialização do programa */
#define ERROR 0
#define SUCCESS 1
#define INITIAL_COUNT 1;

/* Constantes de char do programa */
#define REGEX_LETTER '*'
#define STRING_END '\0'

/* Definição de String */
typedef char String[21];

typedef
	struct {
		int count;
		String name;
	} File;

/* Cria um ponteiro de arquivo a partir de um nome */
File* createFile(String);

/* Aumenta a contagem do arquivo */
void increase(File**);

/* Faz uma comparação entre os nomes dos arquivos parametrizados
 * Retorna 0 caso sejam iguais, positivo caso o primeiro seja maior que o segundo
 * e negativo caso o primeiro seja menor que o segundo, ordem alfabética respeitada
 */
int compareFiles(File*, File*);

/* Método que compara o nome do arquivo com a expressão parametrizada
 * Retorna SUCCESS caso seja prefixo possível e ERROR caso contrário,
 * leva em conta o uso do * para regex
 */
int isPrefixExpression(File*, String);

/* Libera a memória de uma estrutura de arquivo */
void freeFile(File**);

#endif