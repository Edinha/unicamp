#ifndef STRUCTS_H_
#define STRUCTS_H_

// Definições dos tamanhos máximos para certos tipos da entrada

#define ESPACO ' '
#define FIM_LINHA '\n'
#define FIM_STRING '\0'

#define DIMENSAO_MATRIZ 2

#define TAMANHO_NOME 101
#define TAMANHO_CID 4
#define TAMANHO_CRM 7

typedef char String[TAMANHO_NOME];
typedef char CID[TAMANHO_CID];
typedef char CRM[TAMANHO_CRM];

typedef short Chave[DIMENSAO_MATRIZ][DIMENSAO_MATRIZ]; 

// Definição das estruturas utilizadas pelo programa

typedef 
    struct {
        unsigned char dia, mes;
        int ano;
    } Data;

typedef 
    struct {
        CID codigo;
        String nome;
    } Doenca;

typedef
    struct {
        CRM registro;
        String nome;
    } Medico;

typedef 
    struct {
        String paciente;
        Data data;
        CID diagnostico;
        CRM medico;
    } Consulta;

typedef 
    struct {
        Chave matriz;
        char letraPreferida;
    } Relatorio;

/* 
 *  Funções de Leitura do programa e suas declarações
 */

void lerString(String);

void lerNumero(unsigned char*);
void lerTexto(char[], unsigned char, char);
void lerData(Data*);

void lerDoenca(Doenca*);
void lerMedico(Medico*);
void lerConsulta(Consulta*);

void lerConsultas();
void lerMedicos();
void lerDoencas();

void lerMatrizChave(Chave*);
void lerLetraPreferida(char*);

char minuscula (char);

#endif

