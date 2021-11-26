#include <time.h>

#ifndef UTILS_H
#define UTILS_H

#define BOARD_COLS 96
#define BOARD_ROWS 32

#define FILENAME_MAX_LEN 64

#define coordToCellIdx(coord) (unsigned int)coord.y * BOARD_COLS + coord.x

typedef struct Tuple2_t {
	int x;
	int y;
} Tuple2_t;

typedef struct Board_t {
	unsigned int boardArr[96]; // 96x32
	char name[64];
	struct tm timeCreated;
	struct tm timeLastEdited;

} Board_t;

/* malloc() memory for a board, prints error message if fails
 * returns pointer to
 */
Board_t* createBoard();

#endif