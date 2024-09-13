#ifndef SYSTEM_LOAD_H
#define SYSTEM_LOAD_H

#include "Exceptions.h"
#include "Line.h"
#include "Station.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class SystemLoad {
public:
	SystemLoad();
	SystemLoad(const SystemLoad&) = delete;
	SystemLoad(SystemLoad&&) = delete;

	Station* loadStation(const string& argument);								// Loads the station
	Line* loadLine(string& argument, const vector <Station*>& stations);		// Loads the line

private: 

	// Pomocne funkcije

	int stringToInt(const string& tmp);									// Converts a string to an integer
	Station* findStation(const vector <Station*>& stations, int id);	// Finds the station by ID

	int extractStationId(const string& argument);						// Extracts station ID
	string extractStationName(const string& argument);					// Extracts station name

	string extractLineName(const string& argument);						// Extracts the line name
	int extractStation(const string& argument, int& pos);				// Extracts line stations
};

#endif