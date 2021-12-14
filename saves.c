#include "saves.h"


void saveBoard(Board_t* saveBoards) {

	FILE* file = fopen("BoardSaves.txt", "w");
	if (file != NULL) {

		int count = 0;

		while ((saveBoards + count) != NULL) {

			for (int i = 0; i < 96; i++) {

				fprintf(file, "%u ", (saveBoards + count)->boardArr + i);

			}

			fprintf(file, ".%s\n", (saveBoards + count)->name);

			++count;

		}

	} 

	fclose(file);

}

int searchSaves(Board_t* searchThis) {

	int count = 0;
	char searchString[64];

	printf("Type the file name you want to search for:\n");
	scanf("%s", &searchString);

	while (searchThis + count != NULL){

		if (strcmp((searchThis + count)->name, searchString) == 0) {

			printf("\"%s\" is loaded.\n", &searchString);

			return count;

		}

		++count;

	}

	return NULL;

}

Board_t* sortBoards(Board_t* sortThis) {

	int count = 0;

	while (sortThis + count != NULL){

		++count;

	}

	qsort(sortThis, count, sizeof(Board_t*), compareBoards);

	return sortThis;

}

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
