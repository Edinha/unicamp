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

#define SUCESSO 1
#define FALHA 0
#define MEDIA_MINIMA_AFINIDADE 5

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
void lerData(Data * data) {
    scanf("%hhu/%hhu/%hhu ", &data->dia, &data->mes, &data->ano);
    //scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);   
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

    lerString(pessoa->nome);
    
    lerData(&pessoa->nascimento);
    pessoa->pessoal = lerGenero();
    pessoa->preferencia = lerGenero();
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
double mediaGeometrica (unsigned char valor, unsigned char fator) {
    return sqrt ( valor * fator);
} 

int ponteirosParaPessoasIguaisNaAresta (Pessoa * a, Pessoa * b, Aresta aresta) {
    if (aresta.parceiro == a && aresta.companheiro == b) {
        return SUCESSO;
    }

    return FALHA;
} 

int jaExisteArestaEntrePessoasNaPosicao (Pessoa * parceiro, Pessoa * companheiro, Aresta arestas[], int posicao) {
    
    if ( ponteirosParaPessoasIguaisNaAresta (parceiro, companheiro, arestas[posicao]) ) {
        return SUCESSO;
    }

    if ( ponteirosParaPessoasIguaisNaAresta (companheiro, parceiro, arestas[posicao])  ) {
        return SUCESSO;
    }

    return FALHA;
}

double existeArestaEntrePessoas (Pessoa * parceiro, int posicaoParceiro, Pessoa * companheiro, int posicaoCompanheiro, Aresta arestas[]) {

    double mediaNotas = mediaGeometrica ( parceiro->afinidades[posicaoCompanheiro] , companheiro->afinidades[posicaoParceiro]);

    if (mediaNotas < MEDIA_MINIMA_AFINIDADE) {
        return FALHA;
    }

    for (int i = 0; i < NUMERO_ARESTAS; i++) {
        if (jaExisteArestaEntrePessoasNaPosicao (parceiro, companheiro, arestas, i) ) {
            return FALHA;
        }
    }

    return mediaNotas;
} 

int montarGrafo (Grafo * grafo, Pessoa pessoas[], unsigned char quantidade) {

    int posAresta = 0;

    for (int i = 0; i < quantidade; i++) {
        
        for (int pos = 0; pos < quantidade; pos++) {
            if (mesmaPosicaoDaPessoa(i, pos)) {
                continue;
            }

            double afinidade = existeArestaEntrePessoas (&pessoas[i], i, &pessoas[pos], pos, grafo->arestas);

            // Se existe afinidade entre as pessoas possível para formar aresta
            if ( afinidade ) {
                
                grafo->arestas[posAresta].parceiro = &pessoas[i];
                grafo->arestas[posAresta].companheiro = &pessoas[pos];
                grafo->arestas[posAresta].afinidade = afinidade; 

                posAresta++;   
            }
        }

    }

    return posAresta;
}

void imprimirArestas (Aresta arestas[], int qtd) {

    for (int i = 0; i < qtd; i++) {
        printf ("Nome : %s\n", arestas[i].parceiro->nome);
        printf ("Nome : %s\n", arestas[i].companheiro->nome);
        printf ("Afin : %f\n\n", arestas[i].afinidade);
    }
} 

int main() {
    Data preenchimento;

    Pessoa pessoas[QUANTIDADE_MAXIMA_ALUNOS];

    Grafo grafo;

    unsigned char quantidade;

    int tamanhoGrafo;

    lerData(&preenchimento);

    lerNumero (&quantidade);

    lerPessoas(pessoas, quantidade);

    tamanhoGrafo = montarGrafo ( &grafo, pessoas, quantidade);

    imprimirArestas (grafo.arestas, tamanhoGrafo);

    // TODO explodir isso aqui
    printf("%d", preenchimento.dia);

    return 0;
}
