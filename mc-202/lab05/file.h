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

#define INITIAL_COUNT 1;

/* Definição de string */
typedef char string[21];

typedef 
	struct {
		int count;
		string name;
	} File;

/* Cria um ponteiro de arquivo a partir de um nome */
File* createFile(string);

/* Aumenta a contagem do arquivo */
void increase(File**);

/* Diminue a contagem do arquivo */
void decrease(File**);

#endif