/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

int main() {

	Tree * directory = createTree();

	readAllCommands(directory);

	freeTree(&directory);

	return 0;
}