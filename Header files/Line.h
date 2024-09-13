#ifndef LINE_H
#define LINE_H

#include "Exceptions.h"
#include <string>
#include <vector>
using namespace std;

class Station;

class Line {
public:
	Line(const string& name);
	Line(const Line&) = delete;
	Line(Line&&) = delete;
	~Line();
	
	string getLineName() const;								// Returns the name of the station
	const vector <Station*>& getLineStations() const;		// Returns the stations through which the line passes
	
	Station* getLineStart() const;							// Returns the starting station
	Station* getLineEnd() const;							// Returns the end station

	void setLineEnd();										// Sets the last station
	void addStation(Station* station);						// Adds a line station

private:
	string name_;						// Line name
	Station* line_end_;					// End station
	vector <Station*> stations_;		// Stations through which the line passes
};

#endif
