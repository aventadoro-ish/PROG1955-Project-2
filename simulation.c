#include "simulation.h"

int getNeighbours(const Board_t* b, int x, int y) {
	int n = 0;
	n += getCellInts(b, x - 1, y - 1);
	n += getCellInts(b, x    , y - 1);
	n += getCellInts(b, x + 1, y - 1);

	n += getCellInts(b, x + 1, y);
	n += getCellInts(b, x - 1, y);

	n += getCellInts(b, x - 1, y + 1);
	n += getCellInts(b, x    , y + 1);
	n += getCellInts(b, x + 1, y + 1);

	return n;
}

int simStep(Board_t* board, Board_t* cpy) {
	// TOOD proper borders
	for (int y = 0; y < BOARD_ROWS; y++) {
		for (int x = 0; x < BOARD_COLS; x++) {
			int neighbours = getNeighbours(board, x, y);

			//if (getCellInts(board, x, y)) {
			//	if (!(neighbours == 2 || neighbours == 3)) setCellInts(cpy, x, y, 0);
			//} else {
			//	if (neighbours == 3) setCellInts(cpy, x, y, 1);
			//}

			if (getCellInts(board, x, y)) {
				if (neighbours < 2) setCellInts(cpy, x, y, 0); // 1.
				else if (neighbours == 2 || neighbours == 3) setCellInts(cpy, x, y, 1); // 2.
				else if (neighbours > 3) setCellInts(cpy, x, y, 0); // 3.

			} else {
				if (neighbours == 3) setCellInts(cpy, x, y, 1); // 4.
			}

		}
	}

	return 0;
}


