#include "global.hpp"

const int numberOfPieces = 7;
const int sleepTime = 0;
const char * symbol[] = {"x","o"};
bool board[2][14];
int piecePool[] = {numberOfPieces, numberOfPieces};//use piecePool[side] 
int wonPieces[] = {0,0};//use wonPieces[side]
bool display = true;
