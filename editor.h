#include "rendering.h"
#include "utils.h"




#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED


int toggleCell(Board_t* b, unsigned int cellIdx);
int getCellTuple(const Board_t* b, Tuple2_t coord);
int getCellInts(const Board_t* b, int x, int y);

//#define getCell(_1, ... ) _Generic((_1), \
//									Tuple2_t: getCellTuple,				\
//									int )

//#define getCell(...) OVERLOAD(getCell, (__VA_ARGS__),	\
//	(getCellTuple, (Board_t*, Tuple2_t*)),				\
//	(getCellInts, (Board_t*, int, int))					\
//)
//
//#define OVERLOAD_ARG_TYPES (int, double)
//#define OVERLOAD_FUNCTIONS (print)
//#include "activate-overloads.h"



void fillZero(Board_t* b);
void fillChess(Board_t* b);
void fillDiagonal(unsigned long long int board[], Tuple2_t dim);

int enterEditorMode(Board_t* b);


int setCellInts(Board_t* b, int x, int y, int value);

#endif
