#include "utils.h"

#ifndef RENDERING_H_
#define RENDERING_H_


#define CELL_ALIVE '#'
#define CELL_DEAD ' '

#define OFFSET_X 2
#define OFFSET_Y 4


void drawBoard(const Board_t* b);
void moveCursour(const Tuple2_t* coord);

void drawFrame(Tuple2_t* pos, Tuple2_t* dim, int doReturnCursour);
void printText(Tuple2_t* pos, char* str, int doReturnCurour);


#endif
