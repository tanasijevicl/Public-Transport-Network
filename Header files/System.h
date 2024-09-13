#ifndef PUBLIC_TRANSPORT_H
#define PUBLIC_TRANSPORT_H

#include "Exceptions.h"
#include "Line.h"
#include "Map.h"
#include "Station.h"
#include "SystemLoad.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
using namespace std;

class System {
public:
	System();
	System(const System& system) = delete;
	System(System&& system) = delete;
	~System();
	
	void loadStations(const string& stations);					// Loads stations from file
	void loadLines(const string& lines);						// Loads lines from file

	void stationInfo(int id) const;								// Prints station information
	void lineInfo(const string& line_name) const;				// Prints information about lines
	void statisticalLineData(const string& line_name) const;	// Prints statistics line data

	void getRoute(int start_id, int end_id) const;				// Finds any route
	void getFastRoute(int start_id, int end_id) const;			// Finds the shortest route
	void getEasyRoute(int start_id, int end_id) const;			// Finds the route with the fewest transfers

private:
	vector <Station*> stations_;		// Stations
	vector <Line*> lines_;				// Lines
	SystemLoad* loader_;				// Class instance for loading system data
	Map* map_;							// An instance of the system mapping class

	// Helper functions

	Station* findStation(int id) const;				// Finds a station based on the ID
	Line* findLine(const string& name) const;		// Finds a line based on name

	void checkStation(Station* station) const;		// Checks if a station exists
	void checkLine(Line* line) const;				// Checks if a line exists

	string getInfo(Station* start, const vector <Connection*>& route) const;	// Processing the route found by the map
	void printOutput(const string& file_name, const string& output) const;		// Creates an output file
};

#endif 

