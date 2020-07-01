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
	virtual int travelFine() const = 0;
	virtual bool upgradable() const;
	virtual void release();
	int getId() const;
	int getPrice() const;
	const std::string & getName() const;
	int getOwner() const;

protected:
	constexpr static int NOBODY = -1;
	const char TYPE = 0;
	const int ID = 0, PRICE = 0;
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

	constexpr static int MAX_LEVEL = 5;
	int getUpgradePrice() const;
	int getLevel() const;
	virtual int travelFine() const;
	virtual bool upgradable() const;
	void upgrade();
	virtual void release();

private:
	const int UPGRADE_PRICE = 0;
	const int *FINE_OF_LEVEL = nullptr;
	int level = 1;

};


class CollectableUnit : public MapUnit {
	
public:
	CollectableUnit(
		const int &id, 
		const std::string &name,
		const int &price,
		const int &unit_fine
	) : MapUnit('C', id, name, price),
		UNIT_FINE(unit_fine) {}

	constexpr static int MAX_PLAYER = 4;
	static int number_of_units_of_owner[MAX_PLAYER];

	virtual void setOwner(int player);
	virtual int travelFine() const;
	virtual void release();

private:
	const int UNIT_FINE = 0;

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
	const int UNIT_FINE = 0;

};


class JailUnit : public MapUnit {

public:
	JailUnit(
		const int &id, 
		const std::string &name,
		const int &price
	) : MapUnit('J', id, name, price) {}

	virtual int travelFine() const;
	void addPlayer(int player);
	void removePlayer(int player);

private:
	std::set<int> player_in_jail;

};


#endif