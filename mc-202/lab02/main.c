#include "reading.h"

int main() {
	List * mtf, 
		 * tr;

	init(&tr, TR);
	init(&mtf, MTF);

	// readInitialList(&tr);
	// copy(&tr, &mtf);

	freeList(&tr);
	freeList(&mtf);

	return 0;
}