#ifndef MAIN_H_
#define MAIN_H_

#include "utils.h"

#include "rendering.h"
#include "simulation.h"
#include "saves.h"
#include "editor.h"


void mainMenu(Board_t** savedBoardArr);

void newGameStart(Board_t** savedBoardArr);

void loadSavesMenu(Board_t** savedBoardArr);


Board_t* simulation(Board_t* boardA, double timestep);

int saveProcedure(Board_t* board, Board_t** savedBoardArr);

Board_t* selectBoard(Board_t* board, Board_t** savedBoardArr, int doPromptEdit, int doPromptRun, int doPromptSave);


int promptMenuInt(char* promptText, int min, int max);
char promptMenuChar(char* promptText, char* allowedChars);
double promptMenuDouble(char* promptText, double min, double max);
char* promptMenuStr(char* promptText, int maxLen);



#endif

