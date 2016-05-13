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

Genero decideGeneroPorCaracter (char caracter) {
    if (caracter == 'F') {
        return Feminino;
    }

    return Masculino;
}

Genero lerGenero() {
    char caracter;
    scanf("%c ", &caracter);
    return decideGeneroPorCaracter(caracter);
}

int main() {

    return 0;
}
