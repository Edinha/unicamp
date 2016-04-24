// Nome  : William Gonçalves da Cruz
// RA    : 188671
// Turma : W

/*  Lab Semanal 03 -> Processamento de imagem
 *
 *  O intuito desse programa é ler uma imagem que está compactada em seu formato rgb e aplicar um filtro para tal, 
 *  fazendo uma funcionalidade parecida com editores de imagem. Para tal, são usadas técnicas de convolução aplicadas
 *  a cada pixel da imagem a fim de "aplicar" o filtro desejado.
 *
 *  Entrada:
 *      Um número inteiro representando o divisor a ser usado na convolução
 *      A ordem da matriz quadrada de filtro (N) 
 *      N linhas com N números inteiros representando a matriz de filtro
 *      Dois inteiros positivos representando altura e largura
 *      Pares de números representando quantas vezes eles repetem e seu valor
 */

#include <stdio.h>

// Tamanho máximo das matrizes de imagem
#define MAX_TAM_RGB 600

// Tamanho máximo da matriz de filtro
#define MAX_TAM_FILTRO 10

void printc(unsigned char cinza[][MAX_TAM_RGB], int altura, int largura) {

    int i, j;

    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++)
            printf("%d ",  cinza[i][j]);
        printf("\n");
    }

    printf("\n");
}

// Descompacta a entrada para cada cor específica dada a quantidade de elementos e largura e altura da matriz
void descompactarParaCor(unsigned char cor[][MAX_TAM_RGB], int qtdMatriz, int largura, int altura) {
    
    int cont,
        contRepeticao,
        i,
        j;
        
    unsigned short repeticao;
    unsigned char valor;

    for (cont = 0, i = 0, j = 0; cont < qtdMatriz;) {
        
        scanf("%hu %hhu", &repeticao, &valor);
        
        // soma ao contador de pixels mais quantas vezes aquele valor compacto irá aparecer
        cont += repeticao;

        for (contRepeticao = 0; contRepeticao < repeticao; contRepeticao++) {
            cor[i][j] = valor;
           
            // faz a troca de valores dos índices i e j para mantê-los dentro do tamanho suposto da matriz
            j++;
            if (j == largura) {
                j = 0;
                i++;
            } 
        }  
    }
}

// Obtem a imagem cinza a partir das imagens de RGB
void obterMatrizEscalaCinza(int largura, int altura, unsigned char vermelho[][MAX_TAM_RGB], unsigned char verde[][MAX_TAM_RGB], unsigned char azul[][MAX_TAM_RGB], unsigned char cinza[][MAX_TAM_RGB]) {

    int i, j;

    unsigned char valorCinza;
    
    short valorParcial;

    for (i = 0; i < altura; i++) 
        for (j = 0; j < largura; j++) {
        
            valorParcial = (vermelho[i][j] + azul[i][j] + verde[i][j]) / 3;

            if (valorParcial < 0)
                valorParcial = -valorParcial;

            valorCinza = valorParcial;
            cinza[i][j] = valorCinza;
        }
}

// Le da entrada a matriz de filtro a ser aplicada na imagem
void obterFiltro(short filtro[][MAX_TAM_FILTRO], unsigned char dimensaoFiltro) {

    unsigned char i, j;

    for (i = 0; i < dimensaoFiltro; i++)
        for (j = 0; j < dimensaoFiltro; j++)
            scanf("%hi ", &filtro[i][j]);

}

// Calcula o valor do pixel daquela posicao x y da matriz de cinza a partir do filtro dado
unsigned char posicaoConvolucao(short filtro[][MAX_TAM_FILTRO], unsigned char cinza[][MAX_TAM_RGB], int divisor, int x, int y, int altura, int largura, unsigned char dimensaoFiltro) {
    
    unsigned char pixel;

    short valorConvolucao = 0;

    int intervalo,
        xComeco,
        yComeco,
        xFinal,
        yFinal,
        i, 
        j;

    // O intervalo que ocupa em ambos os lados e para cima e para baixo dada a ordem da matriz de filtro
    intervalo = dimensaoFiltro / 2; 

    // O começo de X e Y estão a menos intervalo do X e Y passados, assim como o final analogamente
    xComeco = x - intervalo;
    yComeco = y - intervalo;
    xFinal  = x + intervalo;
    yFinal  = y + intervalo;

    // Caso essas coordenadas não estejam contidas no tamanho da matriz de imagem,
    // é necessário retornar o valor da própria imagem cinza daquela posição X e Y
    if (xComeco < 0 || yComeco < 0 || xFinal >= altura || yFinal >= largura)
        return cinza[x][y];

    // Calcula o valor multiplicando o valor da posicao do filtro pela posicao da imagem cinza
    for (i = 0; i < dimensaoFiltro; i++)
        for (j = 0; j < dimensaoFiltro; j++) 
            valorConvolucao += filtro[i][j] * cinza[xComeco+i][yComeco+j];
        
    valorConvolucao = valorConvolucao / divisor;

    // Trunca os valores menores que 0 e maiores que 255
    if (valorConvolucao < 0)
        pixel = 0;
    else if (valorConvolucao > 255) 
        pixel = 255;
    else
        pixel = valorConvolucao;

    return pixel;
}

// Essa função aplica a técnica de Convolução para cada elemento da imagem (matriz), salvando a imagem com filtro aplicado na variável resultado
void aplicarFiltroMatrizCinza(unsigned char resultado[][MAX_TAM_RGB], short filtro[][MAX_TAM_FILTRO], unsigned char cinza[][MAX_TAM_RGB], int divisor, int altura, int largura, unsigned char dimensaoFiltro) {

    int i, j;

    unsigned char valorPosicao;
    
    for (i = 0; i < altura; i++) 
        for (j = 0; j < largura; j++) { 

            valorPosicao = posicaoConvolucao(filtro, cinza, divisor, i, j, altura, largura, dimensaoFiltro);

            resultado[i][j] = valorPosicao;
        }
}

// Função que organiza a saida do programa na ordem
void imprimirResultado(unsigned char resultado[][MAX_TAM_RGB], int largura, int altura) {

    int i, j;
    
    printf("P2\n");
    printf("%d %d\n", largura, altura);
    printf("255\n");

    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura-1; j++)
            printf("%d ",  resultado[i][j]);
       
        //O ultimo printf deve ficar fora para que não haja espaço antes do \n 
        printf("%d\n", resultado[i][j]);
    }
}

int main() {

    int divisor,
        qtdMatriz,
        largura,
        altura;

    short filtro[MAX_TAM_FILTRO][MAX_TAM_FILTRO];

    unsigned char dimensaoFiltro;
    
    unsigned char
          vermelho[MAX_TAM_RGB][MAX_TAM_RGB],
          azul[MAX_TAM_RGB][MAX_TAM_RGB],       
          verde[MAX_TAM_RGB][MAX_TAM_RGB],
          cinza[MAX_TAM_RGB][MAX_TAM_RGB],
          resultado[MAX_TAM_RGB][MAX_TAM_RGB];


    scanf("%d %hhu", &divisor, &dimensaoFiltro);

    obterFiltro(filtro, dimensaoFiltro);

    scanf("%d %d", &largura, &altura);

    qtdMatriz = largura * altura;

    descompactarParaCor(vermelho, qtdMatriz, largura, altura);
    descompactarParaCor(verde   , qtdMatriz, largura, altura);
    descompactarParaCor(azul    , qtdMatriz, largura, altura); 

    obterMatrizEscalaCinza(largura, altura, vermelho, verde, azul, cinza);

    /*printc(cinza, altura, largura);    
    printc(vermelho, altura, largura);
    printc(verde   , altura, largura);
    printc(azul    , altura, largura); */

    aplicarFiltroMatrizCinza(resultado, filtro, cinza, divisor, altura, largura, dimensaoFiltro);

    imprimirResultado(resultado, largura, altura);
    
    return 0;
}
