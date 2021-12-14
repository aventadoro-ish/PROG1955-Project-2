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

Board_t* createBoardCopy(Board_t* boardToCopy) {
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

	time_t rawtime;
	time(&rawtime);
	board->timeCreated = *localtime(&rawtime);

	return board;
}

int copyBoard(const Board_t* origin, Board_t* destination) {
	// TODO error code
	strcpy(destination->name, origin->name);
	
	for (int i = 0; i < 96; i++) {
		destination->boardArr[i] = origin->boardArr[i];
	}

	destination->timeCreated = origin->timeCreated;
	destination->timeLastEdited = origin->timeLastEdited;

	return 0;
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


int indexCharInStr(char* str, char c) {
	int i = 0;

	while (str[i] != NULL) {
		char ch = str[i];
		if (ch == c) return i;
		++i;
	}

	return -1;
}

Board_t** addNewBoard(Board_t* oldBoards[], Board_t* boardToAdd) {
	int oldLength = boardArrayLen(oldBoards);

	Board_t** updatedBoardArr = malloc(sizeof(Board_t*) * (oldLength + 2));
	if (updatedBoardArr == NULL) {
		printf("malloc() error in utils.h->addNewBoard()");
		return oldBoards;
	}

	for (int i = 0; i < oldLength; i++) {
		updatedBoardArr[i] = oldBoards[i];
	}

	updatedBoardArr[oldLength] = boardToAdd;
	updatedBoardArr[oldLength + 1] = NULL;

	free(oldBoards);

	return updatedBoardArr;

}

Board_t** deleteBoard(int idx, Board_t* oldBoards[]) {
	int oldLength = boardArrayLen(oldBoards);

	Board_t** updatedBoardArr = malloc(sizeof(Board_t*) * (oldLength));
	if (updatedBoardArr == NULL) {
		printf("malloc() error in utils.h->addNewBoard()");
		return oldBoards;
	}

	int i = 0;
	int newIdx = 0;
	while (i < oldLength) {
		if (i != idx) {
			updatedBoardArr[newIdx] = oldBoards[i];
			newIdx++;
		}

		i++;
	}

	updatedBoardArr[oldLength - 1] = NULL;

	free(oldBoards);

	return updatedBoardArr;
}


struct tm scanForDateTime(char* buffer, char* format) {
	// TODO refactoring
	time_t result = 0;
	int year = 0, month = 0, day = 0, hour = 0, min = 0;

	if (sscanf(buffer, format, &year, &month, &day, &hour, &min) == 5) {
		struct tm breakdown = { 0 };
		breakdown.tm_year = year - 1900; /* years since 1900 */
		breakdown.tm_mon = month - 1;
		breakdown.tm_mday = day;
		breakdown.tm_hour = hour;
		breakdown.tm_min = min;

		return breakdown;
	}

	time_t rawtime;
	time(&rawtime);
	return *localtime(&rawtime);
}