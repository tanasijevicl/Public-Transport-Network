#include "Connection.h"

Connection::Connection(Station* station, Line* line) : station_(station), line_(line) {}

Station* Connection::getStation() {
	return station_;
}

Line* Connection::getLine() {
	return line_;
}
