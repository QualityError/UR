#pragma once
// prototypes here

/* not in header?

int mapX(int c);
int mapY(int side, int i);


*/

int piecePosition(int piece, int side);
bool legalMove(int choice, int roll, int side);
void turnFor(int side, int ai = 0, bool again = false);
void clearBoard();
int game(int players[]);

