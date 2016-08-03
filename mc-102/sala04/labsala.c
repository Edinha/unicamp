// Nome  : William Gonçalves da Cruz
// RA    : 188671
// Turma : W

// Lab Sala 04 : Multiplicação de polinômios
//
// O objetivo desse laboratório é desenvolver um programa que calcule a multiplicação de dois polinômios na forma
// 	a0 * x^0 + a1 * x^1 + .... + an * x^n
//
// Entrada : 
// 	Um número N indicando o numero de termos do primeiro polinômio
// 	O primeiro polinômio composto de N termos do tipo a * X^b
// 	Um número M indicando o número de termos do segundo polinômio
// 	O segundo polinômio nas mesmas condições do primeiro
//
// Saida : 
// 	Os coeficientes devem estar em ordem crescente, termo com coeficiente 0 deve ser omitido, a menos no caso de
// 	ser o polinômio nulo
// 		a0 * x^0 + a1 * x^1 + .... + an * x^n é a forma da saida


#include <stdio.h>

#define MAIOR_EXPOENTE 51

int lerNumeroTermos() {
    int n;
    scanf("%d ", &n);
    return n;
}

// Verificação sinal Negativo 
int sinalNegativo(char sinal) {
    if (sinal == '-') {
        return 1;
    }

    return 0;
}

// Valida se o polinômio do parâmetro é nulo ou não, ou seja, tem todos os seus coeficientes ligados a x iguais a 0
int polinomioNulo(int polinomio[]) {

    for (int i = 0; i < MAIOR_EXPOENTE; i++)
	if (polinomio[i] != 0) {
	    return 0;
	}

    return 1;
}

// Valida se existe um coeficiente não nulo após a posição pos
int temProximo(int polinomio[], int pos) {

   int tamanho = MAIOR_EXPOENTE * MAIOR_EXPOENTE;   

   for (int i = pos + 1; i < tamanho; i++)
       if (polinomio[i] != 0)
	   return 1;

   return 0;
}

// Retorna o carácter para especificar o sinal do coeficiente na saida ('-' para negativo e '+' para positivo)
char sinalDoCoeficiente(int coeficiente) {
    if (coeficiente < 0) {
	return '-';
    }

    return '+';
}

// Lê uma linha de polinômio da entrada, armazenando coeficientes no vetor polinomio (parâmetro)
void lerPolinomio(int polinomio[], int termos) {

    int coeficiente,
        expoente,
        i;

    char sinal;

    for (i = 0; i < termos; i++) {
        // le um monômio dentro da repetição
	scanf("%c %d x^%d ", &sinal, &coeficiente, &expoente);

 	// Se o caracter indica número negativo, inverte o sinal do coeficiente lido	
	if (sinalNegativo(sinal)) {
	    coeficiente = -coeficiente;
	}

	polinomio[expoente] = coeficiente;
    }    
}

// Zera os coeficientes do polinômio para inicializá-los 
void zerarMultiplicado (int multiplicado[]) {
    int tamanho = MAIOR_EXPOENTE * MAIOR_EXPOENTE;

    for (int i = 0; i < tamanho; i++)
        multiplicado[i] = 0;
}

// Zera os coeficientes do polinômio para inicializá-los
void zerarPolinomio(int polinomio[]) {
    for (int i = 0; i < MAIOR_EXPOENTE; i++)
	polinomio[i] = 0;
}

// Multiplica os dois primeiros parâmetros, armazenando o resultado de no terceiro
void multiplicarPolinomios(int poliPrim[], int poliSeg[], int multiplicado[]) {

    int i, j, 
        coeficienteAtual,
        expoenteAtual;

    for (i = 0; i < MAIOR_EXPOENTE; i++) {
	for (j = 0; j < MAIOR_EXPOENTE; j++) {

	    // Pega o expoente atual para o termo de x
	    expoenteAtual = i+j;
	    
	    // Multiplica os coeficientes para armazenar a soma atual
	    coeficienteAtual = poliPrim[i] * poliSeg[j];
	    
            // Agrega esse valor ao expoenteAtual
 	    multiplicado[expoenteAtual] += coeficienteAtual;		
	    
	}  
    }
}

// Exibe a saida no formato polinomial a partir do vetor de coeficientes
void mostrarPolinomio(int polinomio[]) {

    int i,
        tamanho = MAIOR_EXPOENTE * MAIOR_EXPOENTE;
    
    char sinal;

    // Caso seja o polinômio nulo, deve ser impresso '+ 0 x^0' e sair da função de mostrar
    if (polinomioNulo(polinomio)) {
	printf("+ 0 x^0\n");
	return;
    }

    for (i = 0; i < tamanho; i++) {
	if (polinomio[i] != 0) {

	    sinal = sinalDoCoeficiente(polinomio[i]);
         
	    // Inverte o sinal caso seja negativo para não imprimir o caracter '-' duas vezes   
	    if (sinalNegativo(sinal)) {
            	polinomio[i] = -polinomio[i];
	    }		    

	    // Escreve o polinômio na forma (sinal) an * x^n 
            printf("%c %d x^%d", sinal, polinomio[i], i); 
	    
	    // Espaço entre os termos caso próximo não seja 0
	    if (temProximo(polinomio, i))
               printf(" ");
	}
    }

    printf("\n");
}

int main() {
    
    int poliPrim[MAIOR_EXPOENTE],
	poliSeg[MAIOR_EXPOENTE],
        multiplicado[MAIOR_EXPOENTE * MAIOR_EXPOENTE],
	numeroAtualTermos;

    zerarPolinomio(poliPrim);
    zerarPolinomio(poliSeg); 
    zerarMultiplicado(multiplicado);   

    numeroAtualTermos = lerNumeroTermos();
    lerPolinomio(poliPrim, numeroAtualTermos);

    numeroAtualTermos = lerNumeroTermos();
    lerPolinomio(poliSeg, numeroAtualTermos);

    multiplicarPolinomios(poliPrim, poliSeg, multiplicado);

    mostrarPolinomio(multiplicado);
	
    return 0;
}



