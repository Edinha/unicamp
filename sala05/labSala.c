// Nome  : William Gonçalves da Cruz
// RA    : 188671
// Turma : W

// Controle de Recursos humanos
// Lab para desenvolvimento de um programa que controla a alocação e desalocação de pessoas em um determinado
// projeto. Sua funcionalidade permite que o programa responda o maior gasto seguido com um funcionário para
// as alocações descritas pela entrada
//
// Funcionário contém uma matricula, 7 caractéres e um preço por hora de serviço
//
// Entrada : 
// 	Um número H de horas do projeto
// 	Um número N de funcionários, seguido de n linhas com matrícula e valor da hora
//	Um número S de sugestões de alocação e desalocação
//	S linhas no formato (tipoDaMudança matrículaFuncionário quantidadeHoras)
//	    Tipo no formato A (alocação) ou D (desalocação)
//

#include <stdio.h>
#include <string.h>

#define maxH 100 //max de horas na agenda do projeto
#define maxF 20 //max funcionários

typedef struct {
	char mat[7]; //matricula 
	float custo;
} func; //funcionario

typedef struct {
	int contagem; // Contagem do maior número de repetições
	int posicao;  // Valor do maior número de repetições
} sequencia;

//Funções para tratar o vetor de funcionários
void lerFunc (int n, func vet[]);
void imprimeFunc(int n, func vet[]);

//funções para tratar agenda do projeto
void imprimeProjeto(int n, int projeto[], func vetFunc[]);
void inicializaVetor(int n, int vet[]);

// Função para retornar a posição funcionário a partir de sua matrícula
int encontrarPosicaoFuncionarioPelaMatricula (func funcionarios[], int qtdFunc, char mat[]);

// Compara as matrículas
int comparaMatriculas (char primMat[], char segMat[]);

// Retorna o valor de projeto que mais se repete
sequencia valorDePosicaoComMaiorSequencia (int projeto[], int qtdHoras);

// Funções para alocação e desalocação
void alocarFuncionarioNoProjeto (int posFuncionario, int horas, int projeto[], int qtdHoras);
void desalocarFuncionarioNoProjeto (int posFuncionario, int horas, int projeto[], int qtdHoras);

// Calcula o maior custo em sequência
float maiorCusto (int projeto[], int qtdHoras, func funcionarios[]);

int main (){
	int nFunc, nHoras, posFuncAtual;
	func vetFunc[maxF];
	int projeto[maxH]; //vetor deverá armazenar o índice (posição) do funcionário no vetor vetFunc
	int i, nReg, horas;
	char tipo; //tipo do registro: Alocar ou desalocar horas em projeto
	char mat[7]; //matricula
	float maiorCustoProjeto;

	scanf("%d", &nHoras);
	inicializaVetor(nHoras, projeto);

	//leitura dos funcionarios (maticula e custo por hora)
	scanf("%d", &nFunc);
	lerFunc(nFunc, vetFunc);

	//leitura dos registos de agendamento e cancelamento
	scanf("%d", &nReg);
	for (i=0; i < nReg; i++){
		scanf("\n%c ", &tipo);
		scanf("%s", mat);
		scanf("%d", &horas);
		
		posFuncAtual = encontrarPosicaoFuncionarioPelaMatricula(vetFunc, nFunc, mat);	

		switch (tipo){
			case 'A':
				//ALOCAR HORAS PARA FUNCIONARIO AQUI
				alocarFuncionarioNoProjeto (posFuncAtual, horas, projeto, nHoras);
				break;
			case 'D':
				//DESALOCAR HORAS PARA FUNCIONARIO AQUI
				desalocarFuncionarioNoProjeto (posFuncAtual, horas, projeto, nHoras);
				break;
			default:
				printf("ERRO");
				break;
		}
	}

	maiorCustoProjeto = maiorCusto (projeto, nHoras, vetFunc);

	// Imprime a resposta	
	printf("O valor pago para a maior sequencia consecutiva realizada por um unico funcionario eh %.2f\n", maiorCustoProjeto);

	return 0;
}


/**
 * Ler os funcionários da entrada. 
 * Função ler N funcionários e armazenas num vetor de estrutura do tipo func. 
 * O vetor é recebido como referência, portanto a função modifica seus valores.
 * Função retorna nada.
 * @param n Número de funcionários a serem lidos na entrada
 * @param vet Vetor de estrutura func, onde serão armazenados os funcionários lido da entrada.
 */
void lerFunc(int n, func vet[]){
	int i;
	
	for (i=0; i<n; i++)
		scanf("\n%s %f", vet[i].mat, &vet[i].custo);		
}


/**
 * Função que imprime o vetor de funcionários. 
 * Função feita apenas com o propósito de teste.
 * Função imprime a matrícula do funcionário e o custo por hora do funcionário
 * @param n Número de funcionários, tamanho do vetor
 * @param vet Vetor de estrutura que armazena os funcionários.
 */
void imprimeFunc(int n, func vet[]){
	int i;
	
	for (i=0; i<n; i++)
		printf("%s %.2f", vet[i].mat, vet[i].custo);
}

/**
 * Função que imprime a agenda do projeto. 
 * Função feita apenas com o propósito de testar.
 * Função imprime * para horas livres e a matrícula do funcionário para horas alocada para alguém
 * @param n Número de horas na agenda
 * @param projeto Vetor de inteiros/índice para o funcionário alocado. Vetor mostra a configuração da agenda do projeto (os funcionários alocados). 
 * @param vetFunc Vetor que armazena as informações dos funcionários
 */
void imprimeProjeto(int n, int projeto[], func vetFunc[]){
	int i;
	
	for (i=0; i<n; i++)
		if (projeto[i]==-1)
			printf("* "); //uso * para mostrar hora vazia (disponível)
		else
			printf("%s ", vetFunc[projeto[i]].mat);
}


/**
 * Função que inicializa um vetor de inteiros com valor -1.
 * Função usada para inicializar o vetor que representa a agenda do projeto.
 * @param n Números de horas do projeto
 * @param vet Vetor de inteiros que armazena o índice para o funcionário alocado. 
 * Vetor guarda a configuração da agenda do projeto.
 */
void inicializaVetor(int n, int vet[]){
	int i;
	for (i=0; i<n; i++)
		vet[i]=-1;
}

/* Função que aplica a comparação entre duas matrículas que são vetores de char
 * @param primMat a primeira 
 * @param segMat a segunda matricula(s) */
int comparaMatriculas (char primMat[], char segMat[]) {
	return strcmp (primMat, segMat);
}


/* Função que retorna a posição do funcionário no vater de registros a partir de sua matrícula
 * @param funcionarios vetor com os registros de entrada
 * @param n o número de registros
 * @param mat[] a matrícula do funcionário desejado */
int encontrarPosicaoFuncionarioPelaMatricula (func funcionarios[], int qtdFunc, char mat[]) {
	for (int i = 0; i < qtdFunc; i++) {
		if (comparaMatriculas(funcionarios[i].mat, mat) == 0) {
			return i;
		}
	}

	return -1;
}

/* Função que aloca um funcionario no projeto a partir de sua matricula, guardando a posição do vetor que 
 * ele ocupa para representá-lo no projeto
 * @param int posFuncionario representando a posição que o funcionário ocupa no vetor de registros
 * @param horas a serem alocadas do funcionário
 * @param int projeto[] vetor que representa as alocações no projeto 
 * @param int qtdHoras quantidade horas projeto */
void alocarFuncionarioNoProjeto (int posFuncionario, int horas, int projeto[], int qtdHoras) {
	for (int i = 0; i < qtdHoras; i++) {
		// Todas as horas já foram alocadas
		if (horas == 0) {
			break;
		}	
	
		// Não há alocações para esse horário
		if (projeto[i] == -1) {
			projeto[i] = posFuncionario;
			horas--;
		}
	}
}

/* Função que desaloca um funcionario no projeto a partir de sua matricula, procurando suas alocações a 
 * partir da posção que ele ocupa no vetor de registros de funcionários
 * @param int posFuncionario representando a posição que o funcionário ocupa no vetor de registros
 * @param horas a serem desalocadas do funcionário
 * @param int projeto[] vetor que representa as alocações no projeto 
 * @param int qtdHoras quantidade horas projeto */
void desalocarFuncionarioNoProjeto (int posFuncionario, int horas, int projeto[], int qtdHoras) {
	for (int i = 0; i < qtdHoras; i++) {
		// Todas as horas já foram alocadas
		if (horas == 0) {
                        break;
                }
	
		// Funcionário está alocado naquela hora, será agora desalocado
		if (projeto[i] == posFuncionario) {
			projeto[i] = -1;
			horas--;
		}
	}
}

/* Função que retorna o valor e a quantidade contidos em projeto com maior sequência a partir da comparação 
 * sequêncial entre os valores do vetor. O retorno está encapsulado na estrutura de sequencia
 * @param int proetos[] vetor com as alocações
 * @param int qtdHoras tamanho do vetor */
sequencia valorDePosicaoComMaiorSequencia (int projeto[], int qtdHoras){
	sequencia seq;
	
	int contMaiorSequencia,
	    valorDaMaiorSequencia,
            contAtual,
	    valorAtual,
	    valorAnterior;

	// Inicializa a contagem para cada valor
	valorAnterior = projeto[0];
	contAtual = 1;

	// Inicializa os maiores valores (retornos) com valores simples para comparação
	contMaiorSequencia = contAtual;
	valorDaMaiorSequencia = valorAnterior;
	
	for (int i = 1; i < qtdHoras; i++) {
		valorAtual = projeto[i];

		// Caso sejam iguais, contabiliza mais uma contagem
		if (valorAtual == valorAnterior) {
			contAtual++;	
		} else {
			
			// Caso a contagem de repetidos seja maior do que a maior contagem atual
			if (contAtual > contMaiorSequencia) {
				valorDaMaiorSequencia = valorAnterior;
				contMaiorSequencia = contAtual;
			}

			// São diferentes, começa novamente a contar
			contAtual = 1;
		}

		valorAnterior = valorAtual; 
	}

	// Caso o último tenha a maior contagem
	if (contAtual > contMaiorSequencia) {
        	valorDaMaiorSequencia = valorAnterior;
                contMaiorSequencia = contAtual;
        }

	// Atualiza a estrutura de sequência para conter os maiores valores de contagem de sequência
	// Obtidos pelo algoritmo
	seq.contagem = contMaiorSequencia;
	seq.posicao  = valorDaMaiorSequencia;

	return seq;
}

/* Função que calcula o maior custo em sequência a partir do projeto
 * @param int projeto[] vetor do projeto com as alocações do projeto 
 * @param int qtdHoras tamanho do vetor projeto
 * @param funcionarios[] vetor com os registros de entrada */
float maiorCusto (int projeto[], int qtdHoras, func funcionarios[]) {
	sequencia maiorRepeticao = valorDePosicaoComMaiorSequencia (projeto, qtdHoras);

	float maiorCusto,
	      valorPorHora;	

	// A partir da posição retornada de maior sequência, pega o valor por hora daquele funcionário
	valorPorHora = funcionarios[maiorRepeticao.posicao].custo;	

	maiorCusto = maiorRepeticao.contagem * valorPorHora;

	return maiorCusto;
}
