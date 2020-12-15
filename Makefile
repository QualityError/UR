
output: main.o ur.o global.o display.o players.o
	g++ main.o ur.o global.o display.o players.o -o output -lncurses

main.o: main.cpp
	g++ -c main.cpp -lncurses

ur.o: ur.cpp
	g++ -c ur.cpp

global.o: global.cpp
	g++ -c global.cpp

display.o: display.cpp
	g++ -c display.cpp -lncurses
	
players.o: players.cpp
	g++ -c players.cpp

test.o: test.cpp
	g++ -c test.cpp

clean:
	rm *.o output

test: test.o ur.o global.o display.o players.o
	g++ test.o ur.o global.o display.o players.o -o output -lncurses
