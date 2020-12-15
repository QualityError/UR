#include <string>
#include "global.hpp"
#include <random>
#include <unistd.h>//for usleep

#include "display.hpp"
#include "players.hpp"
#include "ur.hpp"

int piecePosition(int piece, int side){
	if(piece == 0){
		return -1;//selected draw bank
	}
	int counter = 0;
	for(int i = 0; i < 14; i++){
		if(board[side][i]){
			counter++;
		}
		if(counter == piece){
			return i;
		}
	}
	return -2;//no piece at that position
}
bool legalMove(int choice, int roll, int side){
	int startPosition = piecePosition(choice, side);

	if(roll == 0 || startPosition == -2){//if no piece for choice or roll of zero
		return false;
	}

	if(startPosition == -1){//if piece is comming from side piece pool
		if(choice != 0){//didnt choose piece pool
			return false;
		}
		if(piecePool[side] < 1){//cannot draw form empty
			return false;
		}
		startPosition = -1;//account for comming from side
	}

	int endPosition = startPosition + roll;

	if(endPosition > 14){//if piece will go to far off edge of board.(a won piece must go exacly one off of the board)
		return false;
	}
	if(endPosition < 14){
		if(board[side][endPosition] == true){//if piece will end on friendly piece
			return false;
		}
		if(endPosition == 7 && board[!side][7] == true){//land on enemy in a protected space
			return false;
		}
	}
	return true;
}

void turnFor(int side, int ai, bool extraTurn){
	
	updateDisplay();

	int roll = rand() % 2 + rand() % 2 + rand() % 2 + rand() % 2;

	if(display){
        	printRoll(roll);
	}

	if(roll == 0){
		message("Turn Over");
		return;
	}

	bool turnPossible = false;
	for(int i = 0; i < numberOfPieces; i++){//worth finding a way to only check to pieces on the board
		if(legalMove(i, roll, side)){
			turnPossible = true;
		}
	}
	if(!turnPossible){
		message("No Possible Moves");
		return;
	}


	//get legal move choice
	int choice;

	switch(ai) {
		case human:
			message("HUMAN'S TURN");
			choice = humanChoice(roll, side);
			break;
		case randomAI:
			message("AI'S TURN");
			choice = randomAi(roll, side);
			break;
		case basicAI:
			message("AI'S TURN");
			choice = basicAi(roll, side);
			break;
		case safetyAI:
			message("AI'S TURN");
			choice = basicSafetyAi(roll, side);
			break;
		default:
			message("ERROR: BAD AI ASSIGNMENT");
	}

	//display valid choice
	message("Chosen Move:%d",choice);
	//Move Piece	
	int position = piecePosition(choice, side);
	int endPosition = position + roll;
	//remove old and place new
	if(position == -1){
		piecePool[side] -= 1;
		board[side][endPosition] = true;
	}else{
		board[side][position] = false;
		if(endPosition != 14){
			board[side][endPosition] = true;
		}else{
			wonPieces[side] += 1;
		}
	}
	
	//if landed on, move opposition piece to their pool 
	if(board[!side][endPosition] && 3 < endPosition && endPosition < 12 && endPosition != 7){
		//if in middle lane and not reroll
		board[!side][endPosition] = false;
		piecePool[!side] += 1;
	}

	//check for additional turn
	if(endPosition == 3 || endPosition == 7 || endPosition == 13){
		turnFor(side, ai);
	}

}

void clearBoard(){
	//reset game data
	for(int i = 0; i < 14; i++){
		board[0][i] = false;
		board[1][i] = false;
	}
	for(int side = 0; side <= 1; side++){
		piecePool[side] = numberOfPieces;
		wonPieces[side] = 0;
	}
}

int game(int players[]){
	
	clearBoard();
	//game loop
	while(wonPieces[0] < numberOfPieces && wonPieces[1] < numberOfPieces){
		for(int side = 0; side <= 1; side++){
		turnFor(side,players[side]);
		//animateMove(side,start,finnish);
		}
	}
	return wonPieces[1] == numberOfPieces;
}
