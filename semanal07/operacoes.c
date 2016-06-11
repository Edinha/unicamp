#include "operacoes.h"

char letraTabelaPeloNumero (int num) {
    return (char) num + 'A';
}

int numeroPelaLetraTabela (char letra) {
    return (letra - 'A');
}

unsigned char iguais (char entrada[], char procurado[]) {
    return !strcmp(entrada, procurado);
}

unsigned char nomeMaior (String nome, String comparado) {
    int comparacao = strcmp (nome, comparado);

    if (comparacao > 0)
        return MAIOR;

    return MENOR;
}

int determinante (Chave chave) {
    int det = 0;

    det += chave[0][0] * chave[1][1];
    det -= chave[1][0] * chave[0][1];

    return det;
}

// Retorna o primeiro i encontrado a partir de 1 que satisfaz (det * i) % 26 == 1 
int numeroInversoComModulo26 (int det) {
    for (int i = 1;; i++) {
        if ( (i * det) % 26 == 1) {
            return i;
        }
    }
    
    return -1;
}

// Calcula o módulo da multiplicação entre os os parâmetros
int calcMod (int num, int numChave) {
    int mult = num * numChave,
        mod  = mult % MODULO;

    /* Caso seja negativo, deve-se adicionar o número usado para modular
     * uma vez em ordem de manter o resultado esperado, pois o operadoe
     * modular do C (%) cálcula módulos a partir de divisões inteiras */
    if (mod < 0)
        mod += MODULO;

    return mod;
}

void chaveInversa(Chave chave, Chave inversa) {
    int numInverso = numeroInversoComModulo26 (determinante(chave));
    
    inversa[0][0] = calcMod( numInverso, chave[1][1]);
    inversa[1][1] = calcMod( numInverso, chave[0][0]);
    inversa[0][1] = calcMod(-numInverso, chave[0][1]);
    inversa[1][0] = calcMod(-numInverso, chave[1][0]);
}

void multiplicarMatrizes (Chave chave, int matriz[]) {
    int prim = matriz[0],
        seg  = matriz[1];

    matriz[0] = prim * chave[0][0] + seg * chave[0][1];
    matriz[1] = prim * chave[1][0] + seg * chave[1][1];

    matriz[0] %= MODULO;
    matriz[1] %= MODULO;
}

void criptografia(String entrada, Chave chave, String descript) {
    int matriz[DIMENSAO_MATRIZ];
    for (unsigned char i = 0; i < TAMANHO_NOME; i += 2) {
        if (entrada[i] == FIM_STRING) {
            descript[i] = FIM_STRING;
            break;
        }
        
        //printf("Letras : %c %c", entrada[i], entrada[i+1]);

        matriz[0] = numeroPelaLetraTabela(entrada[i]);
        matriz[1] = numeroPelaLetraTabela(entrada[i+1]);

        //printf(" Multiplicando...");
        multiplicarMatrizes (chave, matriz);

        descript[i]   = letraTabelaPeloNumero(matriz[0]);
        descript[i+1] = letraTabelaPeloNumero(matriz[1]);
        //printf(" Decriptografado!\n");
    }
}

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

void remover(Lista * consultas, Consulta * consulta, Relatorio * relatorio) {
    // Deletando quando há apenas um registro na lista
    if (consultas->primeiro == consultas->primeiro->proximo) {
        consultas->primeiro = NULL;
        return;
    }

    String entrada, pacienteAtual;
    criptografia (consulta->paciente, relatorio->chave, entrada);

    No * atual = consultas->primeiro;
    strcpy(pacienteAtual, atual->consulta->paciente); //criptografia (atual->consulta->paciente, relatorio->chave, pacienteAtual);

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

void alteraData(Consulta * consulta, Data data) {
    // TODO
}

void alteraMedico(Consulta * consulta, Medico* medico) {
    // TODO
}

void alteraDiag(Consulta * consulta, Doenca* doenca) {
    // TODO
}

// Retorna um ponteiro para a estrutura de Médico que possue o nome
// passado pelo parâmetro para alterações nas consultas
Medico* encontrarMedico(String nome, Medico * medicos) {
    for (unsigned char i = 0;;i++) {
        if (iguais(medicos[i].nome, nome))
            return &medicos[i];
    }
    
    return NULL;
}

// Retorna um ponteiro para a estrutura de doença que possue o nome
// passado pelo parâmetro para alterações nas consultas
Doenca* encontrarDoenca(String nome, Doenca * doencas) {
    for (unsigned char i = 0;;i++) {
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
    
    while (!iguais(entrada, pacienteAtual)) {
        atual = atual->proximo;
        strcpy(pacienteAtual, atual->consulta->paciente);
    }

    return atual->consulta;
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
    String busca;
    Consulta * buscada;
    Doenca * doenca;
    Medico * medico;

    for (;;) {
        Consulta * consulta = (Consulta*) malloc (sizeof(Consulta));
        definirOperacao(op);

        // Caso tenha lido "0", encerram-se as operacões nas consultas
        if (iguais(FIM_OPERACOES, op))
            break;

        if (iguais(INSERIR, op)) {
            lerTexto(consulta->paciente, TAMANHO_NOME, ESPACO);
            lerTexto(consulta->data, TAMANHO_DATA, ESPACO);
            lerTexto(consulta->diagnostico, TAMANHO_CID, ESPACO);
            lerTexto(consulta->crmMedico, TAMANHO_CRM, FIM_LINHA);
           
            inserir(consultas, consulta, relatorio);
        } 

        if (iguais(REMOVER, op)) {
            lerTexto(consulta->paciente, TAMANHO_NOME, FIM_LINHA);
            remover(consultas, consulta, relatorio);
        }

        if (iguais(ALTERAR_DATA, op)) {
            lerTexto(consulta->paciente, TAMANHO_NOME, ESPACO);
            lerTexto(busca, TAMANHO_DATA, FIM_LINHA);

            buscada = encontrarConsulta(consultas, consulta->paciente, relatorio);
            strcpy(buscada->data, busca);
        }
        
        if (iguais(ALTERAR_DOENCA, op)) {
            lerTexto(consulta->paciente, TAMANHO_NOME, ESPACO);
            lerTexto(busca, TAMANHO_NOME, FIM_LINHA);
            
            doenca = encontrarDoenca(busca, doencas);
            buscada = encontrarConsulta(consultas, consulta->paciente, relatorio);
            strcpy(buscada->diagnostico, doenca->codigo);
        }   

        if (iguais(ALTERAR_MEDICO, op)) {
            lerTexto(consulta->paciente, TAMANHO_NOME, ESPACO);
            lerTexto(busca, TAMANHO_NOME, FIM_LINHA);
           
            medico = encontrarMedico(busca, medicos);
            buscada = encontrarConsulta(consultas, consulta->paciente, relatorio);
            strcpy(buscada->crmMedico, medico->crm);
        }

    }
}
