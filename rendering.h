#include "utils.h"

#ifndef RENDERING_H_
#define RENDERING_H_


#define CELL_ALIVE '#'
#define CELL_DEAD ' '

#define OFFSET_X 2
#define OFFSET_Y 4


void drawBoard(const Board_t* b);
void drawCursour(const Tuple2_t* coord); // TODO rename to moveCursour()

void drawFrame(Tuple2_t pos, Tuple2_t dim);
void printText(Tuple2_t pos, char* str);


void setupConsole(void);


#endif
