// Nome  : William Gonçalves da Cruz
// RA    : 188671
// Turma : W

// Lab semanal 05 - Relacionamento entre pessoas 
// 
// Trata-se de uma solução para organizar dados de relacionamentos entre pessoas. Podemos organizar a pessoa da seguinte forma
//      Pessoa : Nome, nascimento, gênero, preferência, afinidades com outras pessoas
// Para armazenar as afinidades, é utilizado o conceito de grafo, onde existe uma aresta com peso numérico que indica a afinidade entre duas estruturas de pessoas diferentes.
// Também possui a funcionalidade de encontrar a pessoa mais popular dos dados de entrada, ou seja, aquela que possui a maior afinidade com os demais colegas
// Por último, há o cálculo de da sintonia entre pessoas por numerologia, afim de encontrar o "par perfeito"

#include <stdio.h>
#include <math.h>

#define TAMANHO_NOME 200
#define QUANTIDADE_MAXIMA_ALUNOS 40

// O número máximo de arestas é definido a partir de um número n de vértices pela fórmula :
//     n * (n - 1) / 2
#define NUMERO_ARESTAS QUANTIDADE_MAXIMA_ALUNOS * (QUANTIDADE_MAXIMA_ALUNOS - 1) / 2

// Definindo as estruturas utilizáveis pelo programa
typedef char string[TAMANHO_NOME]; 

typedef
    enum {
        Masculino, Feminino
    } Genero;

typedef
    struct {
        unsigned char dia, mes, ano;
    } Data;

typedef 
    struct {
        string nome;
        Data nascimento;
        Genero pessoal;
        Genero preferencia;
        unsigned char afinidades[QUANTIDADE_MAXIMA_ALUNOS];
    } Pessoa;

typedef
    struct {
        Pessoa * parceiro;
        Pessoa * companheiro;
        double afinidade;
    } Aresta;

typedef 
    struct {
        Aresta arestas[NUMERO_ARESTAS];     
    } Grafo;

// Lê uma string e armazena no parâmetro string s
void lerString(string s) {
    scanf(" %[^\n]s", s);
}

// TODO caso exploda com int
// Lê uma entrada numérica do programa
void lerNumero (unsigned char * numero) {
    scanf("%hhu", numero);
}

// Lê um número inteiro no endereço passado como parâmetro
void lerInteiro(int * inteiro) {
    scanf("%d", inteiro);
}

// Lê uma entrada no formato da estrutura de data
Data lerData() {
    Data data;
    scanf("%hhu/%hhu/%hhu ", &data.dia, &data.mes, &data.ano);
    //scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);
    return data;   
}

// A partir dos carácteres 'F' ou 'M' decide o  gênero a ser devolvido
Genero decideGeneroPorCaracter (char caracter) {
    if (caracter == 'F') {
        return Feminino;
    }

    return Masculino;
}

// Lê um gênero de entrada
Genero lerGenero() {
    char caracter;
    scanf("%c ", &caracter);
    return decideGeneroPorCaracter(caracter);
}

// Compara duas posições passadas por parâmetro, retornando verdadeiro se forem a mesma
int mesmaPosicaoDaPessoa (int posicaoAtual, int posicaoPessoa) {
    return (posicaoAtual == posicaoPessoa);
} 

// A partir de um vetor de afinidades para a pessoa passado, lê a entrada e armazena no vetor
void popularAfinidadesDaPessoa (unsigned char afinidades[], unsigned char quantidade, int posicao) {
    for (int i = 0; i < quantidade; i++) {
        // caso seja a posição da própria pela ela não avalia sua afinidade com ela mesma, então é pulada
        if (mesmaPosicaoDaPessoa (posicao, i) ) {
            continue;
        }

        lerNumero (&afinidades[i]);
    }
} 

// Lê os campos para uma pessoa exceto suas afinidades
void lerPessoa (Pessoa * pessoa) {

    lerString( (*pessoa).nome);
    
    (*pessoa).nascimento = lerData();
    (*pessoa).pessoal = lerGenero();
    (*pessoa).preferencia = lerGenero();
} 

char getChar (Genero g) {
    if (g == Masculino)
        return 'M';

    return 'F';
}

void printarPessoa (Pessoa pessoa) {
    printf("%s\n", pessoa.nome);
    printf("%d/%d/%d\n", pessoa.nascimento.dia, pessoa.nascimento.mes, pessoa.nascimento.ano);
    printf("%c %c\n", getChar(pessoa.pessoal), getChar(pessoa.preferencia));
    
    for (int i = 0; i < QUANTIDADE_MAXIMA_ALUNOS; i++)
        printf("%d ", pessoa.afinidades[i]);

    printf("\n");
}    

// Dado um vetor de pessoas, lê toda a entrada do programa
void lerPessoas (Pessoa pessoas[], unsigned char quantidade) {
    for (int i = 0; i < quantidade; i++) {
        lerPessoa (&pessoas[i]);
        popularAfinidadesDaPessoa(pessoas[i].afinidades, quantidade, i);
        printarPessoa(pessoas[i]);
    }
}

// Média geométrica entre dois valores é a raiz quadrada da multiplicação entre eles 
double mediaGeometrica (int valor, int fator) {
    double media = sqrt (valor * fator);
    return media;
} 

int main() {
    Data preenchimento;

    Pessoa pessoas[QUANTIDADE_MAXIMA_ALUNOS];

    unsigned char quantidade;

    preenchimento = lerData();

    lerNumero (&quantidade);

    lerPessoas(pessoas, quantidade);

    // TODO explodir isso aqui
    printf("%d", preenchimento.dia);

    return 0;
}
