#include "rendering.h"

/* Draws a game-board board[] of size boardDimensions to console with a preset offset */
void drawBoard(const Board_t* b) {
    char line[128];

    unsigned long long int cellNum = 0;
    Tuple2_t cPos = { .x = OFFSET_X, .y = OFFSET_Y };

    // save coursor position and move it to offset
    printf("\x1B[s");
    moveCursour(&cPos);
    //printf("\x1B[%d;%dH", OFFSET_Y, OFFSET_X);
    //printf("\x1B[%dG\n", offset->x);


    for (unsigned int y = 0; y < BOARD_ROWS; y++) {
        //printf("\x1B[%d;%dH", OFFSET_Y + y, OFFSET_X);
        cPos.y = OFFSET_Y + y;
        moveCursour(&cPos);
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

void moveCursour(const Tuple2_t* coord) {
    printf("\x1B[%d;%dH", coord->y + 1, coord->x + 1);

}

void drawFrame(Tuple2_t* pos, Tuple2_t* dim, int doReturnCursour) {
    printf("(%d, %d) (%d, %d)", pos->x, pos->y, dim->x, dim->y);
    Tuple2_t t = { 1, 3 };
    moveCursour(pos);

    // draw upper bar
    printf("+");
    for (int i = pos->x + 1; i < pos->x + dim->x - 1; i++) {
        printf("-");
    }
    printf("+");


    for (int i = pos->y + 1; i < pos->y + dim->y - 1; i++) {
        Tuple2_t cPos = { .x = pos->x, .y =  i };
        moveCursour(&cPos);
        printf("|");

        cPos.x = pos->x + dim->x-1;
        moveCursour(&cPos);
        printf("|");
    }


    // draw lower bar
    t.x = pos->x;
    t.y = pos->y + dim->y - 1;
    moveCursour(&t);
    printf("+");
    for (int i = pos->x + 1; i < pos->x + dim->x - 1; i++) {
        printf("-");
    }
    printf("+");


}

void printText(Tuple2_t pos, char* str, int doReturnCurour) {
    // TODO
}
