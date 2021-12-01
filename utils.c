#include "utils.h"


Board_t* createBoard() {
	Board_t* board = (Board_t*)malloc(sizeof(Board_t));
	if (board == NULL) {
		printf("ERROR: editor.c -> createBoard() -> malloc() returned NULL\n");
	}

	return board;

}

Tuple2_t intsToTuple(int x, int y) {
	Tuple2_t tuple = { x, y };
	return tuple;
}