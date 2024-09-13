// Exception classes

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
using namespace std;

class Line;
class Station;

class InvalidArgument : public exception {
public:
	InvalidArgument(const char* error) : exception(error) {}
};

class InvalidUserInput : public exception {
public:
	InvalidUserInput(const char* error) : exception(error) {}
};

class SystemError : public exception {
public:
	SystemError(const char* error) : exception(error) {}
};

class NotFound : public exception {
public:
	NotFound(const char* error) : exception(error) {}
};

class NotUpdated : public exception {
public:
	NotUpdated(const char* error) : exception(error) {}
};

class StationAlreadyExist : public exception {
public:
	StationAlreadyExist(Station* station, const char* error) : exception(error), station_(station) {}
	Station* getStation() { return station_; }
private:
	Station* station_;
};

class LineAlreadyExist : public exception {
public:
	LineAlreadyExist(Line* line, const char* error) : exception(error), line_(line) {}
	Line* getLine() { return line_; }
private:
	Line* line_;
};

#endif
