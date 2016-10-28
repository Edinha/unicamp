/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

int main() {

	Tree * ingredients = createTree();

	readAllClientRequests(ingredients);

	freeTree(&ingredients);

	return 0;
}