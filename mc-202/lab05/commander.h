/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef COMMANDER_H
#define COMMANDER_H

#include "tree.h"

/* Esse arquivo conterá as definições para as funções de commando
 * de listagem, remoção e adição de arquivos no diretório
 */

/* Mensagem caso não existam arquivos correspondentes a expressão no diretório */
#define EMPTY_MESSAGE "nao existem arquivos com essa expressao\n"

/* Definições dos commandos que o programa pode realizar nos arquivos de entrada */
#define RM "rm"
#define LS "ls"
#define TOUCH "touch"

/* Lista todos os arquivos que contém a expressão parametrizada no nome */
void ls(Tree*, String);

/* Remove todos os arquivos que contém a expressão parametrizada no nome */
void rm(Tree*, String);

/* Cria um arquivo no diretório com o nome parametrizado */
void touch(Tree*, String);

/* A partir de uma expressão, retorna a lista de arquivos encontrados */
List* similar(Tree*, String, int);

/* Insere na lista todos os arquivos similares a expressão dada */
void similarExpression(NodeTree*, String, List**, int);

/* Printa mensagem de não encontrado */
void printError();

#endif