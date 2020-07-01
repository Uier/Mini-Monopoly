#ifndef MAPUNIT__
#define MAPUNIT__

#include "util.h"
#include <set>
#include <string>

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

	bool isJail() const;
	bool isOwner(int player) const;
	bool buyable() const;
	virtual void setOwner(int player);
	virtual int travelFine() const;
	virtual bool upgradable() const;
	virtual void release();
	int getId();
	int getPrice();
	std::string getName();
	int getOwner();

protected:
	constexpr static int NOBODY = -1;
	const char TYPE;
	const int ID, PRICE;
	const std::string NAME;
	int owner = NOBODY;

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

	int getUpgradePrice() const;
	int getLevel() const;
	virtual int travelFine() const;
	virtual bool upgradable() const;
	void upgrade();
	virtual void release();

private:
	constexpr static int MAX_LEVEL = 5;
	const int UPGRADE_PRICE;
	const int *FINE_OF_LEVEL;
	int level = 1;

};


class CollectableUnit : public MapUnit {

private:
	constexpr static int MAX_PLAYER = 4;
	const int UNIT_FINE;
	
public:
	CollectableUnit(
		const int &id, 
		const std::string &name,
		const int &price,
		const int &unit_fine
	) : MapUnit('C', id, name, price),
		UNIT_FINE(unit_fine) {}

	static int number_of_units_of_owner[MAX_PLAYER];

	virtual void setOwner(int player);
	virtual int travelFine() const;
	virtual void release();

};


class RandomCostUnit : public MapUnit {
	
public:
	RandomCostUnit(
		const int &id, 
		const std::string &name,
		const int &price,
		const int &unit_fine
	) : MapUnit('R', id, name, price),
		UNIT_FINE(unit_fine) {}

	virtual int travelFine() const;

private:
	const int UNIT_FINE;

};


class JailUnit : public MapUnit {

public:
	JailUnit(
		const int &id, 
		const std::string &name,
		const int &price
	) : MapUnit('J', id, name, price) {}

	void addPlayer(int player);
	void removePlayer(int player);

private:
	std::set<int> player_in_jail;

};


#endif