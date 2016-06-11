#include "structs.h"

// FIXME if needed
void lerTexto (char texto[], unsigned char tamanho, char final) {
    unsigned char i;
    char letra;

    for (i = 0; i < tamanho; i++) {
        scanf("%c", &letra);

        if (letra == final)
            break;

        texto[i] = letra;
    }

    texto[i] = FIM_STRING;
}

void lerNumero(unsigned char * num) {
    scanf("%hhu ", num);
}

void lerInteiro(int * num) {
    scanf("%d ", num);
}

void lerDoenca(Doenca * doenca) {
    lerTexto(doenca->codigo, TAMANHO_CID, ESPACO);
    lerTexto(doenca->nome, TAMANHO_NOME, FIM_LINHA);
}

void lerMedico(Medico * medico) {
    lerTexto(medico->crm, TAMANHO_CRM, ESPACO);
    lerTexto(medico->nome, TAMANHO_NOME, FIM_LINHA);
}


void lerMedicos(Medico * medicos, unsigned char qtd) {
    for (unsigned char i = 0; i < qtd; i++) {
        Medico medico;
        lerMedico(&medico);
        medicos[i] = medico;
    }
}

void lerDoencas(Doenca * doencas, unsigned char qtd) {
    for (unsigned char i = 0; i < qtd; i++) {
        Doenca doenca;
        lerDoenca(&doenca);
        doencas[i] = doenca;
    }
}

void lerMatrizChave(Chave chave) {
    unsigned char i, j;
    for (i = 0; i < DIMENSAO_MATRIZ; i++)
        for (j = 0; j < DIMENSAO_MATRIZ; j++)
            lerInteiro(&chave[i][j]);
}

void lerLetraPreferida(char * letra) {
    scanf("%c ", letra);
}

void lerConsulta(Consulta * consulta) {
    // TODO read
}

void zerar (String s) {
    for (unsigned char i = 0; i < TAMANHO_NOME; i++)
        s[i] = 0;
}
