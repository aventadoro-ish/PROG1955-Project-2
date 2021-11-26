#include "Project-2.h"
#include "rendering.h"


#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED


/* malloc() memory for a board, prints error message if fails
 * returns pointer to  
 */
Board_t* createBoard();

int toggleCell(Board_t* b, unsigned int cellIdx);

void fillZero(Board_t* b);
void fillChess(Board_t* b);
void fillDiagonal(unsigned long long int board[], Tuple2_t dim);

int enterEditorMode(Board_t* b);


#endif
