/* In general it's good to include also the header of the current .c,
   to avoid repeating the prototypes */
#include "rendering.h"
#include <stdio.h>




void drawBoard(unsigned long long int board[], unsigned int size,
                Coord *boardDimensions, Coord *offset) {
    /* Draws a game-board board[] of size boardDimensions to console
     *   with an offset by ofset
     */

    //char* line[] = malloc(boardDimensions->x);
    char line[128];
    //printf("board Dimensions = (%d, %d)\n", boardDimensions->x, boardDimensions->y);

    unsigned long long int cellNum = 0;
    
    // save coursor position and move it to offset
    printf("\x1B[s");
    printf("\x1B[%d;%dH\n", offset->y, offset->x);
    //printf("\x1B[%dG\n", offset->x);


    for (unsigned long long int y = 0; y < boardDimensions->y; y++) {
        // TODO: redo hacky way of offsetting x
        printf("%*c", offset->x-1, ' '); 

        for (unsigned long long int x = boardDimensions->x; x > 0 ; x--) {
            unsigned int maskOffset = cellNum % (8 * sizeof(board[0]));
            unsigned int boardIdx = cellNum / (8 * sizeof(board[0]));
            //printf("(%02d,%02d) c=%04llu, MO=%02u, idx=%u, board[idx]=%llu\n", 
                //(int)x, (int)y, cellNum, maskOffset, boardIdx, board[boardIdx]);
            
            unsigned long long int mask = (unsigned long long int)1 << maskOffset;
            char bit = (board[boardIdx] & mask) > 0 ? CELL_ALIVE : CELL_DEAD;
            line[x-1] = bit;
            printf("%c", bit);
            ++cellNum;
        }
        printf("\n");
        //printf("%.*s\n", 32, line);
    }

    printf("\x1B[u");

    
}
