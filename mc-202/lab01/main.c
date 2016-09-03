/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define o 'fim de linha' para o final da lista de entrada
#define END_LINE '\n'

// Define as constantes strings usadas no programa
#define PARAMETERS "m=%d, n=%d, p=%d\n"
#define FIRST_LIST "primeira "
#define SECOND_LIST "segunda "
#define THIRD_LIST "terceira "
#define ORIGINAL_LIST "original "

// Estrutura de nó para elemento da lista, contém seu valor e o próximo nó
typedef
	struct Node {
		short value;
		struct Node * next;
	} Node;

/* Estrutura de lista, contém seu primeiro e último nó, além dos parâmetros
 * m, n e p descritos como limitadores para as sublistas do laboratório
 */
typedef
	struct {
		Node * first, * last;
		short m, n, p;
	} List;

// Lê os parâmetros m, n, p da lista
void readParameters(List ** list) {
	scanf("%hi %hi %hi", &(*list)->m, &(*list)->n, &(*list)->p);
}

// Inicializa um ponteiro de ponteiro para a lista
void init(List ** list) {
	(*list) = malloc(sizeof(List*));
	(*list)->first = NULL;
	(*list)->last = NULL;
}

// Cria um novo nó para a lista a partir de um valor parametrizado
Node * createNode(short value) {
	Node * n = malloc(sizeof(Node));
	n->value = value;
	n->next = NULL;
	return n;
}

// Insere um novo nó ao final da lista
void insert(List ** list, short value) {
	Node * node = createNode(value),
		 * actual = actual = (*list)->first;

	// Caso a lista esteja vazia
	if (actual == NULL) {
		(*list)->first = node;
		(*list)->last = node;
		return;
	}

	for (; actual->next != NULL; actual = actual->next) {
	}

	// O novo nó também é o novo final da lista
	actual->next = node;
	(*list)->last = node;
}

/* Lê is valores inteiros e espaços da entrada para formar a lista, até que
 * se encontre o final de linha (\n)
 */
void readList(List ** list) {
	char allValues[1000],
		 * splited;

	short value;

	// Lê toda a entrada e separa por espaço para pegar todos os valores
	scanf("%[^\n]s", allValues);
	splited = strtok(allValues, " ");
	for (;splited != NULL;) {
		// Pega o próximo elemento do splited
		sscanf(splited, "%hi", &value);
		insert(list, value);
		splited = strtok(NULL, " ");
	}
}

/* Retorna a última ocorrência do ponteiro para o nó que contém o mesmo valor
 * passado no parâmetro, a partir de um ponteiro dado como inicio
 */
Node * getListNodeWithValueFromStart(Node * actual, short * value) {
	Node * required = NULL;
	for (; actual->next != NULL; actual = actual->next) {
		if (actual->value == *value) {
			required = actual;
		}
	}

	return required;
}

/* Retorna a prmieira ocorrência do ponteiro para o nó que contém o mesmo valor
 * passado no parâmetro, a partir de um ponteiro dado como inicio
 */
Node * getFirstNodeWithValueFromStart(Node * actual, short * value) {
	for (; actual->next != NULL; actual = actual->next) {
		if (actual->value == *value) {
			return actual;
		}
	}

	return NULL;
}

// Retorna a última ocorrência do valor a partir do começo da listagem
Node * getListNodeWithValue(List ** list, short * value) {
	return getListNodeWithValueFromStart((*list)->first, value);
}

// Retorna a primeira ocorrência a partir do começo da listagem
Node * getFirstListNodeWithValue(List ** list, short * value) {
	return getFirstNodeWithValueFromStart((*list)->first, value);
}

// Retorna o primeiro nó que contém o valor de M
Node * getMStartNodeWithValue(List ** list) {
	Node * mStart = getListNodeWithValue(list, &(*list)->m);
	if (mStart == NULL) {
		mStart = (*list)->first;
	}
	return mStart;
}

/* Printa, a partir do nó começo, todos os valores dos nós subsequentes, até
 * que se encontre o valor final parametrizado, sempre identificando qual das
 * listas (primeira, segunda, terceira) está sendo printada
 */
void printNodes(Node ** start, short * endValue, char listIdentifier[]) {
	Node * actual = (*start);

	printf("%s", listIdentifier);
	for (; actual->value != *endValue; actual = actual->next) {
		printf("%d ", actual->value);
	}

	printf("%d\n", actual->value);
}

/* Método que define o começo e final da primeira lista, dada existência dos
 * parâmetro m, n, p e passa esses parâmetros para serem printados
 */
void printFirstList(List ** list) {
	Node * start = getFirstListNodeWithValue(list, &(*list)->m),
		 * end = getFirstListNodeWithValue(list, &(*list)->n);

	if (start == NULL) {
		start = (*list)->first;
	}

	if (end == NULL) {
		end = getFirstListNodeWithValue(list, &(*list)->p);
		if (end == NULL) {
			end = (*list)->last;
		}
	}

	printNodes(&start, &end->value, FIRST_LIST);
}

/* Método que define o começo e final da segunda lista, dada existência dos
 * parâmetro m, n, p e passa esses parâmetros para serem printados
 */
void printSecondList(List ** list) {
	Node * mStart = getMStartNodeWithValue(list),
		 * start = getFirstNodeWithValueFromStart(mStart, &(*list)->n),
		 * end = getListNodeWithValueFromStart(mStart, &(*list)->p);

	if (start == NULL) {
		start = mStart;
	}

	if (end == NULL) {
		end = (*list)->last;
	}

	printNodes(&start, &end->value, SECOND_LIST);
}

/* Método que define o começo e final da segunda lista, dada existência dos
 * parâmetro m, n, p e passa esses parâmetros para serem printados
 */
void printThirdList(List ** list) {
	Node * mStart = getMStartNodeWithValue(list),
		 * start = getListNodeWithValueFromStart(mStart, &(*list)->p),
		 * end = (*list)->last;

	if (start == NULL) {
		start = getFirstNodeWithValueFromStart(mStart, &(*list)->n);
		if (start == NULL) {
			start = mStart;
		}
	}

	printNodes(&start, &end->value, THIRD_LIST);
}

// Printa a lista original seguida por seus parâmetros m, n, p
void printOriginalList(List ** list) {
	printNodes(&(*list)->first, &(*list)->last->value, ORIGINAL_LIST);
	printf(PARAMETERS, (*list)->m, (*list)->n, (*list)->p);
}

// Libera os nós da lista em estratégia recursiva
void freeNodes(Node * n) {
	if (n == NULL) {
		return;
	}

	freeNodes(n->next);
	free(n);
}

// Libera a lista em si, a começar por seus nós
void freeList(List ** list) {
	freeNodes((*list)->first);
	free(*list);
}

int main() {
	List * list = NULL;

	init(&list);
	readList(&list);

	readParameters(&list);

	printOriginalList(&list);
	printFirstList(&list);
	printSecondList(&list);
	printThirdList(&list);

	freeList(&list);
	return 0;
}
