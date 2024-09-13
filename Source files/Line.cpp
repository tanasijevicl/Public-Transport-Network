#include "Line.h"

Line::Line(const string& name) : name_(name), line_end_(nullptr) {}

Line::~Line() {
	line_end_ = nullptr;
	stations_.clear();
}


string Line::getLineName() const {
	return name_;
}

const vector<Station*>& Line::getLineStations() const { 
	return stations_;
}


Station* Line::getLineStart() const {
	if (!stations_.empty()) return stations_[0];
	else throw NotFound("Station doesn't exist");
}

Station* Line::getLineEnd() const {
	if (line_end_) return line_end_;
	else throw NotFound("Station doesn't exist");
}


void Line::setLineEnd() {
	if (!stations_.empty()) line_end_ = stations_.back();
	else throw InvalidArgument("Invalid line input!");
}

void Line::addStation(Station* station) {
	stations_.push_back(station);
}
