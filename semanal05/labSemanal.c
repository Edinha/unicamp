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

#define TAMANHO_CODINOME 4
#define TAMANHO_NOME 200
#define QUANTIDADE_MAXIMA_ALUNOS 40

// Definindo as estruturas utilizáveis pelo programa
typedef char string[TAMANHO_NOME]; 
typedef char codinome[TAMANHO_CODINOME];

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
        Pessoa * sintonizado;
        double sintonia;
    } Par;

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

// Retorna o vértice onde está a pessoa mais popular
Vertice* pessoaMaisPopular (Grafo * grafo, unsigned char quantidade) {
    unsigned char maiorNumeroLigacoes = 0;
    Vertice* maisPopular;

    for (int i = 0; i < quantidade; i++) {
        if (grafo->vertices[i].ligacoes > maiorNumeroLigacoes) {
            maiorNumeroLigacoes = grafo->vertices[i].ligacoes;
            maisPopular = &grafo->vertices[i];
        }
    }

    return maisPopular;
}

// TODO melhorar se possível
unsigned char numeroPelaConsoante (char c) {
    if (c == 'g' || c == 'j')
        return 1;
    
    if (c == 's' || c == 'z' || c == 'x')
        return 2;
    
    if (c == 'c' || c == 'k' || c == 'q')
        return 3;

    if (c == 'b' || c == 'p')
        return 4;

    if (c == 'm' || c == 'n')
        return 5;

    if (c == 'd' || c == 't')
        return 6;

    if (c == 'f' || c == 'v')
        return 7;

    if (c == 'l')
        return 8;

    if (c == 'r')
        return 9;

    return 0;
} 

int naoVogal (char letra) {
    if (letra == 'a' || letra == 'e' || letra == 'i' ||
        letra == 'o' || letra == 'u') {
            return FALHA;
    }
    
    return SUCESSO;
}

// Transforma o número passado por parâmetro no seu respectivo caracter ASCII
char charPeloNumero (unsigned char numero) {
    char c = (char) (numero + 48);
    return c;
}

void gerarCodinome (codinome codigo, string nome) {
    unsigned char numeros[TAMANHO_CODINOME - 1],
                  atual, i,
                  contador = 0;

    // Atribue a primeira letra ao codinome
    codigo[0] = nome[0];

    for (i = 1; ; i++) {
        char letra = nome[i];
             
        // Codifica apenas o primero nome, quando chega ao caracter espaço, chegou ao fim do primero fim
        if (letra == ' ')
            break;

        if (naoVogal(letra)) {
            atual = numeroPelaConsoante (letra); 
           
            // Condições para se adicionar um número ao codinome 
            if ( (contador == 0) || (contador > 0 && numeros[contador - 1] != atual) ) {
                numeros[contador] = atual;
                codigo[i] = charPeloNumero (atual);
                contador++;
            } 

            // Caso já tenha contabilizado o codinome completo
            if (contador >= TAMANHO_CODINOME - 1) 
                break;
        }
    }

    for (i = contador; i < TAMANHO_CODINOME - 1; i++)
       codigo[i] = '0';

}

// Dada uma data dd/mm/yyyy retorna um número no formato yyyymmdd
int formatarData (Data * data) {
    int num = data->ano;
    num = num * 100 + data->mes;
    num = num * 100 + data->dia;
    return num;
}

// Calcula a idade a partir da formatação de duas datas
// Logo após, subtrai os resultados e elimina os 4 ultimos dígitos para conseguir a idade
int idade (Data * nascimento, Data * atual) {
    int nasc = formatarData (nascimento),
        hoje = formatarData (atual);

    return (hoje - nasc) / 10000;
}

// retorna a similaridade entre 2 codinomes pelos seus caracteres
double similaridade (codinome prim, codinome seg) {
    unsigned char i, qtd = 0;

    for (i = 0; i < TAMANHO_CODINOME; i++)
        if (prim[i] == seg[i])
            qtd++;

    return qtd / 4.0;
}

// Retorna a similaridade entre dois números por seus dígitos
double similaridadeNumerica (int prim, int seg) {
    unsigned char i, qtd = 0;
 
    for (i = 0; i < TAMANHO_CODINOME - 1; i++) {
        // Quando o ultimo digito é igual
        if ( prim % 10 == seg % 10 ) 
            qtd++;

        prim = prim / 10;
        seg  = seg / 10;
    }

    return qtd / 3.0;   
}

// Calcula a numerologia a partir de uma data
int numerologia (Data * data) {
    int diaMes = data->dia + data->mes,
        ano = data->ano,
        contAno,
        numero,
        final;

    for (contAno = 0; ano != 0; ano = ano / 10) 
        contAno += ano % 10;

    diaMes += contAno;

    for (numero = 0; diaMes != 0; diaMes /= 10) 
        numero += diaMes % 10;

    for (final = 0; numero != 0; numero /= 10) 
        final += numero;
    
    return final;
}

// Calcula a sintonia entra duas pessoas
double sintonia (Pessoa * popular, Pessoa * parceiro, Data * hoje, double afinidade) {
    int idadePopular  = idade (&popular->nascimento, hoje),
        idadeParceiro = idade (&parceiro->nascimento, hoje),
        numPopular = numerologia (&popular->nascimento),
        numParceiro = numerologia (&parceiro->nascimento),

        // Multiplicar po 100 para deslocar duas casas para esquerda
        codNascPop = numPopular * 100 + idadePopular,
        codNascParc = numParceiro * 100 + idadeParceiro;

    codinome pop, parc;

    gerarCodinome (pop, popular->nome);
    gerarCodinome (parc, parceiro->nome);

    double primFator = 3 * similaridade (pop, parc),
           segFator = 5 * similaridadeNumerica (codNascPop, codNascParc),
           tercFator = 2 * (afinidade / 10);

    return (primFator + segFator + tercFator) / 10.0;
}

// Encontra o par perfeito a partir do vertice da pessoa mais popular
Par encontrarParPerfeito (Vertice * vertice, Data * hoje) {
    Par par;
    
    Pessoa * popular = vertice->pessoa,
           * outra,
           * parPerfeito;

    double maiorSintonia = 0.0,
           atualSintonia,
           afinidade;

    for (int i = 0; i < vertice->ligacoes; i++) {
        outra     = vertice->amizades[i].parceiro;
        afinidade = vertice->amizades[i].afinidade;

        atualSintonia = sintonia (popular, outra, hoje, afinidade);

        if (atualSintonia > maiorSintonia) {
            maiorSintonia = atualSintonia;
            parPerfeito = outra;
        }
    } 

    par.sintonia = maiorSintonia;
    par.sintonizado = parPerfeito;

    return par;
}

// imprime a saida do programa a partir da estrutura Par com o par perfeiro para a pessoa mais popular
void saida (Par * par, Pessoa * popular) {
    printf ("%s combina com %s com %.2f de sintonia s2\n", popular->nome, par->sintonizado->nome, par->sintonia);
}

int main() {
    Data preenchimento;

    Vertice * popular;

    Pessoa pessoas[QUANTIDADE_MAXIMA_ALUNOS];

    Grafo grafo;

    unsigned char quantidade;

    Par par;

    lerData(&preenchimento);

    lerNumero (&quantidade);

    lerPessoas(pessoas, quantidade);

    montarGrafo ( &grafo, pessoas, quantidade);

    popular = pessoaMaisPopular (&grafo, quantidade);

    par = encontrarParPerfeito (popular, &preenchimento);

    saida (&par, popular->pessoa);

    return 0;
}
