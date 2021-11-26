
#include "editor.h"



int toggleCell(Board_t* b, Tuple2_t coord) {
	unsigned int cellIdx = coordToCellIdx(coord);
	unsigned int idx = cellIdx / (sizeof(unsigned int) * 8);
	unsigned int bitPos = cellIdx % (sizeof(unsigned int) * 8);

	//unsigned int mask = 1 << (sizeof(unsigned int) * 8 - bitPos);
	unsigned int mask = 1 << bitPos;


	b->boardArr[idx] = b->boardArr[idx] ^ mask;

}


void fillZero(Board_t* b) {
	for (int i = 0; i < BOARD_COLS * BOARD_ROWS / (sizeof(unsigned int) * 8); i++) {
		b->boardArr[i] = 0;
	}
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
}

void fillDiagonal(unsigned long long int board[], Tuple2_t dim) {
	// TODO

	
}

int enterEditorMode(Board_t* b) {
	Tuple2_t cursour = { 0, 0 };
	drawBoard(b);

	for (;;) {

		if (_kbhit()) {
			int cmd = _getch(); // not safe on other platforms

			// exit
			if (cmd == '\x1b') break;

			else if (cmd == 'w') { --cursour.y; drawCursour(&cursour); } // UP
			else if (cmd == 'a') { --cursour.x; drawCursour(&cursour); } // LEFT
			else if (cmd == 'd') { ++cursour.x; drawCursour(&cursour); } // RIGHT
			else if (cmd == 's') { ++cursour.y; drawCursour(&cursour); } // DOWN
			else if (cmd == 224) {	// arrow keys modifier or something
				cmd = _getch();

				if (cmd == 72)		--cursour.y; // UP
				else if (cmd == 75) --cursour.x; // LEFT
				else if (cmd == 77) ++cursour.x; // RIGHT
				else if (cmd == 80) ++cursour.y; // DOWN
				else printf("**unknown modified keypress %d\n", cmd);

				drawCursour(&cursour);

			} else if (cmd == 13) { // ENTER -> toggle cell
				Tuple2_t coord = cursour;
				coord.x -= OFFSET_X - 1;
				coord.y -= OFFSET_Y - 1;

				unsigned int cellIdx = coordToCellIdx(coord);
				toggleCell(b, coord);
				drawBoard(b);

			} else {
				printf("* key pressed: %c %u\n", cmd, cmd);
			}
		}




	}
}