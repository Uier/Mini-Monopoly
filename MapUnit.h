#include "util.h"
#include <set>
#include <assert.h>

constexpr int MAX_LEVEL = 5;
constexpr int MAX_PLAYER = 4;

class MapUnit {

public:
	/*
		TODO:
			- Show Info ?
	*/

	MapUnit(
		const char &type,
		const int &id,
		const std::string &name,
		const int &price = -1
	) : TYPE(type),
		ID(id),
		NAME(name),
		PRICE(price) {}

	bool isJail() const { return (TYPE == 'J'); }
	bool isOwner(int player) const { return (owner == player); }
	bool buyable() const { return (!isJail() && owner == NULL); }
	virtual void buy(int player) { owner = player; }
	virtual int travelFine() const;
	virtual bool upgradable() const { return false; }
	virtual void release() { owner = NULL; }
	int getPrice() { return PRICE; }
	std::string getName() { return NAME; }

protected:
	const char TYPE;
	const int ID, PRICE;
	const std::string NAME;
	int owner = NULL;

};


class UpgradableUnit : public MapUnit {
	
public:
	UpgradableUnit(
		const int &id, 
		const std::string &name,
		const int &price,
		const int &upgrade_price,
		const int *fine_of_level
	) : MapUnit('U', id, name, price), 
		UPGRADE_PRICE(upgrade_price), 
		FINE_OF_LEVEL(fine_of_level) {}

	~UpgradableUnit() { delete[] FINE_OF_LEVEL; }

	int getUpgradePrice() const { return UPGRADE_PRICE; }
	int getLevel() const { return level; }
	virtual int travelFine() const {
		assert(0 <= level < MAX_LEVEL);
		return FINE_OF_LEVEL[level];
	}
	virtual bool upgradable() const { return (level+1 < MAX_LEVEL); }
	void upgrade() { level += 1; }
	virtual void release() {
		owner = NULL;
		level = 0;
	}

private:
	const int UPGRADE_PRICE;
	const int *FINE_OF_LEVEL;
	int level = 0;

};


class CollectableUnit : public MapUnit {
	
public:
	CollectableUnit(
		const int &id, 
		const std::string &name,
		const int &price,
		const int &unit_fine,
	) : MapUnit('C', id, name, price),
		UNIT_FINE(unit_fine) {}

	static int number_of_units_of_owner[MAX_PLAYER];

	virtual void buy(int player) {
		owner = player;
		number_of_units_of_owner[owner] += 1;
	}
	virtual int travelFine() const {
		assert(0 <= owner < MAX_PLAYER);
		return number_of_units_of_owner[owner] * UNIT_FINE;
	}
	virtual void release() {
		number_of_units_of_owner[owner] -= 1;
		owner = NULL;
	}

private:
	const int UNIT_FINE;

};


class RandomCostUnit : public MapUnit {
	
public:
	RandomCostUnit(
		const int &id, 
		const std::string &name,
		const int &price,
		const int &unit_fine,
	) : MapUnit('R', id, name, price),
		UNIT_FINE(unit_fine) {}

	virtual int travelFine() const { return randint(1, 6) * UNIT_FINE; }

private:
	const int UNIT_FINE;

};


class JailUnit : public MapUnit {

public:
	JailUnit(
		const int &id, 
		const std::string &name,
		const int &price,
	) : MapUnit('J', id, name, price) {}


	void addPlayer(int player) { player_in_jail.insert(player); }
	void removePlayer(int player) { player_in_jail.erase(player); }

private:
	set<int> player_in_jail;

};

