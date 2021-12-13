#include "utils.h"

#ifndef SAVES_H_
#define SAVES_H_
/* ^^ these are the include guards */

/* Prototypes for the functions */

void saveBoard(Board_t* saveBoards);
int compareBoards(Board_t* boardA, Board_t* boardB);
Board_t* sortBoards(Board_t* sortThis);
int searchSaves(Board_t* searchThis);


#endif
