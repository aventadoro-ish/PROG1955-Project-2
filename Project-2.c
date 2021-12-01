#include "Project-2.h"


int main() {
	printf("For this program to work correctly, You have to maximize console window.\n");
	printf("Press any button, when You're ready...");
	while (!_kbhit());
	_getch();
	
	Tuple2_t temp = intsToTuple(0, 0);

	moveCursour(&temp);
	printf("                                                                         \n"
		   "                                                                         ");


	//Tuple2_t pos = {BOARD_SCREEN_OFFSET_X - 1, BOARD_SCREEN_OFFSET_Y - 1};
	Tuple2_t dim = {BOARD_COLS + 2, BOARD_ROWS + 2};

	//drawFrame(&pos, &dim, 0);

	drawScreenSections();
	temp.x = 2;
	temp.y = 1;
	moveCursour(&temp);
	printTitle();

	

	Tuple2_t ui = { BOARD_SCREEN_OFFSET_X + BOARD_COLS + 2, BOARD_SCREEN_OFFSET_Y};
	printText(&ui, "Hello There!", 1);
	
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

		//Sleep(500);

		simStep(boardB, board);
		fillZero(boardB);
		drawBoard(board);

		//Sleep(500);
		if (_kbhit()) {
			break;
		}
	}


	moveCursour(&dim);

	



	return 0;
}


void drawScreenSections() {
	Tuple2_t pos;
	Tuple2_t dim;

	// draw title frame
	pos.x = 1;
	pos.y = 0;

	dim.x = BOARD_COLS + INFO_X;
	dim.y = BOARD_SCREEN_OFFSET_Y;

	drawFrame(&pos, &dim, 1);

	// draw main game board
	pos.x = BOARD_SCREEN_OFFSET_X - 1;
	pos.y = BOARD_SCREEN_OFFSET_Y - 1;

	dim.x = BOARD_COLS + 2;
	dim.y = BOARD_ROWS + 2;

	drawFrame(&pos, &dim, 1);


	// draw info board
	pos.x = BOARD_SCREEN_OFFSET_X + BOARD_COLS;
	pos.y = BOARD_SCREEN_OFFSET_Y - 1;

	dim.x = INFO_X - 1;
	dim.y = BOARD_ROWS + 2;

	drawFrame(&pos, &dim, 1);
}

void printTitle() {
	char title[] = { 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x20 , 0x2e , 0x20 , 0x2e , 0x20 , 0x2e , 0x20 , 0x2e , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x20 , 0x2e , 0x20 , 0x60 , 0x27 , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x20 , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x20 , 0x20 , 0x2e , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x20 , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x20 , 0x20 , 0x2e , 0x20 , 0x20 , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x0a , 0x7c , 0x20 , 0x20 , 0x20 , 0x7c , 0x20 , 0x7c , 0x20 , 0x7c , 0x5c , 0x7c , 0x20 , 0x7c , 0x20 , 0x7c , 0x20 , 0x7c , 0x20 , 0x7c , 0x2d , 0x7c , 0x20 , 0x20 , 0x7c , 0x20 , 0x20 , 0x60 , 0x27 , 0x20 , 0x60 , 0x2d , 0x2e , 0x20 , 0x20 , 0x20 , 0x7c , 0x2e , 0x2e , 0x20 , 0x7c , 0x2d , 0x7c , 0x20 , 0x7c , 0x5c , 0x2f , 0x7c , 0x20 , 0x7c , 0x2d , 0x20 , 0x20 , 0x20 , 0x20 , 0x7c , 0x20 , 0x7c , 0x20 , 0x7c , 0x2d , 0x20 , 0x20 , 0x20 , 0x20 , 0x7c , 0x20 , 0x20 , 0x20 , 0x20 , 0x7c , 0x20 , 0x20 , 0x7c , 0x2d , 0x20 , 0x20 , 0x7c , 0x2d , 0x20 , 0x20 , 0x0a , 0x60 , 0x2d , 0x27 , 0x20 , 0x60 , 0x2d , 0x27 , 0x20 , 0x27 , 0x20 , 0x60 , 0x20 , 0x60 , 0x2e , 0x27 , 0x2e , 0x27 , 0x20 , 0x60 , 0x20 , 0x27 , 0x20 , 0x20 , 0x60 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x60 , 0x2d , 0x27 , 0x20 , 0x20 , 0x20 , 0x60 , 0x2d , 0x27 , 0x20 , 0x60 , 0x20 , 0x27 , 0x20 , 0x27 , 0x20 , 0x20 , 0x60 , 0x20 , 0x60 , 0x2d , 0x27 , 0x20 , 0x20 , 0x20 , 0x60 , 0x2d , 0x27 , 0x20 , 0x27 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x60 , 0x2d , 0x27 , 0x20 , 0x60 , 0x2d , 0x27 , 0x20 , 0x27 , 0x20 , 0x20 , 0x20 , 0x60 , 0x2d , 0x27, 0x00};

	Tuple2_t pos;

	pos.x = 30;
	pos.y = 1;

	printText(&pos, title, 1);
	//moveCursour(&pos);
	//printf("\x0a \x2e \x2d \x2e \x20 \x2e \x2d \x2e \x20 \x2e \x20 \x2e \x20 \x2e \x20 \x2e \x20 \x2e \x20 \x2e \x2d \x2e \x20 \x2e \x20 \x2e \x20 \x60 \x27 \x20 \x2e \x2d \x2e \x20 \x20 \x20 \x2e \x2d \x2e \x20 \x2e \x2d \x2e \x20 \x2e \x20 \x20 \x2e \x20 \x2e \x2d \x2e \x20 \x20 \x20 \x2e \x2d \x2e \x20 \x2e \x2d \x2e \x20 \x20 \x20 \x2e \x20 \x20 \x20 \x2e \x2d \x2e \x20 \x2e \x2d \x2e \x20 \x2e \x2d \x2e \x20 \x0a \x7c \x20 \x20 \x20 \x7c \x20 \x7c \x20 \x7c \x5c \x7c \x20 \x7c \x20 \x7c \x20 \x7c \x20 \x7c \x2d \x7c \x20 \x20 \x7c \x20 \x20 \x60 \x27 \x20 \x60 \x2d \x2e \x20 \x20 \x20 \x7c \x2e \x2e \x20 \x7c \x2d \x7c \x20 \x7c \x5c \x2f \x7c \x20 \x7c \x2d \x20 \x20 \x20 \x20 \x7c \x20 \x7c \x20 \x7c \x2d \x20 \x20 \x20 \x20 \x7c \x20 \x20 \x20 \x20 \x7c \x20 \x20 \x7c \x2d \x20 \x20 \x7c \x2d \x20 \x20 \x0a \x60 \x2d \x27 \x20 \x60 \x2d \x27 \x20 \x27 \x20 \x60 \x20 \x60 \x2e \x27 \x2e \x27 \x20 \x60 \x20 \x27 \x20 \x20 \x60 \x20 \x20 \x20 \x20 \x20 \x60 \x2d \x27 \x20 \x20 \x20 \x60 \x2d \x27 \x20 \x60 \x20 \x27 \x20 \x27 \x20 \x20 \x60 \x20 \x60 \x2d \x27 \x20 \x20 \x20 \x60 \x2d \x27 \x20 \x27 \x20 \x20 \x20 \x20 \x20 \x60 \x2d \x27 \x20 \x60 \x2d \x27 \x20 \x27 \x20 \x20 \x20 \x60 \x2d \x27 \x20 \x0a \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x0a");
	//printf("%s", title);
}

