#ifndef STATION_H
#define STATION_H

#include "Exceptions.h"
#include <string>
#include <vector>
using namespace std;

class Line;

class Station {
public:
	Station(int id, const string& name);
	Station(const Station&) = delete;
	Station(Station&&) = delete;
	~Station();

	int getStationId() const;								// Returns the station ID
	string getStationName() const;							// Returns the name of the station
	const vector <Line*>& getStationLines() const;			// Returns lines that stop at a station
	void addStationLine(Line* line);						// Adds a line that stops at a station

private:
	int id_;						// Station ID
	string name_;					// Station name
	vector <Line*> lines_;			// Lines that stop at the station

	bool checkLine(Line* line) const;		// Checks if the line has already been added
};

#endif
