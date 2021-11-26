#include "utils.h"
#include "editor.h"


#ifndef SIMULATION_H_
#define SIMULATION_H_

// Counts neighbouring cells
int getNeighbours(const Board_t* b, int x, int y);

// Runs simulation on board and stores the restult into cpy
int simStep(Board_t* board, Board_t* cpy);

#endif
