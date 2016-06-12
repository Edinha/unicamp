#include "structs.h"

void lerTexto(char texto[], unsigned char tamanho, char final) {
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

void zerar(String s) {
    for (unsigned char i = 0; i < TAMANHO_NOME; i++)
        s[i] = 0;
}

char letraTabelaPeloNumero(int num) {
    return (char) num + 'A';
}

unsigned char iguais(char entrada[], char procurado[]) {
    return !strcmp(entrada, procurado);
}

unsigned char nomeMaior(String nome, String comparado) {
    int comparacao = strcmp (nome, comparado);

    if (comparacao > 0)
        return MAIOR;

    return MENOR;
}

int numeroPelaLetraTabela(char letra) {
    return (letra - 'A');
}

int determinante(Chave chave) {
    int det = 0;
    det += chave[0][0] * chave[1][1];
    det -= chave[1][0] * chave[0][1];
    return det;
}

// Retorna o primeiro i encontrado a partir de 1 que satisfaz (det * i) % 26 == 1
int numeroInversoComModulo26(int det) {
    int numero;

    for (int i = 1;; i++) {
        numero = (i * det) % 26;
        
        if (numero  == 1) {
            return i;
        }
    }

    return -1;
}

// Calcula o módulo da multiplicação entre os os parâmetros
int calcMod(int num, int numChave) {
    int mult = num * numChave,
        mod  = mult % MODULO;

    /* Caso seja negativo, deve-se adicionar o número usado para modular
     * uma vez em ordem de manter o resultado esperado, pois o operadoe
     * modular do C (%) cálcula módulos a partir de divisões inteiras */
    if (mod < 0)
        mod += MODULO;

    return mod;
}

// Faz o cálculo da matriz inversa da matriz chave de entrada
void chaveInversa(Chave chave, Chave inversa) {
    int numInverso = numeroInversoComModulo26 (determinante(chave));

    inversa[0][0] = calcMod( numInverso, chave[1][1]);
    inversa[1][1] = calcMod( numInverso, chave[0][0]);
    inversa[0][1] = calcMod(-numInverso, chave[0][1]);
    inversa[1][0] = calcMod(-numInverso, chave[1][0]);
}

// Multiplica as duas matriz de entrada e aplica módulo 26 a saída
void multiplicarMatrizes(Chave chave, int matriz[]) {
    int prim = matriz[0],
        seg  = matriz[1];

    matriz[0] = prim * chave[0][0] + seg * chave[0][1];
    matriz[1] = prim * chave[1][0] + seg * chave[1][1];

    matriz[0] %= MODULO;
    matriz[1] %= MODULO;
}

