#include <random>
#include <sstream>

#include "Game.h"

std::random_device rd;
std::default_random_engine gen = std::default_random_engine(rd());
std::uniform_int_distribution<int> dis(1, 6);

void Game::start() {
	do {

		// TODO: Update UI

		Player & player = players.next();
		if(player.isInJail()) {
			player.setInJail(false);
			continue;
		}

		rollDice(player);

		MapUnit & map_unit = worldMap.getUnit(player.getOffset());
		if(map_unit.isJail()) {
			player.setInJail(true);
			continue;
		}

		map_unit.isOwner(player.getId()) ? fineOrBuy(player, map_unit) : upgradeOrNot(player, dynamic_cast<UpgradableUnit &>(map_unit));

		if(player.getMoney() < 0) {
			for(auto unit_id : player.getBoughtUnits()) {
				MapUnit & unit = worldMap.getUnit(unit_id);
				unit.release();
			}
			players.remove(player.getId());
		}
	} while(players.getNumActive() > 1);

	const Player & winner = players.next();
	std::cout << "The winner is player " << winner.getId() << " (" << winner.getName() << ")!";
}

void Game::rollDice(Player & player) {
	player.move(dis(gen));
}

void Game::fineOrBuy(Player & player, MapUnit & map_unit) {
	map_unit.buyable() ? payFine(player, map_unit) : buyUnit(player, map_unit);
}

void Game::upgradeOrNot(Player & player, UpgradableUnit & map_unit) {
	const int upgrade_price = map_unit.getUpgradePrice();
	if(upgrade_price > player.getMoney()) {
		return;
	}

	if(!map_unit.upgradable()) {
		return;
	}

	std::cout << player.getName() << ", do you want to upgrade " << map_unit.getName() << "? (1: Yes [default] / 2: No) ...> ";

	int select;
	std::cin >> select;
	if(select == 2) {
		return;
	}

	player.increaseMoney(-map_unit.getUpgradePrice());
	map_unit.upgrade();
}

void Game::payFine(Player & player, MapUnit & map_unit) {
	Player & onwer = players.getById(map_unit.getOwner());
	int fine = map_unit.travelFine();

	std::cout << "You have to pay " << fine << " to player " << onwer.getId() << " (" << onwer.getName() << ")";

	player.increaseMoney(-fine);
	onwer.increaseMoney(fine);
}

void Game::buyUnit(Player & player, MapUnit & map_unit) {
	const int unit_price = map_unit.getPrice();
	if(unit_price > player.getMoney()) {
		return;
	}

	std::cout << player.getName() << ", do you want to buy " << map_unit.getName() << "? (1: Yes [default] / 2: No) ...> ";

	int select;
	std::cin >> select;
	if(select == 2) {
		return;
	}

	player.buyUnit(unit_price, map_unit.getId());
	map_unit.buy(player.getId());
}
