#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h> // notice this! you need it! (windows)


#ifndef UTILS_H
#define UTILS_H

#define BOARD_COLS 96
#define BOARD_ROWS 32

#define CELL_ALIVE_CHAR '#'
#define CELL_DEAD_CHAR ' '

#define BOARD_SCREEN_OFFSET_X 2
#define BOARD_SCREEN_OFFSET_Y 4


#define FILENAME_MAX_LEN 64

#define coordToCellIdx(coord) (unsigned int)coord.y * BOARD_COLS + coord.x
#define cellIdxToCoord(cellIdx) Tuple2_t coord = {coord.y = cellId / dim.x, coord.x = cellId - coord.y * dim.x}


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