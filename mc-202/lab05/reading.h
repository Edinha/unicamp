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

/* Definições dos commandos que o programa pode realizar nos arquivos de entrada */
#define RM "rm"
#define LS "ls"
#define TOUCH "touch"

/* Lê uma String do programa de acordo com seu tipo de final, parametrizado como inteiro */
void readString(String, int);

/* Lê uma opção de comando para arquivos da entrada  */
void readCommand(String);

/* Lê um nome de arquivo da entrada */
void readFilename(String);

// TODO this will receive also the motherfucking tree and the printing functions
/* Lê em uma repetição os comandos da entrada e os executa para a estrutura parametrizada */
void readAllCommands(Tree*);

/* Decide qual método aplicar no diretório de acordo com a entrada de commando da linha */
void decideCommandAction(Tree*, String, String);

#endif