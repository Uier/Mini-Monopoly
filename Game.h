#ifndef MINI_MONOPOLY_GAME_H
#define MINI_MONOPOLY_GAME_H

#include <iostream>
#include <vector>
#include <set>

#include "player.h"
#include "WorldMap.h"
#include "WorldPlayers.h"

constexpr char const * DEFAULT_MAP_FILENAME = "map.dat";

class Game {
public:
	enum State {
		SET_UP,
		CHECK_IS_IN_JAIL,
		UPDATE_UI,
		ROLL_DICE,
		GO_TO_JAIL,
		PAY_FINE,
		BUY_UNIT,
		UPGRADE_UNIT,
		CHECK_IS_BANKRUPT,
		TEAR_DOWN,
		NEXT_PLAYER,
		GAME_OVER
	};

	Game(const int num_players, const std::string & map_filename = DEFAULT_MAP_FILENAME): worldMap(map_filename), players(num_players) {};

	void start();
private:
	State state = SET_UP;
	const WorldMap worldMap;
	WorldPlayers players;
};

#endif
