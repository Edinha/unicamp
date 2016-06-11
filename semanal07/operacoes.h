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

// Definindo o tamanho da string de entrada para a operação
#define TAMANHO_OPER 8

typedef char Operacao[TAMANHO_OPER];

void inserir(Lista*, Consulta*);
void remover(Lista*, Consulta*);

void criptografar(String, Chave, String);

void alteraData(Consulta*, Data);
void alteraMedico(Consulta*, Medico*);
void alteraDiag(Consulta*, Doenca*);

void definirOperacao(Operacao);
void aplicarOperacoes(Lista*, Relatorio*, Doenca*, Medico*);

Medico* encontrarMedico(CRM, Medico*);
Doenca* encontrarDoenca(CID, Doenca*);

Consulta* encontrarConsulta(Lista*, String);

unsigned char iguais (char[], char[]);

#endif
