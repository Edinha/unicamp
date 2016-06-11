#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <stdio.h>
#include <stdlib.h>

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
        unsigned char qtdDoencas, qtdMedicos;
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

/* 
 *  Funções de Leitura do programa e suas declarações
 */

void lerInteiro (int*);
void lerNumero(unsigned char*);
void lerTexto(char[], unsigned char, char);

void lerDoenca(Doenca*);
void lerDoencas(Doenca*, unsigned char);

void lerMedico(Medico*);
void lerMedicos(Medico*, unsigned char);

void lerMatrizChave(Chave);
void lerLetraPreferida(char*);

void lerConsulta(Consulta*);

void zerar (String);

/*void lerConsultas(Lista);
//void lerString(String);
//void lerData(Data*);
//char minuscula (char);
//char maiscula (char);*/

#endif

