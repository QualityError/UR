
#include "global.hpp"
#include <iostream>
#include <unistd.h>//for usleep

#include "players.hpp"
#include "ur.hpp"
#include "display.hpp"





int main(){
	//seed random numbers
	srand((int)time(0));

	if(display){
		initNcurses();
	}


	int winner;
	int numberOfGames = 1;
	int topWins = 0;
	int bottomWins = 0;
	for(int i = 0; i < numberOfGames; i++){
		int players[] = {safetyAI,safetyAI};
		winner = game(players);

		topWins += !winner;
		bottomWins += winner;
	}


	if(display){
		printOutcome(winner);
		endNcurses();
	}

//	std::cout << "Out of " << numberOfGames << " of Games" << std::endl;
//	std::cout << "BASIC AI won: " << topWins << std::endl;
//	std::cout << "RANDOM AI won: " << bottomWins << std::endl;
	
	return 0;
}

//change "Pieces:" to a printing of each sides tokens
//add a name to each player to see who's turn it is. X is choosing. turnFor(0,0,"X")
//add animation //color?
//add multi threading for mass game testing


/*

*/
