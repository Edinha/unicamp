/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : W
 */   

#include "operacoes.h"

// Faz a criptografia de uma string de entrada usando a técnica de Hill com a matriz 
// chave (parametrizada) e devolve o resultado no último parâmetro
void criptografia(String entrada, Chave chave, String descript) {
    int matriz[DIMENSAO_MATRIZ];
    for (unsigned char i = 0; i < TAMANHO_NOME; i += 2) {
        if (entrada[i] == FIM_STRING) {
            descript[i] = FIM_STRING;
            break;
        }

        matriz[0] = numeroPelaLetraTabela(entrada[i]);
        matriz[1] = numeroPelaLetraTabela(entrada[i+1]);

        multiplicarMatrizes (chave, matriz);

        descript[i]   = letraTabelaPeloNumero(matriz[0]);
        descript[i+1] = letraTabelaPeloNumero(matriz[1]);
    }
}

// Insere uma nova consulta na lista mantendo a ordem alfabética
void inserir(Lista * consultas, Consulta * consulta, Relatorio * relatorio) {
    No * novo = (No*) malloc(sizeof(No));
    novo->consulta = consulta;
   
    // Caso a lista esteja vazia 
    if (consultas->primeiro == NULL) {
        consultas->primeiro = novo;
        consultas->primeiro->proximo = consultas->primeiro;
        return;
    }
   
    String entrada, pacienteAtual;
    criptografia(consulta->paciente, relatorio->inversa, entrada);
    
    No * atual = consultas->primeiro;
    criptografia(atual->consulta->paciente, relatorio->inversa, pacienteAtual);

    // Caso o nome deva ser inserido antes do primeiro
    if (nomeMaior(pacienteAtual, entrada)) {
        // Percorre até o final da lista, que aponta para seu começo
        while (atual->proximo != consultas->primeiro)
           atual = atual->proximo;

        // Altera as valores apontados para alocar o novo registro na
        // primeira posição e mudar o apontador da última para a nova primeira
        atual->proximo = novo;
        novo->proximo = consultas->primeiro;
        consultas->primeiro = novo; 
        return;
    }

    zerar(pacienteAtual);
    criptografia(atual->proximo->consulta->paciente, relatorio->inversa, pacienteAtual);
    
    /* Casos onde há parada, caso tenha-se chegado ao fim da lista ou tenha-se
     * encontrado um nome maior que a entrada na posição atual, é o lugar para se
     * alocar o mais novo registro para a listagem */
    while (atual->proximo != consultas->primeiro && !nomeMaior(pacienteAtual, entrada)) {
        atual = atual->proximo;
        zerar(pacienteAtual);
        criptografia(atual->proximo->consulta->paciente, relatorio->inversa, pacienteAtual);
    }

    // Coloca o novo registro entre o próximo e o atual
    novo->proximo = atual->proximo;
    atual->proximo = novo;
}

// Remove um registro da listagem que contém o nome do paciente passado no parâmetro
void remover(Lista * consultas, String paciente, Relatorio * relatorio) {
    // Deletando quando há apenas um registro na lista
    if (consultas->primeiro == consultas->primeiro->proximo) {
        consultas->primeiro = NULL;
        return;
    }

    String entrada, pacienteAtual;
    criptografia (paciente, relatorio->chave, entrada);

    No * atual = consultas->primeiro;
    strcpy(pacienteAtual, atual->consulta->paciente);

    // Primeiro registro para ser deletado
    if (iguais(entrada, pacienteAtual)) {
        while (atual->proximo != consultas->primeiro)
            atual = atual->proximo;
       
        // Percorre até o final e atualiza a lista retirando o primeiro 
        // elemento dela e apontando para o novo primeiro 
        No * novoPrimeiro = consultas->primeiro->proximo;
        atual->proximo = novoPrimeiro;
        consultas->primeiro = novoPrimeiro;
        return;
    }

    strcpy(pacienteAtual, atual->proximo->consulta->paciente);
   
    // Enquanto não encontrou o nome passado na entrada, procura nos próximos
    // elementos da lista  
    while (!iguais(entrada, pacienteAtual)) {
        atual = atual->proximo;
        strcpy(pacienteAtual, atual->proximo->consulta->paciente);
    }

    // Pula o registro que se deseja deletar pelos apontadores
    atual->proximo = atual->proximo->proximo;
}

// Imprime na tela um registro de consulta na ordem
// Nome(descriptografado) , data , Códigoi Doença , CRM Médico
void imprimeConsulta(Consulta * consulta, Relatorio * relatorio) {
    String descript;
    criptografia(consulta->paciente, relatorio->inversa, descript);

    printf("%s %s %s %s\n", descript, consulta->data, consulta->diagnostico, consulta->crmMedico);
}

// Lista todas as consultas a partir da letra preferida para o relatório
// Passada na entrada
void listarConsultas(Lista * consultas, Relatorio * relatorio) {
    No * atual, 
       * comecoListagem;

    char letraInicial;
    String descript;

    for (atual = consultas->primeiro;; atual = atual->proximo) {
        zerar(descript);
        criptografia(atual->consulta->paciente, relatorio->inversa, descript);

        letraInicial = descript[0];

        // Caso tenha encontrado o começo do relatório
        if (letraInicial >= relatorio->letraPreferida) {
            comecoListagem = atual;
            break;
        }
    }

    // Imprime todas as consultas
    for (;;) {
        imprimeConsulta(atual->consulta, relatorio);

        atual = atual->proximo;
        
        //Caso tenha voltado ao começo, acabou a listagem
        if (atual == comecoListagem)
            break;
    }
}

// Retorna um ponteiro para a estrutura de Médico que possue o nome
// passado pelo parâmetro para alterações nas consultas
Medico* encontrarMedico(String nome, Medico * medicos) {
    for (int i = 0;;i++) {
        if (iguais(medicos[i].nome, nome))
            return &medicos[i];
    }
    
    return NULL;
}

// Retorna um ponteiro para a estrutura de doença que possue o nome
// passado pelo parâmetro para alterações nas consultas
Doenca* encontrarDoenca(String nome, Doenca * doencas) {
    for (int i = 0;;i++) {
        if (iguais(doencas[i].nome, nome))
            return &doencas[i];
    }
    
    return NULL;
}

// Busca pela consulta desejada a partir do nome do paciente buscado
Consulta* encontrarConsulta(Lista * consultas, String buscado, Relatorio * relatorio) {
    No * atual = consultas->primeiro;

    String entrada, pacienteAtual;
    criptografia (buscado, relatorio->chave, entrada);

    strcpy(pacienteAtual, atual->consulta->paciente);
   
    // Enquanto não foi encontrado, deve-se continuar para frente,
    // atualizando o valor de atual e comparando com a entrada
    while (!iguais(entrada, pacienteAtual)) {
        atual = atual->proximo;
        strcpy(pacienteAtual, atual->consulta->paciente);
    }

    return atual->consulta;
}

// Faz a leitura de uma nova operação do sistema
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

// Função que controla o fluxo da lista de consultas, lendo cada uma das operações e aplicando-nas
// a lista de consulta até encontrar o "0", que significa o final das operações
void aplicarOperacoes(Lista * consultas, Relatorio * relatorio, Doenca * doencas, Medico * medicos) {
    Operacao op;
    String nome, novoValor;
    Consulta * buscada;
    Doenca * doenca;
    Medico * medico;
    
    for (;;) {
        definirOperacao(op);

        // Caso tenha lido "0", encerram-se as operacões nas consultas
        if (iguais(FIM_OPERACOES, op))
            break;

        // Faz o fluxo de inserir, lendo todos os dados do novo paciente
        if (iguais(INSERIR, op)) {
            Consulta * consulta = (Consulta*) malloc (sizeof(Consulta));
           
            lerTexto(consulta->paciente, TAMANHO_NOME, ESPACO);
            lerTexto(consulta->data, TAMANHO_DATA, ESPACO);
            lerTexto(consulta->diagnostico, TAMANHO_CID, ESPACO);
            lerTexto(consulta->crmMedico, TAMANHO_CRM, FIM_LINHA);
           
            inserir(consultas, consulta, relatorio);
        } 

        // Faz o fluxo de remover, lendo apenas o nome do paciente
        if (iguais(REMOVER, op)) {
            lerTexto(nome, TAMANHO_NOME, FIM_LINHA);
            remover(consultas, nome, relatorio);
        }

        // Faz o fluxo de alterar a data, lendo o nome do paciente e a nova data da consulta
        if (iguais(ALTERAR_DATA, op)) {
            lerTexto(nome, TAMANHO_NOME, ESPACO);
            lerTexto(novoValor, TAMANHO_DATA, FIM_LINHA);

            buscada = encontrarConsulta(consultas, nome, relatorio);
            strcpy(buscada->data, novoValor);
        }
        
        // Faz o fluxo de alterar o diagnóstico de um paciente, lendo o nome e o novo diagnóstico
        if (iguais(ALTERAR_DOENCA, op)) {
            lerTexto(nome, TAMANHO_NOME, ESPACO);
            lerTexto(novoValor, TAMANHO_NOME, FIM_LINHA);
           
            // Encontra a doença a partir de seu nome para obter seu CID e alterar 
            // esse valor na consulta do paciente desejado 
            doenca = encontrarDoenca(novoValor, doencas);
            buscada = encontrarConsulta(consultas, nome, relatorio);
            strcpy(buscada->diagnostico, doenca->codigo);
        }   

        // Faz o fluxo de alterar um médico de uma consulta, lendo o nome do paciente e o nome do médico
        if (iguais(ALTERAR_MEDICO, op)) {
            lerTexto(nome, TAMANHO_NOME, ESPACO);
            lerTexto(novoValor, TAMANHO_NOME, FIM_LINHA);
           
            // Encontra o médico que possui aquele nome para obter seu CRM e alterar esse valor
            // Na consulta do paciente desejado
            medico = encontrarMedico(novoValor, medicos);
            buscada = encontrarConsulta(consultas, nome, relatorio);
            strcpy(buscada->crmMedico, medico->crm);
        }
    }
}
