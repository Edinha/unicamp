//Nome  : William Gonçalves da Cruz
//RA    : 188671
//Turma : W

/*  Batalha naval (Lab Sala 03)
 *  O programa consiste em uma forma de ajudar o jogar a acertar os proximos tiro em uma partida de batalha naval
 *  Dizendo as coordenadas do resto do navio a partir de alguns tiros dados
 *
 *  Entrada :
 *      Uma linha contendo dois números (M, N) que são as dimensões da matriz
 *      Uma linha com MXN caracteres representando o tabuleiro do jogo
 *          O caracter * significa água
 *          As letra significam que tem um barco naquela posição
 *      Uma linha contendo as jogadas no formato LxCy onde x e y são números
 *          Essa linha acaba com L-1C-1
 */

#include <stdio.h>

// Essa função acha os equivalentes à aquele navio no tabuleiro em uma linha passada e os printa na tela
// No formato "LxCy "
// È somado um as variaveis 'linha' e 'j' pois a contagem da matriz começa em 0, quando deveria significa 1, e assim por diante 
void acharEquivalentesLinha(char tabuleiro[20][20], int colunas, int linha, int colunaTiro, char navioAcertado) {
    int j;

    for (j = 0; j < colunas ; j++) 
        if (tabuleiro[linha][j] == navioAcertado && j != colunaTiro)
           printf("L%dC%d ", linha+1, j+1);
    
    printf("\n");
}

// Essa função acha os equivalentes à aquele navio no tabuleiro em uma coluna passada e os printa na tela
// No formato "LxCy "
// È somado um as variaveis 'coluna' e 'j' pois a contagem da matriz começa em 0, quando deveria significa 1, e assim por diante 
void acharEquivalentesColuna(char tabuleiro[20][20], int linhas, int coluna, int linhaTiro, char navioAcertado) {
    int j;
        
    for (j = 0; j < linhas; j++) { 
        if (tabuleiro[j][coluna] == navioAcertado && linhaTiro != j)
           printf("L%dC%d ", j+1, coluna+1);
    }

    printf("\n");
} 

int main() {
   
    int linhas,
        colunas,
        xJogada, 
        yJogada,
        cima,
        baixo,
        esq,
        dir,
        i,
        j;
    
    char navioAcertado; 
    char tabuleiro[20][20];
  
    // Ler as dimensões da matriz 
    scanf("%d %d ", &linhas, &colunas);
   
    // inicializa a matriz
    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
            tabuleiro[i][j] = '*';

    // Repetir para proxima linha
    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
           scanf("%c", &tabuleiro[i][j]);
           // Ler o cáracter da linha e salvar na matriz na posicao i,j

    scanf(" L%dC%d", &xJogada, &yJogada);
    // Ler a jogada
    
    for(;;) {

        // Caso seja L-1,C-1, acabaram as jogadas
        if (xJogada == -1 && yJogada == -1)
            break;

        // Subtração por 1 pois a linha 3 é representada em C pelo número 2, pois começa sua contagem em 0 em vez de 1
        xJogada--;
        yJogada--;

        // A partir da jogada, buscar em seus arredores a continuação do navio
        navioAcertado = tabuleiro[xJogada][yJogada]; 
        
        // Configura as posições de cima,baixo,direita,esquerda seguindo uma padronização de que
        // Cima é anterior (-1) ao x (à linha do tiro)
        // Baixo é posterior (+1) ao x (à linha do tiro)
        // Esquerda é anterior (-1) ao y (à coluna do tiro)
        // Direita é posterior (+1) ao x (à coluna do tiro)
        cima  = xJogada - 1;
        baixo = xJogada + 1;
        esq   = yJogada - 1;
        dir   = yJogada + 1;

        // Caso a outra letra igual ao navio esteja a sua esquerda ou direita
        if (esq > -1 && tabuleiro[xJogada][esq] == navioAcertado) {
            acharEquivalentesLinha(tabuleiro, colunas, xJogada, yJogada, navioAcertado);
        } else if (dir < 20 && tabuleiro[xJogada][dir] == navioAcertado) {
            acharEquivalentesLinha(tabuleiro, colunas, xJogada, yJogada, navioAcertado);
        } 
        
        // Caso a outra letra igual ao navio esteja a cima ou a baixo
        if (cima > -1 && tabuleiro[cima][yJogada] == navioAcertado) {
            acharEquivalentesColuna(tabuleiro, linhas, yJogada, xJogada, navioAcertado);
        } else if (baixo < 20 && tabuleiro[baixo][yJogada] == navioAcertado) {     
            acharEquivalentesColuna(tabuleiro, linhas, yJogada, xJogada, navioAcertado);    
        }

        // Ler a próxima jogada
        scanf("L%dC%d", &xJogada, &yJogada);
    }   

    return 0;
}
