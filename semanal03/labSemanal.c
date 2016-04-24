// Nome  : William Gonçalves da Cruz
// RA    : 188671
// Turma : W

/*  Lab Semanal 03 -> Processamento de imagem
 *
 *  O intuito desse programa é ler uma imagem que está compactada em seu formato rgb e aplicar um filtro para tal, 
 *  fazendo uma funcionalidade parecida com editores de imagem. Para tal, são usadas técnicas de convolução aplicadas
 *  a cada pixel a fim de deixar a imagem com "filtro" representado por uma matriz e um número divisor.
 *
 *  Entrada:
 *      Um número inteiro representando o divisor a ser usado na convolução
 *      A ordem da matriz quadrada de filtro (N) 
 *      N linhas com N números inteiros representando a matriz de filtro
 *      Dois inteiros positivos representando altura e largura
 *      Pares de números representando quantas vezes eles repetem e seu valor
 *  
 *  Saida:
 *      P2
 *      (largura) (altura)
 *      255 
 *      A matriz representando a imagem com filtro aplicado
 */

#include <stdio.h>

// Tamanho máximo das matrizes de imagem
#define MAX_TAM_RGB 600

// Tamanho máximo da matriz de filtro
#define MAX_TAM_FILTRO 10

// Descompacta a entrada para cada cor específica dada a quantidade de elementos e largura e altura da matriz
void descompactarCor(unsigned char cor[][MAX_TAM_RGB], int qtdMatriz, int largura, int altura) {
    
    int cont,
        contRepeticao,
        i,
        j;
        
    unsigned int  repeticao;
    unsigned char valor;

    for (cont = 0, i = 0, j = 0; cont < qtdMatriz;) {
        
        scanf("%u %hhu", &repeticao, &valor);
        
        // Soma ao contador de pixels a quantidade de valores repetidos atualmente lida
        cont += repeticao;

        for (contRepeticao = 0; contRepeticao < repeticao; contRepeticao++) {
            cor[i][j] = valor;
           
            // Faz a troca de valores dos índices i e j para mantê-los dentro do tamanho suposto da matriz
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
    
    for (i = 0; i < altura; i++) 
        for (j = 0; j < largura; j++) {
       
            // É a média aritimética entre os pixels das cores da imagem 
            valorCinza = (vermelho[i][j] + azul[i][j] + verde[i][j]) / 3;

            // Caso seja menor que 0, inverte
            if (valorCinza < 0)
                valorCinza = -valorCinza;

            cinza[i][j] = valorCinza;
        }
}

// Le da entrada a matriz de filtro a ser aplicada na imagem
void obterFiltro(int filtro[][MAX_TAM_FILTRO], unsigned char dimensaoFiltro) {

    unsigned char i, j;

    for (i = 0; i < dimensaoFiltro; i++)
        for (j = 0; j < dimensaoFiltro; j++)
            scanf("%d ", &filtro[i][j]);

}

// Calcula o valor do pixel daquela posicao x y da matriz de cinza a partir do filtro dado
unsigned char posicaoConvolucao(int filtro[][MAX_TAM_FILTRO], unsigned char cinza[][MAX_TAM_RGB], int divisor, int x, int y, int altura, int largura, unsigned char dimensaoFiltro) {
    
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

    // Calcula o valor multiplicando o valor da posicao do filtro pela posicao da imagem cinza e adicionando a uma somatória
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

// Aplica a técnica de Convolução para cada elemento da imagem (matriz), salvando a imagem com filtro aplicado na variável resultado
void aplicarFiltroMatrizCinza(unsigned char resultado[][MAX_TAM_RGB], int filtro[][MAX_TAM_FILTRO], unsigned char cinza[][MAX_TAM_RGB], int divisor, int altura, int largura, unsigned char dimensaoFiltro) {

    int i, j;

    unsigned char valorPosicao;
    
    for (i = 0; i < altura; i++) 
        for (j = 0; j < largura; j++) { 

            valorPosicao = posicaoConvolucao(filtro, cinza, divisor, i, j, altura, largura, dimensaoFiltro);

            resultado[i][j] = valorPosicao;
        }
}

// Executa a saída do programa no formato descrito pelo enunciado
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

    unsigned char dimensaoFiltro;
    
    int filtro[MAX_TAM_FILTRO][MAX_TAM_FILTRO];

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

    descompactarCor(vermelho, qtdMatriz, largura, altura);
    descompactarCor(verde   , qtdMatriz, largura, altura);
    descompactarCor(azul    , qtdMatriz, largura, altura); 

    obterMatrizEscalaCinza(largura, altura, vermelho, verde, azul, cinza);
    
    aplicarFiltroMatrizCinza(resultado, filtro, cinza, divisor, altura, largura, dimensaoFiltro);

    imprimirResultado(resultado, largura, altura);
    
    return 0;
}
