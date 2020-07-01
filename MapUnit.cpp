#include "MapUnit.h"

#include <assert.h>

bool MapUnit::isJail() const { 
	return (TYPE == 'J'); 
}
bool MapUnit::isOwner(int player) const { 
	return (owner == player); 
}
bool MapUnit::buyable() const { 
	return ( !isJail() && owner == NOBODY ); 
}
void MapUnit::setOwner(int player) { 
	owner = player; 
}
bool MapUnit::upgradable() const { 
	return false; 
}
void MapUnit::release() { 
	owner = NOBODY; 
}
int MapUnit::getId() const { 
	return ID; 
}
int MapUnit::getPrice() const { 
	return PRICE; 
}
const std::string & MapUnit::getName() const { 
	return NAME; 
}
int MapUnit::getOwner() const { 
	return owner; 
}


int UpgradableUnit::getUpgradePrice() const { 
	return UPGRADE_PRICE; 
}
int UpgradableUnit::getLevel() const { 
	return level; 
}
int UpgradableUnit::travelFine() const {
	assert(1 <= level && level <= MAX_LEVEL);
	return FINE_OF_LEVEL[level-1];
}
bool UpgradableUnit::upgradable() const { 
	return (level+1 <= MAX_LEVEL); 
}
void UpgradableUnit::upgrade() { 
	level += 1; 
}
void UpgradableUnit::release() {
	owner = NOBODY;
	level = 1;
}


int CollectableUnit::number_of_units_of_owner[MAX_PLAYER];
void CollectableUnit::setOwner(int player) {
	owner = player;
	number_of_units_of_owner[owner] += 1;
}
int CollectableUnit::travelFine() const {
	assert(0 <= owner && owner < MAX_PLAYER);
	return number_of_units_of_owner[owner] * UNIT_FINE;
}
void CollectableUnit::release() {
	number_of_units_of_owner[owner] -= 1;
	owner = NOBODY;
}


int RandomCostUnit::travelFine() const { 
	return randint(1, 6) * UNIT_FINE; 
}

int JailUnit::travelFine() const {
	return 0;
}
void JailUnit::addPlayer(int player) { 
	player_in_jail.insert(player); 
}
void JailUnit::removePlayer(int player) { 
	player_in_jail.erase(player); 
}
