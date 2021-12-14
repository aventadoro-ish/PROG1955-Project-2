#include "utils.h"

#ifndef SAVES_H_
#define SAVES_H_
/* ^^ these are the include guards */

/* Prototypes for the functions */

void saveBoard(Board_t* saveBoards[]);
Board_t* loadSaves();


int compareBoards(Board_t* boardA, Board_t* boardB);

/* sortBy:
 *	0 - saveName
 *	1 - timeCreated ascending
 *	2 - timeCreated descending
 *	3 - timeLastEdited ascending
 *	4 - timeLastEdited ascending
 */
Board_t* sortBoards(Board_t* sortThis[], int sortBy);
int searchSaves(Board_t* searchThis);


#endif
