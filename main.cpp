//
// Created by yuta on 6/29/2020.
//

#include <iostream>
#include <algorithm>

#include <cstdlib>
#include <ctime>

#include "Game.h"

int main() {
	srand(time(NULL));

	std::cout << "How many players (Minimum: 1, Maximum: 4)...> ";
	
	int num_players;
	std::cin >> num_players; num_players = std::clamp(num_players, 1, 4);

	// Game game("map.dat");
	Game game(num_players);

	game.start();

	return 0;
}