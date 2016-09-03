#include <stdio.h>
#include <stdlib.h>

#define END_LINE '\n'

#define PARAMETERS "m=%d, n=%d, p=%d\n"
#define FIRST_LIST "primeira "
#define SECOND_LIST "segunda "
#define THIRD_LIST "terceira "
#define ORIGINAL_LIST "original "

typedef
	struct Node {
		short value;
		struct Node * next;
	} Node;

typedef
	struct {
		Node * first, * last;
		short m, n, p;
	} List;

void readShort(short * value) {
	scanf("%hi", value);
}

void readChar(char * c) {
	scanf("%c", c);
}

void readParameters(List ** list) {
	scanf("%hi %hi %hi", &(*list)->m, &(*list)->n, &(*list)->p);
}

void init(List ** list) {
	(*list) = malloc(sizeof(List*));
	(*list)->first = NULL;
	(*list)->last = NULL;
}

Node * createNode(short value) {
	Node * n = malloc(sizeof(Node));
	n->value = value;
	n->next = NULL;
	return n;
}

void insert(List ** list, short value) {
	Node * node = createNode(value),
		 * actual = actual = (*list)->first;

	if (actual == NULL) {
		(*list)->first = node;
		(*list)->last = node;
		return;
	}

	for (; actual->next != NULL; actual = actual->next) {
	}

	actual->next = node;
	(*list)->last = node;
}

void readList(List ** list) {
	char c;
	short value;

	for (;c != END_LINE;) {
		readShort(&value);
		insert(list, value);
		readChar(&c);
	}
}

Node * getListNodeWithValue(List ** list, short * value) {
	Node * actual = (*list)->first;
	if (actual == NULL) {
		return NULL;
	}

	for (; actual->next != NULL; actual = actual->next) {
		if (actual->value == *value) {
			return actual;
		}
	}

	return NULL;
}

void printNodes(Node ** start, short * endValue, char listIdentifier[]) {
	Node * actual = (*start);

	printf("%s ", listIdentifier);
	for (; actual->value != *endValue; actual = actual->next) {
		printf("%d ", actual->value);
	}

	printf("%d\n", actual->value);
}

void printFirstList(List ** list) {
	Node * start = getListNodeWithValue(list, &(*list)->m),
		 * end = getListNodeWithValue(list, &(*list)->n);

	if (start == NULL) {
		start = (*list)->first;
	}

	if (end == NULL) {
		end = getListNodeWithValue(list, &(*list)->p);
		if (end == NULL) {
			end = (*list)->last;
		}
	}

	printNodes(&start, &end->value, FIRST_LIST);
}

void printSecondList(List ** list) {
	Node * start = getListNodeWithValue(list, &(*list)->n),
		 * end = getListNodeWithValue(list, &(*list)->p);

	if (start == NULL) {
		start = getListNodeWithValue(list, &(*list)->m);
		if (start == NULL) {
			start = (*list)->first;
		}
	}

	if (end == NULL) {
		end = (*list)->last;
	}

	printNodes(&start, &end->value, SECOND_LIST);
}

void printThirdList(List ** list) {
	Node * start = getListNodeWithValue(list, &(*list)->p),
		 * end = (*list)->last;

	if (start == NULL) {
		start = getListNodeWithValue(list, &(*list)->n);
		if (start == NULL) {
			start = (*list)->first;
		}
	}

	printNodes(&start, &end->value, THIRD_LIST);
}

void print(List ** list) {
	Node * actual;

	printf(ORIGINAL_LIST);
	for (actual = (*list)->first; actual->next != NULL; actual = actual->next) {
		printf("%d ", actual->value);
	}

	printf("%d\n", actual->value);
	printf(PARAMETERS, (*list)->m, (*list)->n, (*list)->p);
}

void freeNodes(Node * n) {
	if (n == NULL) {
		return;
	}

	freeNodes(n->next);
	free(n);
}

void freeList(List ** list) {
	freeNodes((*list)->first);
	free(*list);
}

int main() {
	List * list = NULL;

	init(&list);
	readList(&list);

	readParameters(&list);

	print(&list);
	printFirstList(&list);
	printSecondList(&list);
	printThirdList(&list);

	freeList(&list);
	return 0;
}
