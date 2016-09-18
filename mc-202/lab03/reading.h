/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef READING_H
#define READING_H

#include "doll.h"
#include "builder.h"

/* Serão aqui descritas as definições das funções de leitura do programa em formato de vetor,
 * a ser passado para a montagem das estruturas de bonecas no 'builder'.
 */

/* Definição da mensagem de erro para sequência inválida */
#define ERROR_MESSAGE "sequencia invalida ou nao pode colorir\n"

/* Lê um inteiro no parâmetro passado */
void readInt (int*);

/* Lê o vetor de entrada do arquivo, bem como seu tamanho e o retorna */
int readArrayFromFile (int**);

/* Método que criará a relação entre as bonecas da entrada e retornará caso aconteca erro de leitura */
void createDollsRelation (Doll**);

#endif