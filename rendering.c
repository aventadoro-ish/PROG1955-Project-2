#include "rendering.h"

void drawBoard(const Board_t* b) {
    unsigned long long int cellNum = 0;
    Tuple2_t cPos = { .x = BOARD_SCREEN_OFFSET_X, .y = BOARD_SCREEN_OFFSET_Y };

    // save coursor position and move it to offset
    printf("\x1B[s");
    moveCursour(&cPos);

    // for each row
    for (unsigned int y = 0; y < BOARD_ROWS; y++) {
        cPos.y = BOARD_SCREEN_OFFSET_Y + y;
        moveCursour(&cPos);
        
        // for each cell in current row
        for (unsigned int x = BOARD_COLS; x > 0 ; x--) {
            unsigned int maskOffset = cellNum % (8 * sizeof(unsigned int));
            unsigned int boardIdx = cellNum / (8 * sizeof(unsigned int));
            
            unsigned int mask = 1 << maskOffset;
            char bit = (b->boardArr[boardIdx] & mask) > 0 ? CELL_ALIVE_CHAR : CELL_DEAD_CHAR;
            printf("%c", bit);

            ++cellNum;
        }
    }

    printf("\x1B[u");
    
}

void moveCursour(const Tuple2_t* coord) {
    printf("\x1B[%d;%dH", coord->y + 1, coord->x + 1);

}

void drawFrame(const Tuple2_t* pos, const Tuple2_t* dim, int doReturnCursour) {
    if (doReturnCursour) printf("\x1B[s"); // save cursour position if needed
    Tuple2_t t;
    moveCursour(pos);

    // draw upper bar
    printf("+");
    for (int i = pos->x + 1; i < pos->x + dim->x - 1; i++) {
        printf("-");
    }
    printf("+");

    // draw sides
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

    if (doReturnCursour) printf("\x1B[u"); // return cursour if needed
}

void printText(Tuple2_t* pos, char* str, int doReturnCursour) {
    if (doReturnCursour) printf("\x1B[s"); // save cursour position if needed
    Tuple2_t posLocal = *pos;

    int line = 0;
    int n = 0;
    moveCursour(&posLocal);

    while (str[n] != 0) {
        if (str[n] == '\n') {
            posLocal.y++;
            moveCursour(&posLocal);

        } else {
            printf("%c", str[n]);
        }
        ++n;

    }
    
    //printf("%s", str);


    if (doReturnCursour) printf("\x1B[u"); // return cursour if needed

}
