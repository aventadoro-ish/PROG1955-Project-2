#include "utils.h"
#include "editor.h"


#ifndef SIMULATION_H_
#define SIMULATION_H_

int getNeighbours(const Board_t* b, int x, int y);
int simStep(Board_t* board, Board_t* cpy);

#endif
