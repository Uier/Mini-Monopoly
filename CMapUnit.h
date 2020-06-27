#include "util.h"
#include <vector>

const int MAX_LEVEL = 5;
const int MAX_Player = 4;

class MapUnit {

public:
	/*
		TODO:
			- Destructor ?
			- Hiding data to private
			- func: Release Units
	*/
	/*
		Constructor
	*/
	MapUnit(
		const int &id,
		const std::string &name,
		const int &price
	) : ID(id),
		PRICE(price),
		NAME(name) {}
	/*
		Properties
	*/
	const int ID, PRICE;
	const std::string NAME;
	int owner = NULL;
	/*
		Methods
	*/
	virtual int travelFine();
	virtual bool isJail() { return false; }
	virtual bool buyable() { return (owner == NULL); }
	virtual void setOwner(int user_id) { owner = user_id; }
	void releaseUnit();

private:

};


class UpgradableUnit : public MapUnit {
	
public:
	/*
		TODO:
			- Destructor ?
			- Hiding data to private
	*/
	/*
		Constructor
	*/
	UpgradableUnit(
		const int &id, 
		const std::string &name,
		const int &price,
		const int &upgrade_price,
		const int *fine_of_level
	) : MapUnit(id, name, price), 
		UPGRADE_PRICE(upgrade_price), 
		FINE_OF_LEVEL(fine_of_level) {}
	/*
		Properties
	*/
	const int UPGRADE_PRICE;
	const int FINE_OF_LEVEL[MAX_LEVEL];
	int level = 0;
	/*
		Methods
	*/
	virtual int travelFine() {
		assert(0 <= level < MAX_LEVEL);
		return FINE_OF_LEVEL[level];
	}

private:

};


class CollectableUnit : public MapUnit {
	
public:
	/*
		TODO:
			- Destructor ?
			- Hiding data to private
	*/
	/*
		Constructor
	*/
	CollectableUnit(
		const int &id, 
		const std::string &name,
		const int &price,
		const int &unit_fine,
	) : MapUnit(id, name, price),
		UNIT_FINE(unit_fine) {}
	/*
		Properties
	*/
	const int UNIT_FINE;
	static int number_of_units_of_owner[MAX_Player];
	/*
		Methods
	*/
	virtual int travelFine() {
		assert(0 <= owner < MAX_Player);
		return number_of_units_of_owner[owner] * UNIT_FINE;
	}
	virtual void setOwner(int user_id) {
		owner = user_id;
		number_of_units_of_owner[owner] += 1;
	}

private:

};


class RandomCostUnit : public MapUnit {
	
public:
	/*
		TODO:
			- Destructor ?
			- Hiding data to private
	*/
	/*
		Constructor
	*/
	RandomCostUnit(
		const int &id, 
		const std::string &name,
		const int &price,
		const int &unit_fine,
	) : MapUnit(id, name, price),
		UNIT_FINE(unit_fine) {}
	/*
		Properties
	*/
	const int UNIT_FINE;
	/*
		Methods
	*/
	virtual int travelFine() {
		return randint(1, 6) * UNIT_FINE;
	}

private:

};


class JailUnit : public MapUnit {
public:
	/*
		TODO:
			- Destructor ?
			- Hiding data to private
	*/
	/*
		Constructor
	*/
	JailUnit(
		const int &id, 
		const std::string &name,
		const int &price,
	) : MapUnit(id, name, price) {}
	/*
		Properties
	*/
	vector<int> player_in_jail;
	/*
		Methods
	*/
	virtual bool isJail() { return true; }

private:

};

