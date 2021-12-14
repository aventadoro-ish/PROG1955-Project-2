#include "saves.h"

int compareBoardByNameAsc(Board_t* boardA, Board_t* boardB);
int compareBoardByTimeCreatedAsc(Board_t* boardA, Board_t* boardB);
int compareBoardByTimeCreatedDes(Board_t* boardA, Board_t* boardB);
int compareBoardByTimeLastEditedAsc(Board_t* boardA, Board_t* boardB);
int compareBoardByTimeLastEditedDes(Board_t* boardA, Board_t* boardB);

<<<<<<< HEAD
// saves an array of board_t* pointers
void saveBoard(Board_t* saveBoards[]) { // when/how to name board?
=======
void saveBoard(Board_t* saveBoards) {
>>>>>>> c1fc8359b85721433ad06b0a2b9846624a660384

	FILE* file = fopen("BoardSaves.txt", "w");
	if (file != NULL) {


		for (int i = 0; i < boardArrayLen(saveBoards); i++) {
			for (int ii = 0; ii < 96; ii++) {
				fprintf(file, "%06x ", saveBoards[i]->boardArr[ii]);

			}
		}

<<<<<<< HEAD
		

	} else {

		printf("File could not be saved.");

	}
=======
	} 
>>>>>>> c1fc8359b85721433ad06b0a2b9846624a660384

	fclose(file);

}


// search in an array of board_t* pointers and return
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

<<<<<<< HEAD
	}
=======
	qsort(sortThis, count, sizeof(Board_t*), compareBoards);
>>>>>>> c1fc8359b85721433ad06b0a2b9846624a660384

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

Board_t* loadSaves() {
	
	int numberOfSaves = 0;

	FILE* file = fopen("BoardSaves.txt", "r");
	if (file != NULL) {		

		char test;

		while (test != EOF) {

			fscanf("%c", test);

			if (test == '\n') {

				++numberOfSaves;

			}

		}

	}

	Board_t* output = malloc(sizeof(Board_t) * (numberOfSaves + 1));

	output[numberOfSaves + 1] = NULL;

	if (file != NULL) {
	
		for (int i = 0; i < numberOfSaves; i++) {

			char buffer[11];

			fscanf("%s ", buffer);

			(output + i)->boardArr = (unsigned) buffer;

		}

	}

	return output;

}
