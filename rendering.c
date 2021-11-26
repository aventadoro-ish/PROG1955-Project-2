/* In general it's good to include also the header of the current .c,
   to avoid repeating the prototypes */
#include "rendering.h"
#include "utils.h"


/* Draws a game-board board[] of size boardDimensions to console with an offset by ofset
 */
void drawBoard(const Board_t* b) {
    char line[128];

    unsigned long long int cellNum = 0;
    
    // save coursor position and move it to offset
    printf("\x1B[s");
    printf("\x1B[%d;%dH", OFFSET_Y, OFFSET_X);
    //printf("\x1B[%dG\n", offset->x);


    for (unsigned int y = 0; y < BOARD_ROWS; y++) {
        printf("\x1B[%d;%dH", OFFSET_Y + y, OFFSET_X);
        for (unsigned int x = BOARD_COLS; x > 0 ; x--) {
            unsigned int maskOffset = cellNum % (8 * sizeof(unsigned int));
            unsigned int boardIdx = cellNum / (8 * sizeof(unsigned int));
            //printf("(%02d,%02d) c=%04llu, MO=%02u, idx=%u, board[idx]=%llu\n", 
                //(int)x, (int)y, cellNum, maskOffset, boardIdx, board[boardIdx]);
            
            unsigned long long int mask = (unsigned long long int)1 << maskOffset;
            char bit = (b->boardArr[boardIdx] & mask) > 0 ? CELL_ALIVE : CELL_DEAD;
            line[x-1] = bit;
            printf("%c", bit);
            ++cellNum;
        }
        printf("\n");
    }

    printf("\x1B[u");
    
}

void drawCursour(const Tuple2_t* coord) {
    // save coursor position and move it to offset
    //printf("\x1B[s");
    printf("\x1B[%d;%dH", coord->y + 1, coord->x + 1);


    
    //printf("\x1B[%dC", coord->y); // this works


    //printf("_");

    //printf("\x1B[u");

}
