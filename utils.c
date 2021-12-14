#include "utils.h"


Board_t* createBoard() {
	Board_t* board = (Board_t*)malloc(sizeof(Board_t));
	if (board == NULL) {
		printf("ERROR: editor.c -> createBoard() -> malloc() returned NULL\n");
		return NULL;
	}

	strcpy(board->name, "                                                              ");
	time_t rawtime;
	time(&rawtime);
	board->timeCreated = *localtime(&rawtime);


	return board;
}

Board_t* copyBoard(Board_t* boardToCopy) {
	Board_t* board = createBoard();
	if (board == NULL) {
		return NULL;
	}

	strcpy(board->name, boardToCopy->name);
	board->timeCreated = boardToCopy->timeCreated;
	board->timeLastEdited = boardToCopy->timeLastEdited;

	for (int i = 0; i < 96; i++) {
		board->boardArr[i] = boardToCopy->boardArr[i];
	}

	return board;
}


Tuple2_t intsToTuple(int x, int y) {
	Tuple2_t tuple = { x, y };
	return tuple;
}

int charOccurrences(char* str, char c) {
	int i = 0;
	int count = 0;

	while (str[i] != NULL) {
		if (str[i] == c) ++count;

		++i;
	}

	return count;
}

int boardArrayLen(Board_t* arr[]) {
	int count = 0;

	while (arr[count] != NULL) {
		++count;
	}

	return count;
}

Board_t* addNewBoard(Board_t* oldBoards[]) {

	int oldLength = boardArrayLen(oldBoards);

	Board_t* updatedBoardArr[] = malloc(sizeof(Board_t) * (oldLength + 2));

	for (int i = 0; i <= oldLength; i++) {

		updatedBoardArr[i] = oldBoards[i];

	}

	updatedBoardArr[oldLength + 1] = NULL;

	free(oldBoards);

	return updatedBoardArr;

}