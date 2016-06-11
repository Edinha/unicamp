#include "operacoes.h"

unsigned char iguais (char entrada[], char procurado[]) {
    return !strcmp(entrada, procurado);
}

void inserir(Lista * consultas, Consulta * consulta) {
    // TODO
}

void remover(Lista * consultas, Consulta * consulta) {
    // TODO
}

void alteraData(Consulta * consulta, Data data) {
    // TODO
}

void alteraMedico(Consulta * consulta, Medico* medico) {
    // TODO
}

void alteraDiag(Consulta * consulta, Doenca* doenca) {
    // TODO
}

Medico* encontrarMedico(CRM crm, Medico * medicos) {
    for (unsigned char i = 0;;i++) {
        if (iguais(medicos[i].crm, crm))
            return &medicos[i];
    }
    
    return NULL;
}

Doenca* encontrarDoenca(CID codigo, Doenca * doencas) {
    for (unsigned char i = 0;;i++) {
        if (iguais(doencas[i].codigo, codigo))
            return &doencas[i];
    }
    
    return NULL;
}

Consulta* encontrarConsulta(Lista * consultas, String paciente) {
    // TODO
    return consultas->primeiro->consulta;
}

void criptografar(String nome, Chave chave, String criptografado) {
    // TODO
}

void definirOperacao(Operacao op) {
    unsigned char i;
    char letra;

    for (i = 0; i < TAMANHO_OPER; i++) {
        scanf("%c", &letra);
        
        if (letra == ESPACO || letra == FIM_LINHA)
            break;

        op[i] = letra;
    }

    op[i] = FIM_STRING;
}

void aplicarOperacoes(Lista * consultas, Relatorio * relatorio, Doenca * doencas, Medico * medicos) {
    Operacao op;

    for (;;) {
        Consulta consulta;

        definirOperacao(op);

        // Caso tenha lido "0", encerram-se as operacoes
        if (iguais(FIM_OPERACOES, op))
            break;

        // TODO ler nome paciente
        lerTexto(consulta.paciente, TAMANHO_NOME, ESPACO);
        printf ("Acao %s Nome paciente : %s\n", op, consulta.paciente);
        break;

        if (iguais(INSERIR, op)) {
            // TODO inserir
        }       

        if (iguais(REMOVER, op)) {
            // TODO remover 
        }

        if (iguais(ALTERAR_DATA, op)) {
            // TODO alterar data 
        }
        
        if (iguais(ALTERAR_DOENCA, op)) {
            // TODO alterar diagnostico doença 
        }        
    }
}







