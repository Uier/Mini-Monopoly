#ifndef MINI_MONOPOLY_WORLD_PLAYERS_H
#define MINI_MONOPOLY_WORLD_PLAYERS_H

#include <string>

#include "player.h"

struct PlayerList {
	Player * player;
	PlayerList * next;
	PlayerList * prev;
};

class WorldPlayers {
public:
	WorldPlayers(const int np);
	~WorldPlayers();

	int getNumActive() const;

	Player & current();
	Player & next();
	Player & getById(const int id) const;

	void remove(const int id);
private:
	int num_active = 0;

	const int num_players = 0;
	PlayerList * const players = nullptr;

	PlayerList * cur_player = nullptr;

	void activate(const std::string & name);
};

#endif
