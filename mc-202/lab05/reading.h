/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef READING_H
#define READING_H

#include "commander.h"

/* Esse arquivo conterá as definições para as funções de entrada do programa
 * como leitura e manutenção dos dados
 */

// TODO this will receive also the motherfucking tree and the printing functions
/* Lê em uma repetição os comandos da entrada e os executa para a estrutura parametrizada */
void readAllCommands(Tree*);

/* Decide qual método aplicar no diretório de acordo com a entrada de commando da linha */
void decideCommandAction(Tree*, String, String);

#endif