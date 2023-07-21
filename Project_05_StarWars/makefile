starwars.out: A5.o game.o getfile.o show_win_lose.o myShip.o enemyShips.o movingShips.o ships.o bullet.o rsdl.o
	g++ -o starwars.out A5.o game.o getfile.o show_win_lose.o myShip.o enemyShips.o movingShips.o ships.o bullet.o rsdl.o -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

A5.o: A5.cpp game.hpp getfile.hpp show_win_lose.hpp
	g++ -c A5.cpp

game.o: game.cpp game.hpp getfile.hpp myShip.hpp ships.hpp enemyShips.hpp bullet.hpp
	g++ -c game.cpp
	
myShip.o: myShip.cpp myShip.hpp movingShips.hpp bullet.hpp
	g++ -c myShip.cpp
	
enemyShips.o: enemyShips.cpp enemyShips.hpp movingShips.hpp bullet.hpp
	g++ -c enemyShips.cpp

movingShips.o: movingShips.cpp movingShips.hpp ships.hpp
	g++ -c movingShips.cpp

ships.o: ships.cpp ships.hpp
	g++ -c ships.cpp

bullet.o: bullet.cpp bullet.hpp myShip.hpp
	g++ -c bullet.cpp

getfile.o: getfile.cpp getfile.hpp ships.hpp rsdl.hpp enemyShips.hpp
	g++ -c getfile.cpp

show_win_lose.o: show_win_lose.cpp show_win_lose.hpp
	g++ -c show_win_lose.cpp

rsdl.o: rsdl.cpp rsdl.hpp
	g++ -c rsdl.cpp

clean:
	rm starwars.out *.o