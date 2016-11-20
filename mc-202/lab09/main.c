/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

int main() {

	Image * image = readImage();

	Graph * graph = buildGraph(image);

	// TODO free graph pointer and remove printf
	printf("%d\n", graph->size);

	Position p = graph->vertexes[100]->position;
	printf("%d %d -> %d %d", p.x, p.y, graph->vertexes[100]->neighbours[3].x, graph->vertexes[100]->neighbours[3].y);

	freeImage(&image);

	return 0;
}
