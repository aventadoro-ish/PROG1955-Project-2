#include "Project-2.h"


int main() {
	printf("For this program to work correctly, You have to maximize console window.\n");
	printf("Press any button, when You're ready...");
	while (!_kbhit());
	_getch();
	
	Tuple2_t temp = { .x = 0, .y = 0 };

	// erase caution info
	movecursor(&temp);
	printf("                                                                         \n"
		   "                                                                         ");

	drawScreenSections();
	printTitle();


	mainMenu();
	
	temp.x = 0;
	temp.y = BOARD_SCREEN_OFFSET_Y + BOARD_ROWS + 1;
	movecursor(&temp);


	//Board_t* board = createBoard();
	//Board_t* boardB = createBoard();
	//
	//fillZero(board);
	//fillZero(boardB);
	//
	////drawBoard(board);
	//enterEditorMode(board);
	//
	//for (;;) {
	//	simStep(board, boardB);
	//	drawBoard(boardB);
	//	fillZero(board);
	//
	//	//Sleep(500);
	//
	//	simStep(boardB, board);
	//	fillZero(boardB);
	//	drawBoard(board);
	//
	//	//Sleep(500);
	//	if (_kbhit()) {
	//		break;
	//	}
	//}

	return 0;
}


void mainMenu() {
	printMainMenu();

	Tuple2_t cursor = { BOARD_SCREEN_OFFSET_X + BOARD_COLS + 2, BOARD_SCREEN_OFFSET_Y + 1 };

	movecursor(&cursor);

	clock_t lastWaitAnimation = clock();

	Board_t* boardA = createBoard();
	Board_t* boardB = createBoard();

	fillZero(boardA);
	fillZero(boardB);

	drawBoard(boardA);

	int isRunning = 1;
	while (isRunning) {
		clock_t curTime = clock();

		if (_kbhit()) { // key press input

			int cmd = _getch(); // not safe on other platforms?

			switch (cmd) {
			case '\x1b': {
				isRunning = 0; // exit
				break;
			}
			case 'w': {
				--cursor.y;
				movecursor(&cursor);
				break;
			}
			case 's': {
				++cursor.y;
				movecursor(&cursor); 
				break;
			}
			case 224: { // special char
				cmd = _getch();

				if (cmd == 72)		--cursor.y; // UP
				else if (cmd == 80) ++cursor.y; // DOWN
				else printf("**unknown modified keypress %d\n", cmd);

				movecursor(&cursor);
				break;
			}
			case 13: { // ENTER
				unsigned int selectedPos = cursor.y - BOARD_SCREEN_OFFSET_Y;

				switch (selectedPos) {
				case 1: // newGame
					newGameStart();
					movecursor(&cursor);
					printMainMenu();
					break;
				case 2: // Load
					// Some action TODO
					break;
				case 3: // Exit
					// Some other action TODO
					isRunning = 0;
					free(boardA);
					free(boardB);
					break;

				default:
					break;
				}

				break;
			}


			default:
				printf("**unknown keypress %d\n", cmd);
				break;
			};

		}

		if (((double)curTime - lastWaitAnimation) / CLOCKS_PER_SEC > 1) { // idle animation
			simStep(boardA, boardB);
			drawBoard(boardB);
			fillZero(boardA);


			Board_t* temp = boardA;
			boardA = boardB;
			boardB = temp;

			lastWaitAnimation = curTime;
		}

	}
}


void newGameStart() {
	printNewGameMenu();
	Board_t* boardA = createBoard();

	fillZero(boardA);

	enterEditorMode(boardA);

	// TODO simulation speed?

	boardA = simulation(boardA, 0.25);
	// TODO prompt save or not?

	free(boardA);
	return NULL;
}

Board_t* simulation(Board_t* boardA, double timestep) {
	
	Board_t* boardB = createBoard();
	fillZero(boardB);

	int isBoardAActive = 1;
	int isRunning = 1;
	clock_t lastStepTime = clock();



	while (isRunning) {
		clock_t curTime = clock();
		if (((double)curTime - lastStepTime) / CLOCKS_PER_SEC > timestep) {
			simStep(boardA, boardB);
			drawBoard(boardB);
			fillZero(boardA);

			isBoardAActive = isBoardAActive ? 0 : 1; // toggle active board

			Board_t* temp = boardA;
			boardA = boardB;
			boardB = temp;
			
			lastStepTime = curTime;
		}

		if (_kbhit()) {
			if (_getch() == '\x1b') {
				isRunning = 0;
			}
		}
	}

	if (isBoardAActive) {
		free(boardB);
		return boardA;

	} else {
		free(boardA);
		return boardB;
	}

}