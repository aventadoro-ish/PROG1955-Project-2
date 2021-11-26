#include "saves.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void saveBoard(Board_t* saveThis) {

	printf("What is the name of your board?"); // Ask about keeping current name (if existing)?
	scanf("%s", saveThis->name);

	FILE* file = fopen(saveThis->name, "w");
	if (file != NULL) {

		fwrite(saveThis, sizeof(Board_t), 1, file);
		fclose(file);

	}

	printf("Board %s has been saved.", saveThis->name);

}

Board_t* openSave(int selection) { // need to use selection number for determining file selection
	
	Board_t* workingBoard = malloc(sizeof(Board_t));

	FILE* file = fopen(, "r"); // need to access information via selection of sort/search results	
	if (file != NULL) {
		
		fread(workingBoard, sizeof(Board_t), 1, file);

		fclose(file);

	}

	return workingBoard;

}

