#ifndef RENDERING_H_
#define RENDERING_H_

#include "utils.h"

/* Draws a game-board board[] of size boardDimensions to console with a preset offset */
void drawBoard(const Board_t* b);

void movecursor(const Tuple2_t* coord);

void drawFrame(const Tuple2_t* pos, const Tuple2_t* dim, int doReturncursor);
void printText(Tuple2_t* pos, char* str, int doReturncursor);

void drawScreenSections();
void printTitle();
void printMainMenu();
void printNewGameMenu();

/* cursorActionCode:
 *  0 - do nothing
 *  1 - put at the begining of menu
 *  2 - put one below the begining
 *  3 - put at the end
 *  4 - put one below the end
 *
 */
void drawToMenuSection(char* str, int doPutCursorToMenu);


#endif