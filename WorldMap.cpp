#include "WorldMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

WorldMap::WorldMap(std::string filename) {
	std::ifstream fin(filename.c_str());
	if ( fin.fail() ) {
		std::cerr << strerror(errno);
		throw;
	}
	std::string r;
	while ( getline(fin, r) ) {
		std::stringstream row(r);
		char type = 0;	
		int price = 0, upgrade_price = 0, unit_fine = 0;
		row >> type;
		std::string name;	
		row >> name;
		row >> price;
		MapUnit *generator;
		switch ( type ) {
			case 'U':
				row >> upgrade_price;
				int fine_of_level[UpgradableUnit::MAX_LEVEL];
				for ( int i=0; i<UpgradableUnit::MAX_LEVEL; ++i )	row >> fine_of_level[i];
				generator = new UpgradableUnit(worldMap.size(), name, price, upgrade_price, fine_of_level);
				break;
			case 'C':
				row >> unit_fine;
				generator = new CollectableUnit(worldMap.size(), name, price, unit_fine);
				break;
			case 'R':
				row >> unit_fine;
				generator = new RandomCostUnit(worldMap.size(), name, price, unit_fine);
				break;
			case 'F':
				generator = new JailUnit(worldMap.size(), name, price);
				break;
			default:
				std::cerr << "Unknown type: " << type << '\n';
				throw;
		}
		worldMap.emplace_back(generator);
	}
}

MapUnit & WorldMap::getUnit(const int offset) const {
	int index = offset % worldMap.size();
	return *worldMap[index];
}
