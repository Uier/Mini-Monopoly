all: main.cpp Game.cpp MapUnit.cpp player.cpp util.cpp WorldMap.cpp WorldPlayers.cpp
	g++ -std=c++17 $^