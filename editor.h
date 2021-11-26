#include "rendering.h"
#include "utils.h"




#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED




int toggleCell(Board_t* b, unsigned int cellIdx);

void fillZero(Board_t* b);
void fillChess(Board_t* b);
void fillDiagonal(unsigned long long int board[], Tuple2_t dim);

int enterEditorMode(Board_t* b);


#endif
