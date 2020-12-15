
#include "global.hpp"
#include <random>
#include <ncurses.h>
#include "ur.hpp"
#include "players.hpp"
#include "display.hpp"



//types of players
int humanChoice(int roll, int side){
	message("Select a piece");
	int choice = getch() - 48;//get human Choice

	while( !legalMove(choice, roll, side)){//until valid choice
		message("Invalid Move:%d", choice);//display invalid choice
		choice = getch() - 48;//get next human Choice
	}

	return choice;
}
int randomAi(int roll, int side){
	int choice;

	do{
		choice = 0 + (rand() % static_cast<int>(7 - 0 + 1));
		//min + (rand() % static_cast<int>(max - min + 1))
	}while( !legalMove(choice, roll, side) );//until valid choice

	return choice;
}
int basicAi(int roll, int side){
	int choice;

	int numOptions = numberOfPieces - piecePool[side] - wonPieces[side];

	int rollAgain = -2;
	int removesOpposition = -2;
	int toSafety = -2;
	int endPos;
	for(int i = 0; i <= numOptions; i++){
		if(legalMove(i, roll, side)){
			endPos = piecePosition(i,side);
			
			if(endPos == 3 || endPos == 7 || endPos == 13){//if it allows an addition roll
				rollAgain = i;
			}
			if(board[!side][endPos] == true){//if it removes an enemy piece
				removesOpposition = i;
			}
			if(endPos > 11){//if off of the main row
				toSafety = i;
			}
			if(endPos = 14){//preffer getting a piece off of the board to just getting it off the main row
				toSafety = i;
			}
		}
	}


	//roll again
	if(rollAgain != -2){
		return rollAgain;
	}
	//removes piece
	if(removesOpposition != -2){
		return removesOpposition;
	}
	//safty
	if(toSafety != -2){
		return toSafety;
	}
	//if nothing else
	//random
	do{
		choice = 0 + (rand() % static_cast<int>(7 - 0 + 1));
		//min + (rand() % static_cast<int>(max - min + 1))
	}while( !legalMove(choice, roll, side) );//until valid choice

	return choice;
}
int basicSafetyAi(int roll, int side){
	int choice;

	int numOptions = numberOfPieces - piecePool[side] - wonPieces[side];

	int rollAgain = -2;
	int removesOpposition = -2;
	int toSafety = -2;
	int endPos;
	for(int i = 0; i <= numOptions; i++){
		if(legalMove(i, roll, side)){
			endPos = piecePosition(i,side);
			
			if(endPos == 3 || endPos == 7 || endPos == 13){//if it allows an addition roll
				rollAgain = i;
			}
			if(board[!side][endPos] == true){//if it removes an enemy piece
				removesOpposition = i;
			}
			if(endPos > 11){//if off of the main row
				toSafety = i;
			}
			if(endPos = 14){//preffer getting a piece off of the board to just getting it off the main row
				toSafety = i;
			}
		}
	}


	//safety
	if(toSafety != -2){
		return toSafety;
	}
	//roll again
	if(rollAgain != -2){
		return rollAgain;
	}
	//removes piece
	if(removesOpposition != -2){
		return removesOpposition;
	}
	//if nothing else
	//random
	do{
		choice = 0 + (rand() % static_cast<int>(7 - 0 + 1));
		//min + (rand() % static_cast<int>(max - min + 1))
	}while( !legalMove(choice, roll, side) );//until valid choice

	return choice;
}
