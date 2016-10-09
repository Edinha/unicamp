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

/* Lista todos os arquivos que contém a expressão parametrizada no nome */
void ls(Tree*, String);

/* Remove todos os arquivos que contém a expressão parametrizada no nome */
void rm(Tree*, String);

/* Cria um arquivo no diretório com o nome parametrizado */
void touch(Tree*, String);

/* A partir de uma expressão, retorna a lista de arquivos encontrados */
List* similar(Tree*, String);

/* Insere na lista todos os arquivos similares a expressão dada */
void similarExpression(NodeTree*, String, List*);

#endif