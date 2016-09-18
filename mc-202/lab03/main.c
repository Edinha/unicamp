/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"
#include "paintor.h"

int main() {
	Doll * outsided;
	List * numbersByColor = malloc(sizeof(List));
	int coloringStatus;

	createDollsRelation(&outsided);

	if (outsided == NULL) {
		printf("%s", ERROR_MESSAGE);
	} else {
		coloringStatus = defineColorForDolls(&outsided, &numbersByColor);

		if (coloringStatus == ERROR_COLORING) {
			printf("%s", ERROR_MESSAGE);
		} else {
			response(&numbersByColor);
		}

		freeDolls(outsided);
	}

	freeList(&numbersByColor);

	return 0;
}