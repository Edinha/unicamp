#include <stdio.h>
#include <stdlib.h>

#define END_LINE '\n'

typedef
	struct Node {
		short value;
		struct Node * next;
	} Node;

typedef
	struct {
		Node * first;
	} List;

void readShort(short * value) {
	scanf("%hi", value);
}

void readChar(char * c) {
	scanf("%c", c);
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
		 * actual;

	if ((*list)->first == NULL) {
		(*list)->first = node;
		return;
	}

	for (actual = (*list)->first; actual->next != NULL; actual = actual->next) {
	}

	actual->next = node;
}

void readList(List ** list) {
	char c;
	short value;

	for (;;) {
		readShort(&value);
		insert(list, value);
		readChar(&c);

		if (c == END_LINE){
			break;
		}
	}
}

void print(List ** list) {
	Node * actual;

	for (actual = (*list)->first; actual != NULL; actual = actual->next) {
		printf("%d ", actual->value);
	}
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
	print(&list);

	freeList(&list);
	return 0;
}
