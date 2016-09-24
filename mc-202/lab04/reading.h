/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef READING_H
#define READING_H

#include <stdio.h>
#include <stdlib.h>

/* Serão aqui descritas as definições das funções de leitura do programa em formato da matriz de
* de Rainhas de entrada do programa */

/* Definição da mensagem de erro e sucesso para solução do problema */
#define ERROR_MESSAGE "Sem solucao\n"
#define SUCESS_MESSAGE "Tem solucao\n"

/* Define a estrutura que guarda os valores para o tabuleiro */
typedef
    struct {
        int size;
        char ** matrix;
    } Board;

/* Lê um inteiro no parâmetro passado */
void readInt (int*);

/* Lê um char no parâmetro passado */
void readChar (char*);

/* Lê um vetor específico da entrada  */
void readArray (char*, int size);

/* Lê e retorna a matriz alocada com o tamanho da entrada e retorna o tabuleiro */
Board* readMatrixEntry();

/* Libera a memória alocada para o tabuleiro */
void freeBoard(Board*);

#endif