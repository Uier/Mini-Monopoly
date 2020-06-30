#ifndef MINI_MONOPOLY_WORLD_PLAYERS_H
#define MINI_MONOPOLY_WORLD_PLAYERS_H

#include <string>

#include "player.h"

struct playerList {
	Player * player;
	playerList * next;
	playerList * prev;
};

class WorldPlayers {
public:
	WorldPlayers(const int np);
	~WorldPlayers();

	int getNumActive() const;

	Player & next();
	Player & getById(const int id) const;

	void remove(const int id);
private:
	int num_active = 0;

	const int num_players = 0;
	playerList * const players = nullptr;

	playerList * cur_player = nullptr;

	void activate(const std::string & name);
};

#endif
