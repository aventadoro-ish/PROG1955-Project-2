#include <stdio.h>
#include <stdlib.h>
#include "Project-2.h"
#include "rendering.h"
#include "simulation.h"
#include "saves.h"
#include "editor.h"




Coord *cellIdxToCoord(unsigned int cellIdx, Coord* boardDimesions) {
	Coord *res = (Coord*) malloc(sizeof(Coord));
	res->x = cellIdx % boardDimesions->x;
	res->y = cellIdx / boardDimesions->y;
	
	return res;
}


void fill(unsigned long long int board[], Coord *boardDimensions) {
	unsigned long long int value = 1;
	unsigned long long int cellNum = 0;
	
	for (unsigned long long int y = 0; y < boardDimensions->y; y++) {
		//cellNum += (unsigned long long int)(boardDimensions->x) - 1;

		unsigned int maskOffset = cellNum % (8 * sizeof(board[0]));
		unsigned int boardIdx = cellNum / (8 * sizeof(board[0]));



		Coord* crd = cellIdxToCoord(cellNum, boardDimensions);

		board[boardIdx] = 0;//value;
		value = value << 1;
		
		printf("*c=%04llu, idx=%02u, board[idx]=%llu\n", cellNum, boardIdx, board[boardIdx]);
		
		cellNum += boardDimensions->x;


	}
}

int main() {
	Coord dim = { .x = 50, .y = 4 };
	unsigned long long int cellsTotal = dim.x * dim.y;

	unsigned int arrSize = (cellsTotal + (64 - 1)) / 64;//(sizeof(unsigned long long int) * 8);

	//unsigned long long board[32] = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 256 };
	unsigned long long int* board = malloc(sizeof(unsigned long long int) * arrSize);
	//unsigned long long board[arrSize];
	unsigned int width = 64;
	Coord boardDimensions = { .x = width, .y = sizeof(board) * sizeof(board[0]) / width};

	fill(board, &dim);
	Coord boardPosition = {.x = 16, .y = 16};
	printf("*dim=(%2d,%2d), arrsize=%u\n", dim.x, dim.y, arrSize);
	drawBoard(board, arrSize, &dim, &boardPosition);

	//for (;;) {
	//	// main loop goes here
	//}

	return 0;
}

void sim_step(unsigned short int *board, unsigned int rows) {
	for (unsigned int i = 0; i < rows; i++) {
		printf("*\n");
	}
}