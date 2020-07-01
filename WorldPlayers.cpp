#include <sstream>
#include <iostream>

#include "WorldPlayers.h"

constexpr int MAX_PLAYERS = 4;
constexpr char const * DEFAULT_PLAYER_NAME[MAX_PLAYERS] = {"Ala", "Bla", "Cla", "Dla"};

std::string getline(const std::string & prompt, const std::string & default_value) {
	std::cout << prompt << "...> ";
	std::string inputs;
	std::getline(std::cin, inputs); {
		size_t end = inputs.find_last_not_of("\n");
		if(end != std::string::npos) {
			inputs = inputs.substr(0, end + 1);
		}
	}
	if(inputs.empty()) {
		inputs = default_value;
	}
	return inputs;
}

WorldPlayers::WorldPlayers(const int np): num_players(np), players(new PlayerList[np]), cur_player(players) {
	for(int i = 0; i < np; ++i) {
		std::stringstream ss;
		ss << "Please input player " << i << "'s name (Default: " << DEFAULT_PLAYER_NAME[i] << ")";

		std::string name(getline(ss.str(), DEFAULT_PLAYER_NAME[i]));
		activate(name);
	}
}

WorldPlayers::~WorldPlayers() {
	for(int i = 0; i < num_players; ++i) {
		delete players[i].player;
	}
	delete [] players;
}

int WorldPlayers::getNumActive() const {
	return num_active;
}

Player & WorldPlayers::current() {
	return *cur_player->player;
}

Player & WorldPlayers::next() {
	cur_player = cur_player->next;
	return current();
}

Player & WorldPlayers::getById(const int id) const {
	return *players[id].player;
}

void WorldPlayers::remove(const int id) {
	players[id].prev->next = players[id].next;
	players[id].next->prev = players[id].prev;
	--num_active;
}

void WorldPlayers::activate(const std::string & name) {
	const int id = num_active++;
	const int prev_id = (id - 1 + num_active) % num_active;

	players[id].player = new Player(id, name);

	players[id].next = players;
	players[prev_id].next = players + id;

	players[id].prev = players + prev_id;
	players[0].prev = players + id;
}
