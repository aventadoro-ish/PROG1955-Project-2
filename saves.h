#ifndef SAVES_H_
#define SAVES_H_

#include "utils.h"

/* takes a NULL-terminated array of Board_t* and saves them all into the save file
 */
void saveBoardArr(Board_t* saveBoards[]);

/* creates NULL-terminated array of Board_t* from the save file
 */
Board_t* loadSavedBoardArr();

// legacy compare method
int compareBoards(Board_t* boardA, Board_t* boardB);

/* Takes a NULL-terminated array of Board_t* and sorts it according to
 * sortBy:
 *	0 - saveName
 *	1 - timeCreated ascending
 *	2 - timeCreated descending
 *	3 - timeLastEdited ascending
 *	4 - timeLastEdited ascending
 */
Board_t* sortBoards(Board_t* sortThis[], int sortBy);

// TODO - implement. Now it has no use, sadly
int searchSaves(Board_t* searchThis);


#endif
