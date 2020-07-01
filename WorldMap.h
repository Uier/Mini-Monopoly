#ifndef WORLDMAP__
#define WORLDMAP__

#include "MapUnit.h"
#include <vector>

class WorldMap {

public:
	WorldMap(std::string filename);
	
	MapUnit & getUnit(int offset) const;

private:
	std::vector<MapUnit*> worldMap;

};


#endif