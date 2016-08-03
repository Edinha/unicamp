// Nome : William Gonçalves da Cruz
// Ra   : 188671

/*
 * Esses programa consiste em calcular a pontuação de um jogo de xadrez com base nas peças que estão na ponta do 
 * tabuleiro, tendo uma regra para acumular ou perder pontos, de acordo com a multiplicidade da soma dos números que
 * ocupam as pontas do tabuleiro
 *
 * Entrada: Um número inteiro dizendo o numero de peças do tabuleiro (N), de valor 1 a 28
 *	    Seguida de N combinações de 2 números inteiros (de 1 a 6) , indicando as peças do jogo
 *
 * Saida:   Um número inteiro que indica a pontuação do jogador
 *
 */

#include <stdio.h>

int main() {

    int numeroPecas, 
	pontaEsquerda,
	pontaDireita,
	somaDasPontas, 
	contador,
	proximaPecaEsquerda, 
        proximaPecaDireita,
	pontuacao;    

    // Ler o número de peças do jogo (N)
    scanf("%d", &numeroPecas);	
    
    //Tem de haver sempre uma peça em jogo, logo a primeira pode ser lida assim
    scanf("%d:%d", &proximaPecaEsquerda, &proximaPecaDireita);
    
    pontaEsquerda = proximaPecaEsquerda;
    pontaDireita  = proximaPecaDireita;	
    somaDasPontas = 0;
    pontuacao = 0;

    for (contador = 1; contador < numeroPecas; contador++){
        
        scanf(" %d:%d", &proximaPecaEsquerda, &proximaPecaDireita);

	// Para o caso da ponta esquerda ter menor valor que a da direita
	if (pontaEsquerda < pontaDireita) {
  	    
	    // Valida onde a proxima peça pode ser encaixada
	    // Quando a ponta esquerda da peça encaixa, sua direita ficará livre para próxima jogada, vice versa
	    if (pontaEsquerda == proximaPecaEsquerda) { 
	        pontaEsquerda = proximaPecaDireita;
	    } else if (pontaEsquerda == proximaPecaDireita) {
	        pontaEsquerda = proximaPecaEsquerda;    	
	    } else if (pontaDireita == proximaPecaEsquerda) {
	        pontaDireita  = proximaPecaDireita;
	    } else if (pontaDireita == proximaPecaDireita) {
	        pontaDireita = proximaPecaEsquerda;   
	    }
	    
	// senão, a direita deve ser encaixada primeiro se for possível
	} else {

	    // Valida onde a proxima peça pode ser encaixada
	    // Quando a ponta esquerda da peça encaixa, sua direita ficará livre para próxima jogada, vice versa
            if (pontaDireita == proximaPecaEsquerda) { 
                pontaDireita = proximaPecaDireita;
            } else if (pontaDireita == proximaPecaDireita) {
                pontaDireita = proximaPecaEsquerda; 
            } else if (pontaEsquerda == proximaPecaEsquerda) {
                pontaEsquerda  = proximaPecaDireita;
            } else if (pontaEsquerda == proximaPecaDireita) {
                pontaEsquerda = proximaPecaEsquerda;
            } 
	}

        // Caso soma for múltiplo de 4, perde-se o valor da soma
        // Caso soma for múltiplo de 5, ganha-se o valor da soma
	somaDasPontas = pontaDireita + pontaEsquerda;        

	if ( somaDasPontas % 4 == 0) {
	    pontuacao -= somaDasPontas;
	} else if ( somaDasPontas % 5 == 0) {
	    pontuacao += somaDasPontas;
	}	
    }

    printf("%d\n", pontuacao);
	
    // Repetir para cada peça, N vezes
    //   a) Ler a peca no formato E:D, sendo E e D inteiros entre 1 e 6
    //   b) Analisar em qual ponta é possível 'encaixar' a peça, 
    //      -> Onde a ponta do tabuleiro tiver um número igual a uma dos números da peça
    // 	    -> Caso as duas pontas seja possivel, colocar na menor possível
    //   c) Soma a pontuacao e checa como somá-la a atual 

    return 0;
}
