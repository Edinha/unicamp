// Nome  : William Gonçalves da Cruz
// RA    : 188671
// Turma : W

/* Lab Semanal : Melhor funcionário do mês
 * 
 * O objetivo do desenvolvimento desse lab é um algoritmo que retorne o funcionário mais produtivo de uma empresa em sua hieraquia.
 * Para isso, existem algumas informações e fórmulas a serem aplicadas para mensurar a produtividade de cada funcionário.
 * Cada funcionário possui uma produtividade absoluta, porém sua produtividade é medida pela fórmula de produtividade relativa.
 *      - Caso um funcionário não tem subordinados, a relativa é igual a sua absoluta;
 *      - Meio vezes a soma entre a produtividade absoluta com 1 sobre o conjunto das produtividades de seus subordinados mais
 *        a somatória das produtividades relativas de seus subordinados;
 *
 * O salário de cada funcionário também é calculado com base na hierarquia da empresa;
 *      - Se a pessoa é o CEO, o seu salário é igual a constante de entrada;
 *      - Senão, è o conjunto dos subordinados do chefe da pessoa sobre conjunto dos suboridinados mais 1 vezes o salário do chefe;
 *
 * O nível hierárquico de uma pessoa é definido por sua distância a presidência mais um;
 *
 * Log Asterisco é um função com um parâmetro numérico (x) definida como: 
 *      - Se x for menor ou igual a 1 (um), retorna 0 (zero);
 *      - Senão, retorna um mais a própria função, com o parâmetro log 2 (x);
 *
 * Por fim, temos o cálculo do indice de qualidade, o índice que sera usado para comparação entre funcionários;
 *      - Fator (Fornecido para o programa como entrada) vezes a função log asterisco do nível da pessoa mais um, vezes
 *        a produtividade relativa do funcionário sobre log 2 do salário da pessoa;
 */

#include <stdio.h>
#include <math.h>
#include <string.h>

#define SEM_VALOR -1
#define ZERAR 0
#define MEIO 0.5
#define TAMANHO_NOME 30
#define MAX_FUNCIONARIOS 100

typedef char string[TAMANHO_NOME];

typedef
    struct {
        string nome;
        unsigned char produtividade;

        unsigned char posChefe;
        unsigned char qtdSubordinados;
        unsigned char subordinados[MAX_FUNCIONARIOS - 1];
    } Funcionario;


// Lê uma string e armazena no parâmetro string s
void lerString (string s) {
    scanf("%s", s);
}

// Lê a entrada real do programa (Total gasto com salário)
void lerReal (double * d) {
    scanf("%lf ", d);
}

// Lê o fator de entrada (Segunda linha da entrada)
void lerFator (long * fator) {
    scanf("%li ", fator);
}

// Lê as entradas que possuem números de 0 até 100 (número de funcionários e a produtividade absoluta)
void lerNumero (unsigned char * n) {
    scanf("%hhu ", n);
}

// Função que a partir de um funcionário, inicializa os campos que mantém a relação
// de chefia e subordinação daquele funcionário para uso posterior
void inicializarHierarquiaParaFuncionario (Funcionario * funcionario) {

    funcionario->qtdSubordinados = ZERAR;
    funcionario->posChefe = SEM_VALOR;

    for (unsigned char i = 0; i < MAX_FUNCIONARIOS - 1; i++) {
        funcionario->subordinados[i] = SEM_VALOR;   
    }
}

// Lê uma entrada de funcionário (nome e produtividade absoluta)
void lerFuncionario (Funcionario * funcionario) {
    lerString(funcionario->nome);
    lerNumero(&funcionario->produtividade);
}

// Lê todos os funcionários da entrada
void lerFuncionarios (Funcionario funcionarios[], unsigned char qtd) {
    Funcionario * atual;
    
    for (unsigned char i = 0; i < qtd; i++) {
        
        atual = &funcionarios[i];
        
        lerFuncionario(atual);
        inicializarHierarquiaParaFuncionario(atual);
    }
}

// Compara duas strings e retorna verdadeiro (diferente 0) se são iguais, falso (0) se são diferentes
unsigned char nomesIguais (string prim, string seg) {
    unsigned char comparacao;

    comparacao = strcmp (prim, seg);

    return (comparacao == 0);
} 

// Retorna a posição que o funcionário ocupa no vetor de registros a partir de seu nome
unsigned char posicaoFuncionarioPeloNome (string nome, Funcionario funcionarios[], unsigned char qtd) {

    for (unsigned char i = 0; i < qtd; i++) {
               
        if (nomesIguais(nome, funcionarios[i].nome)) {
            return i;
        }
    }

    return SEM_VALOR;
}

// Atualiza o registro daquele funcionário para guardar a posição de seu mais novo subordinado 
// direto em seu vetor de posições dos subordinados
void adicionaSubordinadoAoChefe (Funcionario * chefe, unsigned char posSubordinado) {
    unsigned char indice = chefe->qtdSubordinados;

    chefe->subordinados[indice] = posSubordinado;
    chefe->qtdSubordinados++;
}

// Atualiza o registro do funcionário para armazenar a posição no vetor de registro de seu chefe direto
void adicionaChefeAoSubordinado (Funcionario * subordinado, unsigned char posChefe) {
    subordinado->posChefe = posChefe;
}

// Atualiza o vetor de registros com uma nova relação de subordinação lida pela entrada
void montarRelacaoChefeSubordinado (Funcionario funcionarios[], unsigned char posChefe, unsigned char posSubordinado) {
    
    Funcionario * chefe = &funcionarios[posChefe];
    Funcionario * subordinado = &funcionarios[posSubordinado];
    
    adicionaSubordinadoAoChefe (chefe, posSubordinado);    
    adicionaChefeAoSubordinado (subordinado, posChefe);
}

// Monta a hierarquia da empresa a partir da entrada
void montarHierarquia (Funcionario funcionarios[], unsigned int qtd) {

    string nomeChefe;
    string nomeSubordinado;

    unsigned char posChefe,
                  posSubordinado;

    for (unsigned char i = 0; i < qtd - 1; i++) {
   
        // Lê os nomes da relação atual 
        lerString(nomeSubordinado);
        lerString(nomeChefe);

        // Pega a posição de cada uma deles pela função
        posChefe = posicaoFuncionarioPeloNome (nomeChefe, funcionarios, qtd);
        posSubordinado = posicaoFuncionarioPeloNome (nomeSubordinado, funcionarios, qtd);

        // Guarda os dados da relação para o cálculo das fórmulas posteriores
        montarRelacaoChefeSubordinado (funcionarios, posChefe, posSubordinado);    
    }
}

// Comparação para saber se um funcionário possue subordinados
unsigned char semSubordinados (Funcionario * f) {
    return (f->qtdSubordinados == 0);
}

// Calcula parte da fórmula de produtividade abosula, um sobre o conjunto do funcionário
double calculoConjunto (unsigned char qtd) {
    double c = 1 / qtd;
    return c;
}

// Função que calcula a produtividade relativa de um funcionário atual
double produtividadeRelativa (Funcionario funcionarios[], Funcionario * atual) {
    unsigned 
        char i,
             posSubordinado,
             produtividade = atual->produtividade;

    Funcionario * subordinado;
    double somatoria = 0.0;

    // Caso não tenha subordinados, retorna sua própria produtividade absoluta
    if (semSubordinados(atual)) {
        return produtividade;
    }   
   
    // Itera sobre os subordinados do atual e calcula suas produtividades relativas, 
    // sendo estas adicionadas a somatoria, aplicadando, ao final, a fórmula no retorno
    for (i = 0; i < atual->qtdSubordinados; i++) {

        // Recupera o subordinado atual do funcionário a partir de sua posição 
        posSubordinado = atual->subordinados[i];
        subordinado = &funcionarios[posSubordinado];

        somatoria += produtividadeRelativa (funcionarios, subordinado);
        //printf("    Atual : %.2lf\n", somatoria);
    }

    // Aplica a fórmula de produtividade relativa
    return MEIO * (produtividade + (somatoria / atual->qtdSubordinados));
}

void print (Funcionario funcionarios[], unsigned char qtd) {
    for (int i = 0; i < qtd; i++) {
        Funcionario f = funcionarios[i];
        printf("%s ", f.nome);
        printf("%d\n    ", f.produtividade);
        for (int j = 0; j < f.qtdSubordinados; j++) 
            printf("%s ", funcionarios[f.subordinados[j]].nome);
        printf("\n\n");
    }
}

void verProdutividades (Funcionario funcionarios[], unsigned char qtd) {
    double prod;
    Funcionario * f;

    for (int i = 0; i < qtd; i++) {
        f = &funcionarios[i];
        prod = produtividadeRelativa (funcionarios, f);

        printf("%s -> %.2lf\n", f->nome, prod);
    }
}

int main() {
    unsigned char qtdFuncionarios;
    double gasto;
    long fator;

    Funcionario funcionarios[MAX_FUNCIONARIOS];

    lerReal(&gasto);
    
    lerFator(&fator);
    
    lerNumero(&qtdFuncionarios);

    lerFuncionarios(funcionarios, qtdFuncionarios);

    montarHierarquia (funcionarios, qtdFuncionarios);

    //print(funcionarios, qtdFuncionarios);
    verProdutividades(funcionarios, qtdFuncionarios);

    return 0;
}
