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
        int dia, mes, ano;
    } Data;

typedef 
    struct {
        string nome;
        Data nascimento;
        Genero pessoal;
        Genero preferencia;
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

int main() {

    return 0;
}
