/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef COMMANDER_H
#define COMMANDER_H

#include "tree.h"

/* Esse arquivo conterá as definições para as funções de commando
 * de listagem, remoção e adição de arquivos no diretório
 * Todos os commandos retornam um inteiro, dizendo se arquivos similares a expressão
 * parametrizada foram encontrados ou não;
 */

/* Definições dos commandos que o programa pode realizar nos arquivos de entrada */
#define RM "rm"
#define LS "ls"
#define TOUCH "touch"

/* Definição dos estados para similares encontrados ou não */
#define FOUND 1
#define NOT_FOUND 0

/* Lista todos os arquivos que contém a expressão parametrizada no nome */
int ls(Tree*, String);

/* Remove todos os arquivos que contém a expressão parametrizada no nome */
int rm(Tree*, String);

/* Cria um arquivo no diretório com o nome parametrizado */
int touch(Tree*, String);

/* A partir de uma expressão, retorna se existem similares ou não */
int similar(Tree * directory, String expression, int isLsOperation);

/* Aplica a operação parametrizada a arquivos similares a expressão e altera o ponteiro caso algum
 * similar tenha sido encontrado.
 */
void similarExpression(NodeTree * root, String expression, Tree * directory, int isLsOperation, int * found);

#endif