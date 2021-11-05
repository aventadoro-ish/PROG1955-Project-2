#define CELL_ALIVE '#'
#define CELL_DEAD '\''

#include "Project-2.h"

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

void drawBoard(unsigned long long int board[], unsigned int size,
                struct Coord* boardDimensions, struct Coord* offset);


#endif
