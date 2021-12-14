#include "editor.h"


void timeEditStampUpdate(Board_t* b) {
	time_t rawtime;
	time(&rawtime);
	b->timeLastEdited = *localtime(&rawtime);
}

int toggleCell(Board_t* b, Tuple2_t coord) {
	unsigned int cellIdx = coordToCellIdx(coord);
	unsigned int idx = cellIdx / (sizeof(unsigned int) * 8);
	unsigned int bitPos = cellIdx % (sizeof(unsigned int) * 8);

	//unsigned int mask = 1 << (sizeof(unsigned int) * 8 - bitPos);
	unsigned int mask = 1 << bitPos;


	b->boardArr[idx] = b->boardArr[idx] ^ mask;
	timeEditStampUpdate(b);
}


int getCellTuple(const Board_t* b, Tuple2_t coord) {
	unsigned int cellIdx = coordToCellIdx(coord);
	unsigned int idx = cellIdx / (sizeof(unsigned int) * 8);
	unsigned int bitPos = cellIdx % (sizeof(unsigned int) * 8);

	//unsigned int mask = 1 << (sizeof(unsigned int) * 8 - bitPos);
	unsigned int mask = 1 << bitPos;

	return (b->boardArr[idx] & mask) > 0;
}

int getCellInts(const Board_t* b, int x, int y) {
	if (x < 0 || y < 0 || x >= BOARD_COLS || y >= BOARD_ROWS) {
		return 0;
	}

	unsigned int cellIdx = y * BOARD_COLS + x;
	unsigned int idx = cellIdx / (sizeof(unsigned int) * 8);
	unsigned int bitPos = cellIdx % (sizeof(unsigned int) * 8);

	//unsigned int mask = 1 << (sizeof(unsigned int) * 8 - bitPos);
	unsigned int mask = 1 << bitPos;

	return (b->boardArr[idx] & mask) > 0;
}


int setCellInts(Board_t* b, int x, int y, int value) {
	unsigned int cellIdx = y * BOARD_COLS + x;
	unsigned int idx = cellIdx / (sizeof(unsigned int) * 8);
	unsigned int bitPos = cellIdx % (sizeof(unsigned int) * 8);

	//unsigned int mask = 1 << (sizeof(unsigned int) * 8 - bitPos);
	unsigned int mask = 1 << bitPos;

	if (x > BOARD_COLS || y > BOARD_ROWS) {
		printf("gesfigjfgsjegf\n");
	}
	else if (value) {
		b->boardArr[idx] = b->boardArr[idx] | mask;

	} else {
		b->boardArr[idx] = b->boardArr[idx] & ~mask;

	}
	timeEditStampUpdate(b);

}

int setCellTuple(Board_t* b, Tuple2_t coord, int value) {
	unsigned int cellIdx = coordToCellIdx(coord);
	unsigned int idx = cellIdx / (sizeof(unsigned int) * 8);
	unsigned int bitPos = cellIdx % (sizeof(unsigned int) * 8);

	//unsigned int mask = 1 << (sizeof(unsigned int) * 8 - bitPos);
	unsigned int mask = 1 << bitPos;
	if (value) {
		b->boardArr[idx] = b->boardArr[idx] | mask;

	}
	else {
		b->boardArr[idx] = b->boardArr[idx] & ~mask;

	}
	timeEditStampUpdate(b);

}



void fillZero(Board_t* b) {
	for (int i = 0; i < BOARD_COLS * BOARD_ROWS / (sizeof(unsigned int) * 8); i++) {
		b->boardArr[i] = 0;
	}

	timeEditStampUpdate(b);

}

void fillChess(Board_t* b) {
	unsigned long long int cellId = 0;
	unsigned int mask = 0b01010101010101010101010101010101;

	for (int y = 0; y < BOARD_ROWS * BOARD_COLS / (sizeof(unsigned int) * 8); y++) {
		if (y % 6 > 2) {
			b->boardArr[y] = mask;
		} else {
			b->boardArr[y] = mask << 1;
		}
	}

	timeEditStampUpdate(b);

}

void fillDiagonal(unsigned long long int board[], Tuple2_t dim) {
	// TODO

	//timeEditStampUpdate(b);

}

void fillStartPattern(Board_t* b) {
	// TODO this method
	fillChess(b);
	timeEditStampUpdate(b);

}

int enterEditorMode(Board_t* b) {
	drawBoard(b);

	Tuple2_t cursor = { BOARD_SCREEN_OFFSET_X, BOARD_SCREEN_OFFSET_Y };
	movecursor(&cursor);

	for (;;) {

		if (_kbhit()) {
			int cmd = _getch(); // not safe on other platforms
			// exit
			if (cmd == '\x1b') break;

			else if (cmd == 'w') { --cursor.y; movecursor(&cursor); } // UP
			else if (cmd == 'a') { --cursor.x; movecursor(&cursor); } // LEFT
			else if (cmd == 'd') { ++cursor.x; movecursor(&cursor); } // RIGHT
			else if (cmd == 's') { ++cursor.y; movecursor(&cursor); } // DOWN
			else if (cmd == 224) {	// arrow keys modifier or something
				cmd = _getch();

				if (cmd == 72)		--cursor.y; // UP
				else if (cmd == 75) --cursor.x; // LEFT
				else if (cmd == 77) ++cursor.x; // RIGHT
				else if (cmd == 80) ++cursor.y; // DOWN
				else printf("**unknown modified keypress %d\n", cmd);

				movecursor(&cursor);

			} else if (cmd == 13) { // ENTER -> toggle cell
				Tuple2_t coord = cursor;
				coord.x -= BOARD_SCREEN_OFFSET_X;
				coord.y -= BOARD_SCREEN_OFFSET_Y;

				unsigned int cellIdx = coordToCellIdx(coord);
				toggleCell(b, coord);
				drawBoard(b);

			} else {
				printf("* key pressed: %c %u\n", cmd, cmd);
			}
		}




	}
	timeEditStampUpdate(b);

}