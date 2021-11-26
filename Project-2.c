
#include "Project-2.h"


/*
 */

int main() {
	printf("Press any button...");
	while (!_kbhit());
	_getch();


	Tuple2_t pos = {OFFSET_X - 1, OFFSET_Y - 1};
	Tuple2_t dim = {BOARD_COLS + 2, BOARD_ROWS + 2};

	drawFrame(&pos, &dim, 0);
	
	Board_t* board = createBoard();
	Board_t* boardB = createBoard();

	fillZero(board);
	fillZero(boardB);

	//drawBoard(board);
	enterEditorMode(board);


	for (;;) {
		simStep(board, boardB);
		drawBoard(boardB);
		fillZero(board);

		Sleep(500);

		simStep(boardB, board);
		drawBoard(board);
		fillZero(boardB);

		Sleep(500);

	}

	

	moveCursour(&dim);

	


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

