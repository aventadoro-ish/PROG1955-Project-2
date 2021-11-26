#ifndef UTILS_H
#define UTILS_H

#define BOARD_COLS 96
#define BOARD_ROWS 32

#define coordToCellIdx(coord) (unsigned int)coord.y * BOARD_COLS + coord.x

typedef struct Tuple2_t {
	int x;
	int y;
} Tuple2_t;

typedef struct Board_t {
	unsigned int boardArr[96]; // 96x32
} Board_t;

#endif