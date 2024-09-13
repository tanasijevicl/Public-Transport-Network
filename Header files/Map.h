#ifndef MAP_H
#define MAP_H

#include "Connection.h"
#include "Exceptions.h"
#include "Line.h"
#include "Station.h"

#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Map {
public:
	Map();
	~Map();
	Map(const Map&) = delete;
	Map(Map&&) = delete;

	void updateMap(const vector<Line*>& lines, const vector<Station*>& stations);	// Creates (finds) connections between stations
	void findCommonLines(Line* line, map<Line*, int>& common_lines) const;			// Finds lines with which the given line has common stations

	const vector<Connection*>& findRoute(Station* start, Station* end);				// Finds any route
	const vector<Connection*>& findFastRoute(Station* start, Station* end);			// Finds the fastest route (passing through the fewest stations)
	const vector<Connection*>& findEasyRoute(Station* start, Station* end);			// Finds the route with the fewest transfers

private:
	map <Station*, vector <Connection*>> map_;			// Map of station and direct connections ('key'->Station, 'data'->Connections with other stations)

	// Member auxiliary data
	map <int, vector <Connection*>> routes_;			// Found routes (Routes consist of a series of connections between stations)
	int route_cnt_;

	// Helper functions
	void setDefault();									// Sets the default value of auxiliary data
	void getRoutes(Station* start, Station* end);		// Finds all possible routes between stations
};

#endif
