/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : W
 *
 * Esse arquivo contém as declarações de :
 *      Funções relacionadas a criptografia e a realizar as operações na lista a fim de
 *      armazenar, deletar ou alterar os dados de consulta da lista, como também encontrar
 *      os registros a partir de suas chaves
 */

#ifndef OPERACOES_H_
#define OPERACOES_H_

#include "structs.h"

// Definindo as operações na lista de consultas
#define FIM_OPERACOES "0"

#define INSERIR "add"
#define REMOVER "rm"
#define ALTERAR_DATA "altdata"
#define ALTERAR_DOENCA "altdiag"
#define ALTERAR_MEDICO "altmed"

// Definindo o tamanho da string de entrada para a operação
#define TAMANHO_OPER 8

typedef char Operacao[TAMANHO_OPER];

void inserir(Lista*, Consulta*, Relatorio*);
void remover(Lista*, String, Relatorio*);

void criptografia (String, Chave, String);

void definirOperacao(Operacao);
void aplicarOperacoes(Lista*, Relatorio*, Doenca*, Medico*);

void imprimeConsulta(Consulta*, Relatorio*);
void listarConsultas(Lista*, Relatorio*);

Medico* encontrarMedico(String, Medico*);
Doenca* encontrarDoenca(String, Doenca*);
Consulta* encontrarConsulta(Lista*, String, Relatorio*);

#endif
