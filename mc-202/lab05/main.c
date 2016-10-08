/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

int main() {

	File * f = createFile("lala");

	int i = isPrefixExpression(f, "lal*");

	printf("Resposta: %d \n", i);

	freeFile(&f);

	return 0;
}