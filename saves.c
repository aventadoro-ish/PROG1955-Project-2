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

	} else {

		printf("File could not be saved.");

	}

	fclose(file);

	printf("File saved successfully.");

}

Board_t* openSave(int selection, Board_t* list) { // not the final version, just for reference

	FILE* file = fopen("BoardSaves.txt", "r");	
	if (file != NULL) {
		
		fread(workingBoard, sizeof(Board_t), 1, file);

		fclose(file);

	}

	return workingBoard;

}

Board_t* loadSaves() {

	Board_t* output = malloc(sizeof(Board_t) * (numberOfSaves + 1));



}

Board_t* searchSaves(Board_t* searchThis) {

	int count = 0;

	while (searchThis + count != NULL)
	{

		++count;

	}

}

Board_t* sortBoards(Board_t* sortThis) {

	int count = 0;

	while (sortThis + count != NULL)
	{

		++count;

	}

}