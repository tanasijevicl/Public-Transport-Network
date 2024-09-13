#ifndef CONNECTION_H
#define CONNECTION_H

class Line;
class Station;

class Connection {
public:
	Connection(Station* station, Line* line);

	Station* getStation();		// Returns the next station
	Line* getLine();			// Returns the line the stations are connected to

private:
	Station* station_;			// Next station
	Line* line_;				// The line with which the stations are connected
};

#endif
