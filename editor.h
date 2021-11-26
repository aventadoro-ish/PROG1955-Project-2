#include "rendering.h"
#include "utils.h"




#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED


int toggleCell(Board_t* b, Tuple2_t coord);

int getCellTuple(const Board_t* b, Tuple2_t coord);
int getCellInts(const Board_t* b, int x, int y);

int setCellInts(Board_t* b, int x, int y, int value);
int setCellTuple(Board_t* b, Tuple2_t coord, int value);


// Fills the given board with all zeros
void fillZero(Board_t* b);

// Fills the given board with chess-like pattern
void fillChess(Board_t* b);

// Doesn't work for now
void fillDiagonal(unsigned long long int board[], Tuple2_t dim);

// Enter board editor mode to setup a board
//	ENTER toggles selected cell ; [ASWD or arrow keys] move cursour around
int enterEditorMode(Board_t* b);




#endif
