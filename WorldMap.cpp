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
		char type;	
		row >> type;
		std::string name;	
		row >> name;
		int price;	
		row >> price;
		MapUnit *generator;
		switch ( type ) {
			int upgrade_price, unit_fine;	
			case 'U':
				row >> upgrade_price;
				int fine_of_level[5];
				for ( int i=0; i<5; ++i )	row >> fine_of_level[i];
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

MapUnit & WorldMap::getUnit(int offset) const {
	int index = offset % worldMap.size();
	return *worldMap[index];
}

int main() {
	
}