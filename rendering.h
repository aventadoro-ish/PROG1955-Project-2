#ifndef RENDERING_H_
#define RENDERING_H_

#include "utils.h"

/* Draws a game-board board[] of size boardDimensions to console with a preset offset */
void drawBoard(const Board_t* b);

void moveCursour(const Tuple2_t* coord);

void drawFrame(const Tuple2_t* pos, const Tuple2_t* dim, int doReturnCursour);
void printText(Tuple2_t* pos, char* str, int doReturnCursour);


#endif