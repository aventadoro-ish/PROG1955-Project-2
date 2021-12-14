#include "saves.h"

int compareBoardByNameAsc(Board_t* boardA, Board_t* boardB);
int compareBoardByTimeCreatedAsc(Board_t* boardA, Board_t* boardB);
int compareBoardByTimeCreatedDes(Board_t* boardA, Board_t* boardB);
int compareBoardByTimeLastEditedAsc(Board_t* boardA, Board_t* boardB);
int compareBoardByTimeLastEditedDes(Board_t* boardA, Board_t* boardB);

// saves an array of board_t* pointers
void saveBoard(Board_t* saveBoards[]) { // when/how to name board?

	FILE* file = fopen("BoardSaves.txt", "w");
	if (file != NULL) {


		for (int i = 0; i < boardArrayLen(saveBoards); i++) {
			for (int ii = 0; ii < 96; ii++) {
				fprintf(file, "%08x ", saveBoards[i]->boardArr[ii]);
			}
			fprintf(file, "| %s |", saveBoards[i]->name);

			char buffer[128];
			strftime(buffer, 26, "%Y:%m:%d %H:%M:%S", &(saveBoards[i]->timeCreated));
			fprintf(file, " %s |", buffer);

			strftime(buffer, 26, "%Y:%m:%d %H:%M:%S", &(saveBoards[i]->timeLastEdited));
			fprintf(file, " %s\n", buffer);

		}

		
	} else {

		printf("File could not be saved.");

	}

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

Board_t* loadSaves() {

	int numberOfSaves = 0;

	FILE* file = fopen("BoardSaves.txt", "r");
	if (file != NULL) {

		char test = ' ';

		while (!feof(file)) {
			test = fgetc(file);

			if (test == '\n') {
				++numberOfSaves;
			}

		}

		fclose(file);

	}


	Board_t** output = malloc(sizeof(Board_t*) * (numberOfSaves + 1));
	if (output == NULL) {
		return NULL;
	}

	file = fopen("BoardSaves.txt", "r");
	// TODO add NULL check
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
			int idxE = indexCharInStr(&readBuffer[idxS+1], '|');

			strncpy(thisBoard->name, readBuffer + idxS + 2, idxE - idxS - 2);
			thisBoard->name[idxE - 2] = 0;

			// TODO time parsing
			time_t rawtime;

			time(&rawtime);
			thisBoard->timeCreated = *localtime(&rawtime);

			time(&rawtime);
			thisBoard->timeLastEdited = *localtime(&rawtime);

			//printf("%*s", offset, readBuffer);

			//(output + i)->boardArr = (unsigned)buffer;

		}

	}

	return output;

}
