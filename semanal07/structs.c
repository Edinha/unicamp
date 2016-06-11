#include "structs.h"

/*void lerString (String s) { 
    scanf(" %[^\n]s", s); 
} */

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

void lerData(Data * data) {
    scanf("%hhu/%hhu/%d ", &data->dia, &data->mes, &data->ano);
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
            lerNumero(&chave[i][j]);
}

void lerLetraPreferida(char * letra) {
    scanf("%c ", letra);
}

char minuscula (char letra) {
    char min = (char) (letra - 32);
    return min;
}

void lerConsulta(Consulta * consulta) {
    // TODO read
}

void lerConsultas(Lista lista) {
    // TODO read all
}

int main () {
    Relatorio relatorio;

    Doenca * doencas;
    Medico * medicos;

    lerNumero(&relatorio.qtdDoencas);

    doencas = (Doenca*) malloc(sizeof(Doenca) * relatorio.qtdDoencas);   

    lerDoencas(doencas, relatorio.qtdDoencas);

    lerNumero(&relatorio.qtdMedicos);

    medicos = (Medico*) malloc(sizeof(Medico) * relatorio.qtdMedicos);

    lerMedicos(medicos, relatorio.qtdMedicos);

    lerMatrizChave(relatorio.chave);

    lerLetraPreferida(&relatorio.letraPreferida);
    

    //TODO explode
    int i, j;
    for (i = 0; i < relatorio.qtdDoencas; i++)
        printf("%s %s\n", doencas[i].codigo, doencas[i].nome);
    
    printf("\n");
    for (i = 0; i < relatorio.qtdMedicos; i++)
        printf("%s %s\n", medicos[i].crm, medicos[i].nome);

    printf("\n");
    for (i = 0; i < DIMENSAO_MATRIZ; i++)
        for (j = 0; j < DIMENSAO_MATRIZ; j++)
            printf("%d ", relatorio.chave[i][j]);

    return 0;
}
