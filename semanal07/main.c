/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : W
 */

#include "structs.h"
#include "operacoes.h"

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

    listarConsultas(&consultas, &relatorio);

    free(doencas);
    free(medicos);
    freeLista(consultas.primeiro, consultas.primeiro->proximo);

    return 0;
}
