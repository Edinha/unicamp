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
        double afinidade;
    } Aresta;

typedef
    struct {
        Pessoa * pessoa;
        Aresta  amizades[QUANTIDADE_MAXIMA_ALUNOS - 1];
        unsigned char ligacoes;
    } Vertice;

typedef 
    struct {
        Vertice vertices[QUANTIDADE_MAXIMA_ALUNOS];
    } Grafo;

// Lê uma string e armazena no parâmetro string s
void lerString(string s) {
    scanf(" %[^\n]s", s);
}

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


/* TODO descomentar
 * Pega o char a partir do gênero da pessoa
char getChar (Genero g) {
    if (g == Masculino)
        return 'M';

    return 'F';
} */

// Dado um vetor de pessoas, lê toda a entrada do programa
void lerPessoas (Pessoa pessoas[], unsigned char quantidade) {
    for (int i = 0; i < quantidade; i++) {
        lerPessoa (&pessoas[i]);
        popularAfinidadesDaPessoa(pessoas[i].afinidades, quantidade, i);
    }
}

// Média geométrica entre dois valores é a raiz quadrada da multiplicação entre eles 
double mediaGeometrica (unsigned char valor, unsigned char fator) {
    return sqrt ( valor * fator);
} 

// Retorna o valor da afinidade entre as pessoas caso ela exista e ainda não tenho sido inserida na estrutura do grafo (arestas)
double existeAfinidadeEntrePessoas (Pessoa * parceiro, int posicaoParceiro, Pessoa * companheiro, int posicaoCompanheiro) {

    double mediaNotas = mediaGeometrica ( parceiro->afinidades[posicaoCompanheiro] , companheiro->afinidades[posicaoParceiro]);

    // Caso seja menor que 5 não há aresta entre as pessoas
    if (mediaNotas < MEDIA_MINIMA_AFINIDADE) {
        return FALHA;
    }

    return mediaNotas;
} 

void imprimirGrafo (Grafo * grafo, unsigned char qtd) {
    int a;
    for (int i = 0; i < qtd; i++) {
        printf ("Pessoa Vértice : %s\n", grafo->vertices[i].pessoa->nome);
        printf ("Ligacoes : %d\n", grafo->vertices[i].ligacoes);    

        a = grafo->vertices[i].ligacoes;
        for (int j = 0; j < a; j++) {
            Aresta ar = grafo->vertices[i].amizades[j];
            printf ("   Pessoa %s   Afinidade : %f\n", ar.parceiro->nome, ar.afinidade);
        }
            
        printf("\n"); 
    } 
}

// A partir das pessoas, monta as arestas daquele vértice e retorna o número de arestas
unsigned char montarArestas (Aresta arestas[], int i, Pessoa pessoas[], unsigned char quantidade) {

    unsigned char qtdArestas = 0;

    for (int pos = 0; pos < quantidade; pos++) {
        if (mesmaPosicaoDaPessoa(i, pos)) {
            continue;
        }

        double afinidade = existeAfinidadeEntrePessoas (&pessoas[i], i, &pessoas[pos], pos);
    
        if ( afinidade ) {
            arestas[qtdArestas].parceiro = &pessoas[pos];
            arestas[qtdArestas].afinidade = afinidade;
            qtdArestas++;
        } 
    }

    return qtdArestas;
}

// Monta a estrutura do grafo 
void montarGrafo (Grafo * grafo, Pessoa pessoas[], unsigned char quantidade) {

    for (int i = 0; i < quantidade; i++) {
        grafo->vertices[i].pessoa = &pessoas[i];

        grafo->vertices[i].ligacoes = montarArestas( grafo->vertices[i].amizades, i, pessoas, quantidade);    
    }
}

int main() {
    Data preenchimento;

    Pessoa pessoas[QUANTIDADE_MAXIMA_ALUNOS];

    Grafo grafo;

    unsigned char quantidade;

    lerData(&preenchimento);

    lerNumero (&quantidade);

    lerPessoas(pessoas, quantidade);

    montarGrafo ( &grafo, pessoas, quantidade);

    imprimirGrafo ( &grafo, quantidade);
    //imprimirArestas (grafo.arestas, tamanhoGrafo);

    // TODO explodir isso aqui
    printf("%d", preenchimento.dia);

    return 0;
}
