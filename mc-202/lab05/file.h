/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Esse arquivo conterá as definições para a estrutura de um arquivo de entrada
 * a ser controlado pelo programa
 */

/* Constantes númericas para retorno de comparação do prefixo inicialização do programa */
#define LESSER -1
#define EQUALS 0
#define HIGHER 1
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
 * Retorna EQUALS caso seja prefixo possível e LESSER, HIGHER caso contrário,
 * dependendo se é menor ou maior, leva em consideração * para regex
 */
int isPrefixExpression(File*, String);

/* Printa o nome do arquivo n vezes, dado quantos dele existem no diretório */
void printFilename(File*);

/* Libera a memória de uma estrutura de arquivo */
void freeFile(File**);

#endif