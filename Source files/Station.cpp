#include "Station.h"

Station::Station(int id, const string& name) : id_(id), name_(name) {}

Station::~Station() {
	lines_.clear();
}


int Station::getStationId() const {
	return id_;
}

string Station::getStationName() const {
	return name_;
}

const vector<Line*>& Station::getStationLines() const {
	return lines_;
}

bool Station::checkLine(Line* line) const {
	for (Line* tmp : lines_) {
		if (tmp == line) return true;
	}
	return false;
}

void Station::addStationLine(Line* line) {
	if (!checkLine(line)) lines_.push_back(line);
}
