
#include "player.h"

int Player::getId() const {
	return id;
}

const std::string& Player::getName() const {
	return name;
}

int Player::getOffset() const {
	return offset;
}

int Player::getMoney() const {
	return money;
}

int Player::getUnitCount() const {
	return unitCount;
}

void Player::move(int steps) {
	offset += steps;
}

void Player::increaseMoney(int amount) {
	money += amount;
}
