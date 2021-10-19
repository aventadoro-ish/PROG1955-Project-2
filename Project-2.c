#include <stdio.h>
#include "rendering.h"
#include "simulation.h"
#include "saves.h"
#include "editor.h"


int main() {
	unsigned short int initial_board[] = {0b00000000, 
										0b00000000,
										0b00000000,
										0b00000000,
										0b00000000,
										0b00000000,
										0b00000000,
										0b00000000};

	printf("%d", sum(4, 8));


	for (;;) {
		// main loop goes here
	}

	return 0;
}

void sim_step(unsigned short int *board, unsigned int rows) {
	for (int i = 0; i < rows; i++) {
		printf("%");
	}
}