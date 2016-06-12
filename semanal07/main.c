#include "structs.h"
#include "operacoes.h"

void freeLista(No * prim, No * atual) {
    if (atual == NULL)
        return;
    
    if (atual->proximo == prim) { 
        free(atual);
        return;
    }

    freeLista(prim, atual->proximo);
    free(atual->consulta);
    free(atual);
}

int main() {
    Relatorio relatorio;
    
    Doenca * doencas;
    Medico * medicos;

    Lista consultas;
    consultas.primeiro = NULL;

    lerNumero(&relatorio.qtdDoencas);

    doencas = (Doenca*) malloc(sizeof(Doenca) * relatorio.qtdDoencas);   

    lerDoencas(doencas, relatorio.qtdDoencas);

    lerNumero(&relatorio.qtdMedicos);

    medicos = (Medico*) malloc(sizeof(Medico) * relatorio.qtdMedicos);

    lerMedicos(medicos, relatorio.qtdMedicos);

    lerMatrizChave(relatorio.chave);

    chaveInversa(relatorio.chave, relatorio.inversa);
    
    lerLetraPreferida(&relatorio.letraPreferida);

    aplicarOperacoes(&consultas, &relatorio, doencas, medicos);

    // TODO explode this
    String v;//, s = "NACIUKMF\0";
    No * atual = consultas.primeiro;
    printf("\nComeço listagem : \n\n");
    for (;;) {
        zerar(v);
        Consulta * consulta = atual->consulta;
       
        criptografia(consulta->paciente, relatorio.inversa, v);
        printf("%s %s %s %s\n", v, consulta->data, consulta->diagnostico, consulta->crmMedico);
        
        atual = atual->proximo;
        if (atual == consultas.primeiro)
            break;
    }

    free(doencas);
    free(medicos);
   
    freeLista(consultas.primeiro, consultas.primeiro->proximo);

    return 0;
}
