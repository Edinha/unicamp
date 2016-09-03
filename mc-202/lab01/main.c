#include <stdio.h>
#include <stdlib.h>

#define END_LINE '\n'

#define NOT_FOUND 0
#define FOUND 1

typedef
	struct Node {
		short value;
		struct Node * next;
	} Node;

typedef
	struct {
		Node * first;
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
}

Node* createNode(short value) {
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
		return;
	}

	for (; actual->next != NULL; actual = actual->next) {
	}

	actual->next = node;
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

Node * getListLastElement(List ** list) {
	Node * actual = (*list)->first;
	if (actual == NULL) {
		return NULL;
	}

	for (; actual->next != NULL; actual = actual->next) {
	}

	return actual;
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

void printNodes(Node ** start, Node ** end) {
	Node * actual = (*start);
	for (; actual->value != (*end)->value; actual = actual->next) {
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
			end = getListLastElement(list);
		}
	}

	printNodes(&start, &end);
}

void print(List ** list) {
	Node * actual;
	for (actual = (*list)->first; actual->next != NULL; actual = actual->next) {
		printf("%d ", actual->value);
	}

	printf("%d\n", actual->value);
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

	printFirstList(&list);

	print(&list);
	freeList(&list);
	return 0;
}
