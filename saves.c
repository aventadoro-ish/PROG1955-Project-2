#include "saves.h"


void saveBoard(Board_t* saveBoards) { // when/how to name board?

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

	} else {

		printf("File could not be saved.");

	}

	fclose(file);

	printf("File saved successfully.");

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

	if (searchThis + count == NULL) {

		printf("There is no file by that name");

	}

}

Board_t* sortBoards(Board_t* sortThis) {

	int count = 0;

	while (sortThis + count != NULL){

		++count;

	}

	qsort(sortThis, count, sizeof(Board_t), compareBoards);

	return sortThis;

}

int compareBoards(Board_t* boardA, Board_t* boardB) {

	return strcmp(boardA->name, boardB->name);

}

/*Board_t* openSave(int selection, Board_t* list) { // not the final version, just for reference

	FILE* file = fopen("BoardSaves.txt", "r");
	if (file != NULL) {

		fread(workingBoard, sizeof(Board_t), 1, file);

		fclose(file);

	}

	return workingBoard;

}

Board_t* loadSaves() {

	Board_t* output = malloc(sizeof(Board_t) * (numberOfSaves + 1));



}*/
