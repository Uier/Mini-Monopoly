#include "MapUnit.h"
#include <vector>
#include <sstream>

class WorldMap {

friend

public:
	WorldMap(std::string filename) {
		FILE *pF = fopen(filename, "r");
		if ( pF == nullptr ) {
			std::cerr << "Try to open " << filename << "\n";
			std::cerr << "ERR: No such file.\n";
			throw;
		}
		string row;
		while ( getline(pF, row) ) {
			char type;	
			row >> type;
			std::string name;	
			row >> name;
			int price;	
			row >> price;
			MapUnit *generator;
			switch ( type ) {
				case 'U':
					int upgrade_price;	
					row >> upgrade_price;
					int fine_of_level[5];
					for ( int i=0; i<5; ++i )	row >> fine_of_level[i];
					generator = new UpgradableUnit(worldMap.size(), name, price, upgrade_price, fine_of_level);
					break;
				case 'C':
					int unit_fine;
					row >> unit_fine;
					generator = new CollectableUnit(worldMap.size(), name, price, unit_fine);
					break;
				case 'R':
					int unit_fine;
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
	
	MapUnit & getUnit(int offset) const {
		int index = offset % worldMap.size();
		return *worldMap[index];
	}

private:
	const vector<MapUnit*> worldMap;

}