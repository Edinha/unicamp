#ifndef OPERACOES_H_
#define OPERACOES_H_

#include "structs.h"
#include <string.h>

// Definindo as operações na lista de consultas
#define FIM_OPERACOES "0"

#define INSERIR "add"
#define REMOVER "rm"
#define ALTERAR_DATA "altdata"
#define ALTERAR_DOENCA "altdiag"
#define ALTERAR_MEDICO "altmed"

#define MODULO 26
#define MAIOR 1
#define MENOR 0

// Definindo o tamanho da string de entrada para a operação
#define TAMANHO_OPER 8

typedef char Operacao[TAMANHO_OPER];

void inserir(Lista*, Consulta*, Relatorio*);
void remover(Lista*, Consulta*, Relatorio*);

void criptografia (String, Chave, String);

void alteraData(Consulta*, Data);
void alteraMedico(Consulta*, Medico*);
void alteraDiag(Consulta*, Doenca*);

void definirOperacao(Operacao);
void aplicarOperacoes(Lista*, Relatorio*, Doenca*, Medico*);

void chaveInversa(Chave, Chave);

Medico* encontrarMedico(String, Medico*);
Doenca* encontrarDoenca(String, Doenca*);

Consulta* encontrarConsulta(Lista*, String, Relatorio*);

unsigned char iguais (char[], char[]);
unsigned char nomeMaior (String, String);

#endif
