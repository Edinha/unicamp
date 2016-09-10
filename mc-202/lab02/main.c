#include "reading.h"

int main() {
	List * mtf, 
		 * tr;

	int requestSize;
	Request * requests = NULL;

	init(&tr, TR);
	init(&mtf, MTF);

	requestSize = readInitialList(&tr);
	copy(&tr, &mtf);

	initRequests(&requests, requestSize);
	readRequests(&requests, requestSize);

	applyRequests(&tr, &requests, requestSize);
	applyRequests(&mtf, &requests, requestSize);

	printList(&mtf);
	printList(&tr);

	free(requests);
	freeList(&tr);
	freeList(&mtf);

	return 0;
}