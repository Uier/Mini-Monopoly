#include "util.h"
#include <set>
#include <assert.h>

const int MAX_LEVEL = 5;
const int MAX_Player = 4;

class MapUnit {

public:
	/*
		TODO:
			- Buy Method (change owner)
	*/

	MapUnit(
		const char &type
		const int &id,
		const std::string &name,
		const int &price = -1
	) : TYPE(type),
		ID(id),
		NAME(name),
		PRICE(price) {}

	/*
		TODO: 
			- move some data to protected
	*/
	const char TYPE;
	const int ID, PRICE;
	const std::string NAME;
	int owner = NULL;

	bool isJail() { return (TYPE == 'J'); }
	bool isOwner(const int &player) { return (owner == player); }
	bool buyable() { return (!isJail() && owner == NULL); }
	virtual int travelFine();
	virtual bool upgradable() { return false; }
	virtual void release() { owner = NULL; }

private:

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

	const int & getUpgradePrice() { return UPGRADE_PRICE; }
	virtual const int & travelFine() const {
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

	static int number_of_units_of_owner[MAX_Player];

	virtual int travelFine() {
		assert(0 <= owner < MAX_Player);
		return number_of_units_of_owner[owner] * UNIT_FINE;
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

	virtual int travelFine() { return randint(1, 6) * UNIT_FINE; }

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

