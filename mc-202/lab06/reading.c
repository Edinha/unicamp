/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementação dos métodos */

void readAllClientRequests(Tree * ingredients) {
	int sequential, clockTime;
	String ingredientName;

	sequential = 1;

	while (scanf("%d", &clockTime) == 1) {
		Client * client = createClient(sequential);
		client->sequential = sequential;

		while (scanf("%*[ ]%[^ \r\n]", ingredientName) == 1) {
			insertTree(ingredients, ingredientName);

			// TODO inserir lista de clients
		}

		sequential++;
	}
}