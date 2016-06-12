/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : W
 *
 * Esse arquivo contém declarações de :
 *      Funções de Leitura, Cálculos, liberar memória da listagem e transformações necessárias de tipos
 *      como, por exemplo, de uma letra para um número da tabela, além de conter as definições das
 *      estruturas do programa
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definições caractéres de string para uso comum das funções 
#define ESPACO ' '
#define FIM_LINHA '\n'
#define FIM_STRING '\0'

// Definições dos tamanhos máximos para certos tipos da entrada
#define DIMENSAO_MATRIZ 2

#define TAMANHO_NOME 101
#define TAMANHO_DATA 11
#define TAMANHO_CRM 7
#define TAMANHO_CID 4

// Definições números para cálculos e comparações 
#define MODULO 26
#define MAIOR 1
#define MENOR 0

// Definições dos tipos de string utilizados
typedef char String[TAMANHO_NOME];
typedef char Data[TAMANHO_DATA];
typedef char CID[TAMANHO_CID];
typedef char CRM[TAMANHO_CRM];

// Talvez seja maior que unsigned char
typedef int Chave[DIMENSAO_MATRIZ][DIMENSAO_MATRIZ]; 

// Definição das estruturas utilizadas pelo programa
typedef 
    struct {
        CID codigo;
        String nome;
    } Doenca;

typedef
    struct {
        CRM crm;
        String nome;
    } Medico;

typedef 
    struct {
        String paciente;
        Data data;
        CID diagnostico;
        CRM crmMedico;
    } Consulta;

typedef 
    struct {
        int qtdDoencas, qtdMedicos;
        Chave chave, inversa;
        char letraPreferida;
    } Relatorio;

typedef
    struct No {
        Consulta * consulta;
        struct No * proximo;
    } No;

typedef 
    struct {
        No * primeiro;
    } Lista;


void lerInteiro(int*);
void lerTexto(char[], unsigned char, char);

void lerDoenca(Doenca*);
void lerDoencas(Doenca*, unsigned char);

void lerMedico(Medico*);
void lerMedicos(Medico*, unsigned char);

void lerMatrizChave(Chave);
void lerLetraPreferida(char*);

void zerar(String);

void chaveInversa(Chave, Chave);
void multiplicarMatrizes(Chave, int[]);

void freeLista(No*, No*);

char letraTabelaPeloNumero(int);

unsigned char iguais(char[], char[]);
unsigned char nomeMaior(String, String);

int calcMod(int, int);
int determinante(Chave);
int numeroPelaLetraTabela(char);
int numeroInversoComModulo26(int);

#endif

