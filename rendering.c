#include "rendering.h"

void drawBoard(const Board_t* b) {
    unsigned long long int cellNum = 0;
    Tuple2_t cPos = { .x = BOARD_SCREEN_OFFSET_X, .y = BOARD_SCREEN_OFFSET_Y };

    // save coursor position and move it to offset
    printf("\x1B[s");
    movecursor(&cPos);

    // for each row
    for (unsigned int y = 0; y < BOARD_ROWS; y++) {
        cPos.y = BOARD_SCREEN_OFFSET_Y + y;
        movecursor(&cPos);
        
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

void movecursor(const Tuple2_t* coord) {
    printf("\x1B[%d;%dH", coord->y + 1, coord->x + 1);

}

void drawFrame(const Tuple2_t* pos, const Tuple2_t* dim, int doReturncursor) {
    if (doReturncursor) printf("\x1B[s"); // save cursor position if needed
    Tuple2_t t;
    movecursor(pos);

    // draw upper bar
    printf("+");
    for (int i = pos->x + 1; i < pos->x + dim->x - 1; i++) {
        printf("-");
    }
    printf("+");

    // draw sides
    for (int i = pos->y + 1; i < pos->y + dim->y - 1; i++) {
        Tuple2_t cPos = { .x = pos->x, .y =  i };
        movecursor(&cPos);
        printf("|");

        cPos.x = pos->x + dim->x-1;
        movecursor(&cPos);
        printf("|");
    }


    // draw lower bar
    t.x = pos->x;
    t.y = pos->y + dim->y - 1;
    movecursor(&t);
    printf("+");
    for (int i = pos->x + 1; i < pos->x + dim->x - 1; i++) {
        printf("-");
    }
    printf("+");

    if (doReturncursor) printf("\x1B[u"); // return cursor if needed
}

void printText(Tuple2_t* pos, char* str, int doReturncursor) {
    if (doReturncursor) printf("\x1B[s"); // save cursor position if needed
    Tuple2_t posLocal = *pos;

    int line = 0;
    int n = 0;
    movecursor(&posLocal);

    while (str[n] != 0) {
        if (str[n] == '\n') {
            posLocal.y++;
            movecursor(&posLocal);

        } else {
            printf("%c", str[n]);
        }
        ++n;

    }
    
    //printf("%s", str);


    if (doReturncursor) printf("\x1B[u"); // return cursor if needed

}



void drawScreenSections() {
    Tuple2_t pos;
    Tuple2_t dim;

    // draw title frame
    pos.x = 1;
    pos.y = 0;

    dim.x = BOARD_COLS + INFO_X;
    dim.y = BOARD_SCREEN_OFFSET_Y;

    drawFrame(&pos, &dim, 1);

    // draw main game board
    pos.x = BOARD_SCREEN_OFFSET_X - 1;
    pos.y = BOARD_SCREEN_OFFSET_Y - 1;

    dim.x = BOARD_COLS + 2;
    dim.y = BOARD_ROWS + 2;

    drawFrame(&pos, &dim, 1);


    // draw info board
    pos.x = BOARD_SCREEN_OFFSET_X + BOARD_COLS;
    pos.y = BOARD_SCREEN_OFFSET_Y - 1;

    dim.x = INFO_X - 1;
    dim.y = BOARD_ROWS + 2;

    drawFrame(&pos, &dim, 1);
}

void printTitle() {
    char title[] = { 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x20 , 0x2e , 0x20 , 0x2e , 0x20 , 0x2e , 0x20 , 0x2e , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x20 , 0x2e , 0x20 , 0x60 , 0x27 , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x20 , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x20 , 0x20 , 0x2e , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x20 , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x20 , 0x20 , 0x2e , 0x20 , 0x20 , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x2e , 0x2d , 0x2e , 0x20 , 0x0a , 0x7c , 0x20 , 0x20 , 0x20 , 0x7c , 0x20 , 0x7c , 0x20 , 0x7c , 0x5c , 0x7c , 0x20 , 0x7c , 0x20 , 0x7c , 0x20 , 0x7c , 0x20 , 0x7c , 0x2d , 0x7c , 0x20 , 0x20 , 0x7c , 0x20 , 0x20 , 0x60 , 0x27 , 0x20 , 0x60 , 0x2d , 0x2e , 0x20 , 0x20 , 0x20 , 0x7c , 0x2e , 0x2e , 0x20 , 0x7c , 0x2d , 0x7c , 0x20 , 0x7c , 0x5c , 0x2f , 0x7c , 0x20 , 0x7c , 0x2d , 0x20 , 0x20 , 0x20 , 0x20 , 0x7c , 0x20 , 0x7c , 0x20 , 0x7c , 0x2d , 0x20 , 0x20 , 0x20 , 0x20 , 0x7c , 0x20 , 0x20 , 0x20 , 0x20 , 0x7c , 0x20 , 0x20 , 0x7c , 0x2d , 0x20 , 0x20 , 0x7c , 0x2d , 0x20 , 0x20 , 0x0a , 0x60 , 0x2d , 0x27 , 0x20 , 0x60 , 0x2d , 0x27 , 0x20 , 0x27 , 0x20 , 0x60 , 0x20 , 0x60 , 0x2e , 0x27 , 0x2e , 0x27 , 0x20 , 0x60 , 0x20 , 0x27 , 0x20 , 0x20 , 0x60 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x60 , 0x2d , 0x27 , 0x20 , 0x20 , 0x20 , 0x60 , 0x2d , 0x27 , 0x20 , 0x60 , 0x20 , 0x27 , 0x20 , 0x27 , 0x20 , 0x20 , 0x60 , 0x20 , 0x60 , 0x2d , 0x27 , 0x20 , 0x20 , 0x20 , 0x60 , 0x2d , 0x27 , 0x20 , 0x27 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x60 , 0x2d , 0x27 , 0x20 , 0x60 , 0x2d , 0x27 , 0x20 , 0x27 , 0x20 , 0x20 , 0x20 , 0x60 , 0x2d , 0x27, 0x00 };

    Tuple2_t pos;

    pos.x = 30;
    pos.y = 1;

    printText(&pos, title, 1);
    //movecursor(&pos);
    //printf("\x0a \x2e \x2d \x2e \x20 \x2e \x2d \x2e \x20 \x2e \x20 \x2e \x20 \x2e \x20 \x2e \x20 \x2e \x20 \x2e \x2d \x2e \x20 \x2e \x20 \x2e \x20 \x60 \x27 \x20 \x2e \x2d \x2e \x20 \x20 \x20 \x2e \x2d \x2e \x20 \x2e \x2d \x2e \x20 \x2e \x20 \x20 \x2e \x20 \x2e \x2d \x2e \x20 \x20 \x20 \x2e \x2d \x2e \x20 \x2e \x2d \x2e \x20 \x20 \x20 \x2e \x20 \x20 \x20 \x2e \x2d \x2e \x20 \x2e \x2d \x2e \x20 \x2e \x2d \x2e \x20 \x0a \x7c \x20 \x20 \x20 \x7c \x20 \x7c \x20 \x7c \x5c \x7c \x20 \x7c \x20 \x7c \x20 \x7c \x20 \x7c \x2d \x7c \x20 \x20 \x7c \x20 \x20 \x60 \x27 \x20 \x60 \x2d \x2e \x20 \x20 \x20 \x7c \x2e \x2e \x20 \x7c \x2d \x7c \x20 \x7c \x5c \x2f \x7c \x20 \x7c \x2d \x20 \x20 \x20 \x20 \x7c \x20 \x7c \x20 \x7c \x2d \x20 \x20 \x20 \x20 \x7c \x20 \x20 \x20 \x20 \x7c \x20 \x20 \x7c \x2d \x20 \x20 \x7c \x2d \x20 \x20 \x0a \x60 \x2d \x27 \x20 \x60 \x2d \x27 \x20 \x27 \x20 \x60 \x20 \x60 \x2e \x27 \x2e \x27 \x20 \x60 \x20 \x27 \x20 \x20 \x60 \x20 \x20 \x20 \x20 \x20 \x60 \x2d \x27 \x20 \x20 \x20 \x60 \x2d \x27 \x20 \x60 \x20 \x27 \x20 \x27 \x20 \x20 \x60 \x20 \x60 \x2d \x27 \x20 \x20 \x20 \x60 \x2d \x27 \x20 \x27 \x20 \x20 \x20 \x20 \x20 \x60 \x2d \x27 \x20 \x60 \x2d \x27 \x20 \x27 \x20 \x20 \x20 \x60 \x2d \x27 \x20 \x0a \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x20 \x0a");
    //printf("%s", title);
}

void printMainMenu() {
    Tuple2_t coord = { BOARD_SCREEN_OFFSET_X + BOARD_COLS + 2, BOARD_SCREEN_OFFSET_Y };
    // TODO redo using '\n' instead of separate printText() calls
    printText(&coord, "Main menu:                              \n"
        "-New Game                               \n"
        "-Load                                   \n"
        "-Exit                                   \n"
        "                                        \n"
        "                                        \n"
        "                                        \n"
        "                                        \n", 1);



}

void printNewGameMenu() {
    Tuple2_t coord = { BOARD_SCREEN_OFFSET_X + BOARD_COLS + 2, BOARD_SCREEN_OFFSET_Y };
    // TODO add clearText() function
    printText(&coord, "New Game                                \n"
        "*use arrow keys or ASWD to move cursor\n"
        "*use ENTER to toggle cell value       \n"
        "*press ESCAPE once to start simulation\n"
        "*press ESCAPE second time to exit     \n", 1);


}


void drawToMenuSection(char* str, int cursorActionCode) {
    Tuple2_t coord = { BOARD_SCREEN_OFFSET_X + BOARD_COLS + 2, BOARD_SCREEN_OFFSET_Y };
    
    for (int i = 0; i < INFO_Y; i++) {
        movecursor(&coord);
        printf("%*c\n", INFO_X - 4, ' ');

        coord.y++;
    }

    coord.x = BOARD_SCREEN_OFFSET_X + BOARD_COLS + 2;
    coord.y = BOARD_SCREEN_OFFSET_Y;

    printText(&coord, str, 1);

    switch (cursorActionCode) {
    case 0:
        break;

    case 1:
        movecursor(&coord);
        break;

    case 2:
        coord.y++;
        movecursor(&coord);
        break;

    case 3:
        coord.y += charOccurrences(str, '\n');
        movecursor(&coord);
        break;
        
    case 4:
        coord.y += charOccurrences(str, '\n') + 1;
        movecursor(&coord);
        break;

    default:
        break;
    }


}
