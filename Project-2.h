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

#endif

