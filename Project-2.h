#ifndef MAIN_H_
#define MAIN_H_

#include "utils.h"

#include "rendering.h"
#include "simulation.h"
#include "saves.h"
#include "editor.h"


void mainMenu();

void newGameStart();
Board_t* simulation(Board_t* boardA, double timestep);

int saveProcedure(Board_t* board);

void loadSavesMenu();

Board_t* selectBoard(Board_t* board, int doPromptEdit, int doPromptRun, int doPromptSave);

int promptMenuInt(char* promptText, int min, int max);
char promptMenuChar(char* promptText, char* allowedChars);
double promptMenuDouble(char* promptText, double min, double max);
char* promptMenuStr(char* promptText, int maxLen);



#endif

