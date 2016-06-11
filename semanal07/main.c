#include "structs.h"
#include "operacoes.h"

int main () {
    Lista consultas;
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

    aplicarOperacoes(&consultas, &relatorio, doencas, medicos);

    //TODO explode
    /*int i, j;
    for (i = 0; i < relatorio.qtdDoencas; i++)
        printf("%s %s\n", doencas[i].codigo, doencas[i].nome);
    
    printf("\n");
    for (i = 0; i < relatorio.qtdMedicos; i++)
        printf("%s %s\n", medicos[i].crm, medicos[i].nome);

    printf("\n");
    for (i = 0; i < DIMENSAO_MATRIZ; i++)
        for (j = 0; j < DIMENSAO_MATRIZ; j++)
            printf("%d ", relatorio.chave[i][j]);
    */

    return 0;
}
