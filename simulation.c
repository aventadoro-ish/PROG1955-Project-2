#include "simulation.h"

int getCell(board_t_depr* board, Tuple2_t dim, int x, int y) {
	Tuple2_t coord = { x, y };
	unsigned long long int cellIdx = coordToCellIdx(coord, dim);

	unsigned int idx = cellIdx / (sizeof(board_t_depr) * 8);
	unsigned int bitPos = cellIdx % (sizeof(board_t_depr) * 8);
	return board[idx] & ((unsigned long long int) 1 << bitPos) > 0;

}

void setCell(board_t_depr* board, Tuple2_t dim, int x, int y) {
	Tuple2_t coord = { x, y };
	unsigned long long int cellIdx = coordToCellIdx(coord, dim);

	unsigned int idx = cellIdx / (sizeof(board_t_depr) * 8);
	unsigned int bitPos = cellIdx % (sizeof(board_t_depr) * 8);

	board[idx] = board[idx] | ((unsigned long long int) 1 << bitPos);

}

int countNeighbours(board_t_depr* board, Tuple2_t dim, Tuple2_t coord) {
	int count = 0;
	count += getCell(board, dim, coord.x + 1, coord.y + 1);
	count += getCell(board, dim, coord.x    , coord.y + 1);
	count += getCell(board, dim, coord.x - 1, coord.y + 1);

	count += getCell(board, dim, coord.x + 1, coord.y + 1);
	count += getCell(board, dim, coord.x + 1, coord.y + 1);

	count += getCell(board, dim, coord.x + 1, coord.y - 1);
	count += getCell(board, dim, coord.x    , coord.y - 1);
	count += getCell(board, dim, coord.x + 1, coord.y - 1);

	return count;


}

void simOneStep(board_t_depr* board, Tuple2_t dim, board_t_depr* res) {
	for (int y = 0; y < dim.y; y++) {
		for (int x = dim.x; x >= 0; x--) {
			Tuple2_t coord = { x, y };
			int count = countNeighbours(board, dim, coord);
			printf("%2d|", count);
			if (count < 2) {
				setCell(res, dim, x, y);
			}
		}
	}
}