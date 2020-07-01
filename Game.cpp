#include <random>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

#include "Game.h"
#include "player.h"

std::random_device rd;
std::default_random_engine gen = std::default_random_engine(rd());
std::uniform_int_distribution<int> dis(1, 6);

int selectOptions(const std::string & prompt, const std::vector<std::string> & options) {
	std::cout << prompt << "(";
	if(options.empty()) {
		return 0;
	} else {
		std::cout << "1: " << options[0] << " [default]";
	}
	for(int i = 1; i < options.size(); ++i) {
		std::cout << " / " << i + 1 << ": " << options[i];
	}
	std::cout << ") ...> ";
	std::string inputs;
	std::getline(std::cin, inputs);
	std::istringstream iss(inputs);

	int selected = 0;
	iss >> selected;

	if(selected < 1 || selected > options.size()) {
		selected = 1;
	}

	return selected;
}

bool isInJail(Player & player) {
	if(player.isInJail()) {
		player.setInJail(false);
		return true;
	}
	return false;
}

MapUnit & rollDice(Player & player, const WorldMap & worldMap) {
	player.move(dis(gen));
	return worldMap.getUnit(player.getOffset());
}

Game::State mapState(const MapUnit & map_unit, int player_id) {
	Game::State ret;

	if(map_unit.isJail()) {
		ret = Game::GO_TO_JAIL;
	} else if(map_unit.isOwner(player_id)) {
		ret = Game::UPGRADE_UNIT;
	} else if(map_unit.buyable()) {
		ret = Game::BUY_UNIT;
	} else {
		ret = Game::PAY_FINE;
	}

	return ret;
}

void payFine(Player & player, Player & owner, const MapUnit & map_unit) {
	int fine = map_unit.travelFine();

	std::cout << "You have to pay " << fine << " to player " << owner.getId() << " (" << owner.getName() << ")" << std::endl;

	player.increaseMoney(-fine);
	owner.increaseMoney(fine);
}

void buyUnit(Player & player, MapUnit & map_unit) {
	const int unit_price = map_unit.getPrice();
	if(unit_price > player.getMoney()) {
		return;
	}

	std::stringstream ss;
	ss << player.getName() << ", do you want to buy " << map_unit.getName() << "?";

	int select = selectOptions(ss.str(), {"Yes", "No"});
	if(select == 2) {
		return;
	}

	player.buyUnit(unit_price, map_unit.getId());
	map_unit.setOwner(player.getId());
}

void upgradeUnit(Player & player, UpgradableUnit & map_unit) {
	const int upgrade_price = map_unit.getUpgradePrice();
	if(upgrade_price > player.getMoney()) {
		return;
	}

	if(!map_unit.upgradable()) {
		return;
	}

	std::stringstream ss;
	ss << player.getName() << ", do you want to upgrade " << map_unit.getName() << "?";

	int select = selectOptions(ss.str(), {"Yes", "No"});
	if(select == 2) {
		return;
	}

	player.increaseMoney(-map_unit.getUpgradePrice());
	map_unit.upgrade();
}

void releaseUnits(Player & player, const WorldMap & worldMap) {
	for(auto unit_id : player.getBoughtUnits()) {
		MapUnit & unit = worldMap.getUnit(unit_id);
		unit.release();
	}
}

void Game::start() {
	for(state = SET_UP; state != GAME_OVER;) {
		switch(state) {
			case SET_UP: {
				state = CHECK_IS_IN_JAIL;
				break;
			}
			case CHECK_IS_IN_JAIL: {
				state = isInJail(players.current()) ? NEXT_PLAYER : UPDATE_UI;
				break;
			}
			case UPDATE_UI: {
				// TODO: Update UI
				state = ROLL_DICE;
				break;
			}
			case ROLL_DICE: {
				MapUnit & map_unit = rollDice(players.current(), worldMap);
				state = mapState(map_unit, players.current().getId());
				break;
			}
			case GO_TO_JAIL: {
				players.current().setInJail(true);
				state = NEXT_PLAYER;
				break;
			}
			case PAY_FINE: {
				Player & player = players.current();
				const MapUnit & map_unit = worldMap.getUnit(player.getOffset());
				Player & owner = players.getById(map_unit.getOwner());
				payFine(player, owner, map_unit);
				state = CHECK_IS_BANKRUPT;
				break;
			}
			case BUY_UNIT: {
				Player & player = players.current();
				MapUnit & map_unit = worldMap.getUnit(player.getOffset());
				buyUnit(player, map_unit);
				state = TEAR_DOWN;
				break;
			}
			case UPGRADE_UNIT: {
				Player & player = players.current();
				UpgradableUnit & map_unit = dynamic_cast<UpgradableUnit &>(worldMap.getUnit(player.getOffset()));
				upgradeUnit(player, map_unit);
				state = TEAR_DOWN;
				break;
			}
			case CHECK_IS_BANKRUPT: {
				Player & player = players.current();
				if(player.getMoney() < 0) {
					releaseUnits(player, worldMap);
					players.remove(player.getId());
				}
				state = TEAR_DOWN;
				break;
			}
			case TEAR_DOWN: {
				state = players.getNumActive() > 1 ? NEXT_PLAYER : GAME_OVER;
				break;
			}
			case NEXT_PLAYER: {
				players.next();
				state = CHECK_IS_IN_JAIL;
				break;
			}
			case GAME_OVER: {
				// Impossible!
				break;
			}
		}
	}
	const Player & winner = players.next();
	std::cout << "The winner is player " << winner.getId() << " (" << winner.getName() << ") !" << std::endl;
}
