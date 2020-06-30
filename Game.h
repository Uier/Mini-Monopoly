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
	Game(const int num_players, const std::string & map_filename = DEFAULT_MAP_FILENAME): worldMap(map_filename), players(num_players) {};

	void init();
	void start();
private:

	const WorldMap worldMap;
	WorldPlayers players;

	void rollDice(Player & player);

	void fineOrBuy(Player & player, MapUnit & map_unit);
	void upgradeOrNot(Player & player, UpgradableUnit & map_unit);
	void payFine(Player & player, MapUnit & map_unit);
	void buyUnit(Player & player, MapUnit & map_unit);

};

#endif
