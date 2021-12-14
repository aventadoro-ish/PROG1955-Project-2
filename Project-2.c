#include "Project-2.h"

#define MAIN_MENU_TEXT "Main menu:\n-New Game\n-Load\n-Delete\n-Exit\n"


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

	Board_t** savedBoardArr = loadSaves();

	mainMenu(savedBoardArr);
	
	temp.x = 0;
	temp.y = BOARD_SCREEN_OFFSET_Y + BOARD_ROWS + 1;
	movecursor(&temp);

	return 0;
}


void mainMenu(Board_t* savedBoardArr[]) {
	drawToMenuSection(MAIN_MENU_TEXT, 0);

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

				if (cmd == 72) {
					--cursor.y; // UP
					movecursor(&cursor);

				} else if (cmd == 80) {
					++cursor.y; // DOWN
					movecursor(&cursor);
				} else printf("**unknown modified keypress %d\n", cmd);

				break;
			}
			case 13: { // ENTER
				unsigned int selectedPos = cursor.y - BOARD_SCREEN_OFFSET_Y;

				switch (selectedPos) {
				case 1: // newGame
					savedBoardArr = newGameStart(savedBoardArr);
					drawToMenuSection(MAIN_MENU_TEXT, 0);
					movecursor(&cursor);
					break;

				case 2: // Load
					savedBoardArr = loadSavesMenu(savedBoardArr);
					drawToMenuSection(MAIN_MENU_TEXT, 0);
					movecursor(&cursor);
					break;

				case 3:
					savedBoardArr = loadDeleteSavesMenu(savedBoardArr);
					drawToMenuSection(MAIN_MENU_TEXT, 0);
					movecursor(&cursor);
					break;

				case 4: // Exit
					// Some other action TODO
					isRunning = 0;
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

	saveBoard(savedBoardArr);

	for (int i = 0; i < boardArrayLen(savedBoardArr); i++) {
		free(savedBoardArr[i]);
	}

	free(savedBoardArr);

	free(boardA);
	free(boardB);
}

Board_t** newGameStart(Board_t* savedBoardArr[]) {
	drawToMenuSection("\nNew Game\n"
        "*use arrow keys or ASWD to move cursor\n"
        "*use ENTER to toggle cell value\n"
        "*press ESCAPE once to start simulation\n"
		"*press ESCAPE second time to exit\n", 1);

	Board_t* board = createBoard();
	fillZero(board);
	enterEditorMode(board);

	savedBoardArr = selectBoard(board, savedBoardArr, 0, 1, 1);

	//free(board);

	return savedBoardArr;
}

Board_t** loadSavesMenu(Board_t* savedBoardArr[]) {
	int sortingMode = 0;
	char sortingModeNames[][18] = { "alphabetic asc", "date created asc", "date created dec",
							"date modified asc", "date modified dec"};

	sortBoards(savedBoardArr, sortingMode);
	printLoadMenu(savedBoardArr, sortingModeNames[sortingMode]);

	Tuple2_t cursor = { BOARD_SCREEN_OFFSET_X + BOARD_COLS + 2, BOARD_SCREEN_OFFSET_Y + 1 };
	movecursor(&cursor);

	int isRunning = 1;
	int isCursorMoved = 0;

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
				isCursorMoved = 1;
				break;
			}
			case 's': {
				++cursor.y;
				movecursor(&cursor);
				isCursorMoved = 1;
				break;
			}
			case 224: { // special char
				cmd = _getch();

				if (cmd == 72) {
					--cursor.y; // UP
					isCursorMoved = 1;
					movecursor(&cursor);

				} else if (cmd == 80) {
					++cursor.y; // DOWN
					isCursorMoved = 1;
					movecursor(&cursor);

				} else printf("**unknown modified keypress %d\n", cmd);

				break;
			}
			case 13: { // ENTER
				unsigned int selectedPos = cursor.y - BOARD_SCREEN_OFFSET_Y;
				if (selectedPos == 0) {
					isRunning = 0;
					saveBoard(savedBoardArr);

				} else if (selectedPos == 1) {
					sortingMode = (sortingMode + 1) % 
						(sizeof(sortingModeNames) / sizeof(sortingModeNames[0]));

					sortBoards(savedBoardArr, sortingMode);
					printLoadMenu(savedBoardArr, sortingModeNames[sortingMode]);

				} else if (2 < selectedPos && selectedPos < 3 + boardArrayLen(savedBoardArr)) {
					savedBoardArr = selectBoard(savedBoardArr[selectedPos - 3], savedBoardArr, 1, 1, 1);

				} else {
					// do nothing
				}

				break;
			}
			default:
				printf("**unknown keypress %d\n", cmd);
				break;
			};

		}

		if (isCursorMoved) {
			int cursorRelPosY = cursor.y - BOARD_SCREEN_OFFSET_Y;
			if (2 < cursorRelPosY && cursorRelPosY < 3 + boardArrayLen(savedBoardArr)) {
				drawBoard(savedBoardArr[cursorRelPosY - 3]);
			}
			isCursorMoved = 0;
		}
	}

	return savedBoardArr;
}

Board_t** loadDeleteSavesMenu(Board_t* savedBoardArr[]) {
	printDeleteMenu(savedBoardArr);

	Tuple2_t cursor = { BOARD_SCREEN_OFFSET_X + BOARD_COLS + 2, BOARD_SCREEN_OFFSET_Y + 1 };
	movecursor(&cursor);

	int isRunning = 1;
	int isCursorMoved = 0;

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
				isCursorMoved = 1;
				break;
			}
			case 's': {
				++cursor.y;
				movecursor(&cursor);
				isCursorMoved = 1;
				break;
			}
			case 224: { // special char
				cmd = _getch();

				if (cmd == 72) {
					--cursor.y; // UP
					isCursorMoved = 1;
					movecursor(&cursor);

				}
				else if (cmd == 80) {
					++cursor.y; // DOWN
					isCursorMoved = 1;
					movecursor(&cursor);

				}
				else printf("**unknown modified keypress %d\n", cmd);

				break;
			}
			case 13: { // ENTER
				unsigned int selectedPos = cursor.y - BOARD_SCREEN_OFFSET_Y;
				if (selectedPos == 0) {
					isRunning = 0;
					saveBoard(savedBoardArr);

				}
				else if (1 < selectedPos && selectedPos < 2 + boardArrayLen(savedBoardArr)) {
					savedBoardArr = deleteBoardProcedure(savedBoardArr[selectedPos - 2], savedBoardArr);
					printDeleteMenu(savedBoardArr);

				}
				else {
					printf("*%d", selectedPos);
					// do nothing
				}

				break;
			}
			default:
				printf("**unknown keypress %d\n", cmd);
				break;
			};

		}

		if (isCursorMoved) {
			int cursorRelPosY = cursor.y - BOARD_SCREEN_OFFSET_Y;
			if (2 < cursorRelPosY && cursorRelPosY < 3 + boardArrayLen(savedBoardArr)) {
				drawBoard(savedBoardArr[cursorRelPosY - 3]);
			}
			isCursorMoved = 0;
		}
	}

	return savedBoardArr;
}



Board_t* simulation(Board_t* boardA, double timestep) {
	
	Board_t* boardB = createBoardCopy(boardA);
	fillZero(boardB);

	int isBoardAActive = 1;
	int isRunning = 1;
	clock_t lastStepTime = clock();


	while (isRunning) {
		clock_t curTime = clock();
		if (((double)curTime - lastStepTime) / CLOCKS_PER_SEC > timestep) {
			if (isBoardAActive) {
				simStep(boardA, boardB);
				drawBoard(boardB);
				fillZero(boardA);

			} else {
				simStep(boardB, boardA);
				drawBoard(boardA);
				fillZero(boardB);
			}

			isBoardAActive = isBoardAActive ? 0 : 1; // toggle active board

			lastStepTime = curTime;
		}

		if (_kbhit()) {
			if (_getch() == '\x1b') {
				isRunning = 0;
			}
		}
	}

	if (!isBoardAActive) {
		copyBoard(boardB, boardA);
	}

	free(boardB);
	return boardA;

}

Board_t** saveProcedure(Board_t* board, Board_t* savedBoardArr[]) {
	int isBoardIncludedInArray = 0;

	for (int i = 0; i < boardArrayLen(savedBoardArr); i++) {
		char* a = board->name;
		char* b = savedBoardArr[i]->name;
		//int isInstanceMatch = board == savedBoardArr[i];
		int isInstanceMatch = a == b;


		if (isInstanceMatch) {
			isBoardIncludedInArray = 1;
			break;
		}
	}

	if (!isBoardIncludedInArray) {
		char* saveName = promptMenuStr("Enter save name:", FILENAME_MAX);
		if (saveName == NULL) {
			drawToMenuSection("Save name error!", 0);
			return 1;
		}

		strcpy(board->name, saveName);
		free(saveName);

		savedBoardArr = addNewBoard(savedBoardArr, board);
	}

	//time_t rawtime;
	//time(&rawtime);
	//board->timeLastEdited = *localtime(&rawtime);

	//Board_t* saveBoardArr[2] = { board, NULL };

	saveBoard(savedBoardArr);

	// TODO actual save

	drawToMenuSection("Save completed! Press any button!", 0);
	while (!_kbhit());
	_getch();

	return savedBoardArr;
}

Board_t** selectBoard(Board_t* board, Board_t* savedBoardArr[], int doPromptEdit, int doPromptRun, int doPromptSave) {
	char c;

	if (doPromptEdit) {
		c = promptMenuChar("Edit board? y/n", "yn");
		if (c == 'y') {
			enterEditorMode(board);

		}
	}

	if (doPromptRun) {
		c = promptMenuChar("Run Simulation? y/n", "yn");

		if (c == 'y') {
			double simSpeedSeconds = 
				promptMenuDouble("Enter timestep in seconds (0 <= x <= 60.0):", 0.0, 60.0);

			board = simulation(board, simSpeedSeconds);
		}
	}
	
	if (doPromptSave) {
		c = promptMenuChar("Save board? y/n", "yn");
		if (c == 'y') {
			savedBoardArr = saveProcedure(board, savedBoardArr);
		}
	}

	return savedBoardArr;
}

Board_t** deleteBoardProcedure(Board_t* board, Board_t* savedBoardArr[]) {
	char c = promptMenuChar("Are you sure you want do delete it?", "yn");
	if (c == 'n') return savedBoardArr;

	int isBoardIncludedInArray = 0;

	for (int i = 0; i < boardArrayLen(savedBoardArr); i++) {
		char* a = board->name;
		char* b = savedBoardArr[i]->name;
		//int isInstanceMatch = board == savedBoardArr[i];
		int isInstanceMatch = a == b;


		if (isInstanceMatch) {
			isBoardIncludedInArray = 1;
			break;
		}
	}

	if (!isBoardIncludedInArray) {
		printf("Deleted~");
		free(board);
		return savedBoardArr;
	}

	savedBoardArr = deleteBoard(board, savedBoardArr);




}



int promptMenuInt(char* promptText, int min, int max) {
	drawToMenuSection(promptText, 4);
	int val;
	printf("\x1B[s");

	for (;;) {
		scanf_s("%d", &val);
		while (getchar() != '\n');

		if (min <= val && val <= max) {
			return val;
		}
		printf("\x1B[u");
	}
}

char promptMenuChar(char* promptText, char* allowedChars) {
	drawToMenuSection(promptText, 4);
	char c;
	printf("\x1B[s");

	for (;;) {
		scanf_s("%c", &c, 15);
		while (getchar() != '\n');

		if (charOccurrences(allowedChars, c) > 0) {
			return c;

		}
		printf("\x1B[u");

	}

	return c;
}

double promptMenuDouble(char* promptText, double min, double max) {
	drawToMenuSection(promptText, 4);
	double val;
	printf("\x1B[s");

	for (;;) {
		scanf_s("%lf", &val);
		while (getchar() != '\n');

		if (min <= val && val <= max) {
			return val;
		}
		printf("\x1B[u");
	}
}

// uses malloc()!
char* promptMenuStr(char* promptText, int maxLen) {
	char* str = (char*)malloc(sizeof(char) * ++maxLen);
	if (str == NULL) return NULL;
	drawToMenuSection(promptText, 4);
	printf("\x1B[s");


	scanf_s("%s", str, maxLen);

	printf("\x1B[u");

	return str;
}