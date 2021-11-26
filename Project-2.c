
#include "Project-2.h"


/*
 */

int main() {
	printf("Press any button...");
	while (!_kbhit());
	_getch();

	Board_t* board = createBoard();
	fillChess(board);
	enterEditorMode(board);

	//tempEditingMode();

	//Tuple2_t dim = { .x = 9, .y = 5 };
	//board_t* board = createBoard(dim);
	//board_t* boardB = createBoard(dim);


	//fillZero(board, dim);
	////fillDiagonal(board, dim);
	//fillChess(board, dim);

	//fillZero(boardB, dim);


	//Tuple2_t boardPosition = {.x = 16, .y = 16};
	//printf("*dim=(%2d,%2d)\n", dim.x, dim.y);
	//simOneStep(board, dim, boardB);
	//drawBoard(board, &dim, &boardPosition);
	//Sleep(2000); // format is Sleep(x); where x is # of milliseconds.
	//sleep(1);
	//for (;;) {
	//	// main loop goes here
	//}
	//drawBoard(boardB, &dim, &boardPosition);

	return 0;
}

void sim_step(unsigned short int *board, unsigned int rows) {
	for (unsigned int i = 0; i < rows; i++) {
		printf("*\n");
	}
}

