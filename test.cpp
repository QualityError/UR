#include "iostream"
#include "global.hpp"
#include "players.hpp"
#include "ur.hpp"

int main () {


	bool side[] = {0,0,0,0,0,0,0,1,0,0,0,0,0,0};
	bool sideTwo[] = {0,1,0,0,0,0,1,0,0,0,0,0,0,0};

	for(int i = 0; i < 14; i++){
		board[0][i] = side[i];
		board[1][i] = sideTwo[i];
	}


	int passed = 0;
	int total = 4;
	
	passed += legalMove(0,2,1) == false;
	passed += legalMove(2,1,1) == false;
	passed += legalMove(1,2,1) == true;
	passed += legalMove(1,0,1) == false;

	std::cout << "Passed " << passed << " of " << total << std::endl;


	endNcurses();
	return 0;
}
