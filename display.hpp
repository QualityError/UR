#pragma once

//ncurses
void initNcurses();
void endNcurses();
//PRINTING
void printPieces();
void printBoard();
void printMultible(const char * sym, int times);
void updateDisplay();
void message(const char * msg, int x = -1);//must %d if setting x
void printOutcome(int winner);
void printRoll(int roll);