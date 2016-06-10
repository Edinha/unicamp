#include <stdio.h>
#include "structs.h"

void lerString (String s) { 
    scanf(" %[^\n]s", s); 
}

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

    texto[i+1] = FIM_STRING;
}

void lerNumero(unsigned char * num) {
    scanf("%hhd ", num);
}

void lerData(Data * data) {
    scanf("%hhd/%hhd/%d ", &data->dia, &data->mes, &data->ano);
}

void lerDoenca(Doenca * doenca) {
    lerTexto(doenca->codigo, TAMANHO_CID, ESPACO);
    lerString(doenca->nome);
    //lerTexto(doenca->nome, TAMANHO_NOME, FIM_LINHA);
}

void lerMedico(Medico * medico) {
    // TODO read
}

void lerConsulta(Consulta * consulta) {
    // TODO read
}

void lerConsultas() {
    // TODO read all
}

void lerMedicos() {
    // TODO read all
}

void lerDoencas() {
    // TODO read all
}

void lerMatrizChave(Chave * chave) {
    // TODO Read matrix here
}

void lerLetraPreferida(char * letra) {
    scanf("%c ", letra);
}

char minuscula (char letra) {
    char min = (char) (letra - 32);
    return min;
}

int main () {
    unsigned char t;
    Doenca d;

    lerNumero(&t);

    lerDoenca(&d);

    printf("%s %s\n", d.codigo, d.nome);
    printf("%d\n", t);

    return 0;
}
