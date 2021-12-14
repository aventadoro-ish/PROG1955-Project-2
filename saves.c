#include "saves.h"

int compareBoardByNameAsc(Board_t* boardA, Board_t* boardB);
int compareBoardByTimeCreatedAsc(Board_t* boardA, Board_t* boardB);
int compareBoardByTimeCreatedDes(Board_t* boardA, Board_t* boardB);
int compareBoardByTimeLastEditedAsc(Board_t* boardA, Board_t* boardB);
int compareBoardByTimeLastEditedDes(Board_t* boardA, Board_t* boardB);


void saveBoardArr(Board_t* savedBoardsArr[]) { // when/how to name board?
	FILE* file = fopen("BoardSaves.txt", "w");

	if (file != NULL) {

		// for each board in the savedBoardsArr
		for (int i = 0; i < boardArrayLen(savedBoardsArr); i++) {

			// first save each unsigned int as space-separated hex words
			for (int ii = 0; ii < BOARD_INT_ARRAY_SIZE; ii++) {
				fprintf(file, "%08x ", savedBoardsArr[i]->boardArr[ii]);
			}

			// then save board name
			fprintf(file, "| %s |", savedBoardsArr[i]->name);
			
			// format and save time created
			char buffer[128];
			strftime(buffer, 26, "%Y:%m:%d %H:%M:%S", &(savedBoardsArr[i]->timeCreated));
			fprintf(file, " %s |", buffer);

			// format and save time last edited
			strftime(buffer, 26, "%Y:%m:%d %H:%M:%S", &(savedBoardsArr[i]->timeLastEdited));
			fprintf(file, " %s\n", buffer);

			// repeat for each board
		}

		fclose(file);


	} else {
		printf("File could not be saved.");

	}
}

Board_t* loadSavedBoardArr() {
	// find how many saves there are in the file by counting '\n'
	int numberOfSaves = 0;

	FILE* file = fopen("BoardSaves.txt", "r");
	if (file != NULL) {
		char test;

		while (!feof(file)) { // while EOF not reached
			test = fgetc(file); // read single char

			if (test == '\n') {
				++numberOfSaves;
			}
		}

		fclose(file);
	}


	// allocate space for array of saves
	Board_t** output = malloc(sizeof(Board_t*) * (numberOfSaves + 1));
	if (output == NULL) {
		return NULL;
	}

	file = fopen("BoardSaves.txt", "r");
	
	// add NULL-terminator
	output[numberOfSaves] = NULL;

	if (file != NULL) {

		for (int i = 0; i < numberOfSaves; i++) {
			Board_t* thisBoard = malloc(sizeof(Board_t));
			output[i] = thisBoard;

			for (int ii = 0; ii < 96; ii++) {
				fscanf(file, "%x ", &(thisBoard->boardArr[ii]));

			}

			char readBuffer[256];

			fscanf(file, "%[^\n]", readBuffer);

			int idxS = indexCharInStr(readBuffer, '|');
			int idxE = indexCharInStr(&readBuffer[idxS + 1], '|');

			strncpy(thisBoard->name, readBuffer + idxS + 2, idxE - idxS - 2);
			thisBoard->name[idxE - 2] = 0;

			// TODO debug time parsing
			thisBoard->timeCreated = scanForDateTime(readBuffer + idxE + 3, "%Y:%m:%d %H:%M:%S");
			
			idxS = indexCharInStr(&readBuffer[idxE + 1], '|');

			// TODO debug time parsing
			thisBoard->timeLastEdited = scanForDateTime(readBuffer + idxS, "%Y:%m:%d %H:%M:%S");

		}

	}

	return output;

}



int searchSaves(Board_t* searchThis) {

	int count = 0;
	char searchString[64];

	printf("Type the file name you want to search for:\n");
	scanf("%s", &searchString);

	while (searchThis + count != NULL) {

		if (strcmp((searchThis + count)->name, searchString) == 0) {

			printf("\"%s\" is loaded.\n", &searchString);

			return count;

		}

		++count;

	}

	return NULL;

}



Board_t* sortBoards(Board_t* sortThis[], int sortBy) {
	int count = boardArrayLen(sortThis);

	switch (sortBy) {
	case 0:
		qsort(sortThis, count, sizeof(Board_t*), compareBoardByNameAsc);
		break;

	case 1:
		qsort(sortThis, count, sizeof(Board_t*), compareBoardByTimeCreatedAsc);
		break;

	case 2:
		qsort(sortThis, count, sizeof(Board_t*), compareBoardByTimeCreatedDes);
		break;

	case 3:
		qsort(sortThis, count, sizeof(Board_t*), compareBoardByTimeLastEditedAsc);
		break;

	case 4:
		qsort(sortThis, count, sizeof(Board_t*), compareBoardByTimeLastEditedDes);
		break;

	default:
		qsort(sortThis, count, sizeof(Board_t*), compareBoardByNameAsc);
		break;

	}

	return sortThis;
}


int compareBoardByNameAsc(Board_t* boardA, Board_t* boardB) {
	return strcmp(boardA->name, boardB->name);
}

int compareBoardByTimeCreatedAsc(Board_t* boardA, Board_t* boardB) {
	struct tm dateA = boardA->timeCreated;
	struct tm dateB = boardB->timeCreated;

	double d = -difftime(mktime(&dateA), mktime(&dateB));

	return d;
}

int compareBoardByTimeCreatedDes(Board_t* boardA, Board_t* boardB) {
	struct tm dateA = boardA->timeCreated;
	struct tm dateB = boardB->timeCreated;

	double d = difftime(mktime(&dateA), mktime(&dateB));

	return d;
}

int compareBoardByTimeLastEditedAsc(Board_t* boardA, Board_t* boardB) {
	struct tm dateA = boardA->timeLastEdited;
	struct tm dateB = boardB->timeLastEdited;

	double d = -difftime(mktime(&dateA), mktime(&dateB));

	return d;
}

int compareBoardByTimeLastEditedDes(Board_t* boardA, Board_t* boardB) {
	struct tm dateA = boardA->timeLastEdited;
	struct tm dateB = boardB->timeLastEdited;

	double d = difftime(mktime(&dateA), mktime(&dateB));

	return d;
}


// legacy method of comparing board names in ascending alphabetical order
int compareBoards(Board_t* boardA, Board_t* boardB) {

	return strcmp(boardA->name, boardB->name);

}

