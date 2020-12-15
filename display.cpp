
#include "global.hpp"
#include <ncurses.h>
#include <unistd.h>//for usleep
#include "display.hpp"

//INIT
void initNcurses(){
		//init ncurses
		initscr();
		noecho();
		cbreak();
		WINDOW * win = newwin(10,30,0,0);//height width start y start x

		//initial print
		printBoard();
		mvprintw(10,0,"Roll:");
}
void endNcurses(){
		//end ncurses
		endwin();

}
//MAPING
int mapX(int c){
	if(c < 4){
		return 3 - c;
	} else if (c < 12)
	{
		return c - 4;
	} else	{
		return 19 - c;
	}
}
int mapY(int side, int i){
	if(i < 4 || i > 11){
		return side * 2;
	} else {
		return 1;
	}
}
//PRINTING
void printPieces(){
	const char * sym;
	for(int i = 0; i < 14; i++){//for each side or side
		for(int p = 0; p < 2; p++){
			sym = " ";
			if(i == 3 || i == 7 || i == 13){
				sym = ".";//roll again square
			}
			if( i < 12 && i > 3){//if centerlane
				if(board[0][i]){
					sym = symbol[0]; 
				} else if(board[1][i]){
					sym = symbol[1];
				}
			} else if(board[p][i]){
				sym = symbol[0]; 
				if(p == 1){
					sym = symbol[1]; 
				}
			}
			mvprintw(mapY(p,i) * 2 + 2, mapX(i) * 2 + 1, sym);// + yoff , + xoff
		}
	}
}
void printBoard(){
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 14; j++){
			int x = mapX(j) * 2 + 1;// + xoff
			int y = mapY(i,j) * 2 + 2;// + yoff
			mvprintw(y,x+1, "|");
			mvprintw(y,x-1, "|");

			mvprintw(y+1,x-1, "-");
			mvprintw(y+1,x, "-");
			mvprintw(y+1,x+1, "-");

			mvprintw(y-1,x-1, "-");
			mvprintw(y-1,x, "-");
			mvprintw(y-1,x+1, "-");
		}
	}
}
void printMultible(const char * sym, int times){
	for(int i = 0; i < times; i++){
		printw(sym);
	}
}
void updateDisplay(){
	if(!display){
		return;
	}
			//PRINT PIECES ON BOARD
	printPieces();
			//PRINT PIECE POOLS
	//side 0
	mvprintw(0,0,"          ");//clear line
	move(0,0);
	printMultible(symbol[0],piecePool[0]);
	//side 1
	mvprintw(8,0,"          ");//clear line
	move(8,0);
	printMultible(symbol[1],piecePool[1]);
			//PRINT PIECES WON
	//side 0
	move(2,17);
	printMultible(symbol[0],wonPieces[0]);
	//side 1
	move(6,17);
	printMultible(symbol[1],wonPieces[1]);
			//refresh
	refresh();
	usleep(sleepTime);
}
void message(const char * msg, int x){//must %d if setting x
	if(!display){
		return;
	}
	mvprintw(11,0, "                 ");//clear privious message
	if(x == -1){
		mvprintw(11,0, msg);
	} else {
		mvprintw(11,0, msg, x);
	}
	refresh();
	sleep(sleepTime);
}
void printOutcome(int winner){
	if(!display){
		return;
	}
	//OUTCOME
	if(!winner){
		message("TOP SIDE WINS");
	} else {
		message("BOTTOM SIDE WINS");
	}

	//wait for key pressed to end
	getch();
}

void printRoll(int roll){
		mvprintw(10,5,"%d", roll);
		usleep(sleepTime);
}
