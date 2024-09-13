#include "SystemLoad.h"

SystemLoad::SystemLoad() {} 

Station* SystemLoad::loadStation(const string& argument) {
	int id = extractStationId(argument);			// Extract station ID
	string name = extractStationName(argument);		// Extract station name
	Station* station = new Station(id, name);
	
	return station;
}

Line* SystemLoad::loadLine(string& argument, const vector <Station*>& stations)
{
	string name = extractLineName(argument);		// Extract line name
	Line* line = new Line(name);

	try {
		// Checking the format of argument and adding line stations
		if (argument.find_first_of('#') == string::npos) throw InvalidArgument("Invalid line input!");
		int indicator = argument.find_first_of('#');
		int pos = argument.find_first_of(' ') + 1;
		argument.push_back(' ');

		bool set = false;
		// Loading the stations through which the line passes
		for (; pos < argument.length(); pos++) {

			// Save the last station (when '#' is reached)
			if (pos > indicator && set == false) {
				line->setLineEnd();
				set = true;
			}
			
			// Searching for the station and adding to the line, and adding line to the station
			int id = extractStation(argument, pos);    
			Station* station = findStation(stations, id);
			station->addStationLine(line);
			line->addStation(station);
		}

		return line;
	}
	catch (InvalidArgument error) {
		delete line;
		throw;
	}
	catch (NotFound error) {
		delete line;
		throw InvalidArgument("Invalid station list!");
	}
}


int SystemLoad::stringToInt(const string& tmp) {
	int id = 0;

	for (int pos = 0; pos < tmp.length(); pos++) {
		if (tmp[pos] == '#') return id;

		if (tmp[pos] >= '0' && tmp[pos] <= '9') {
			id = id * 10 + (tmp[pos] - '0');
		}
		else throw InvalidArgument("Invalid station Id!");
	}
	return id;
}

Station* SystemLoad::findStation(const vector<Station*>& stations, int id) {
	for (Station* tmp : stations) {
		if (tmp->getStationId() == id) return tmp;
	}
	throw NotFound("Station doesn't exist!");
}


int SystemLoad::extractStationId(const string& argument) {
	if (argument.find_first_of(' ') == string::npos) throw InvalidArgument("Invalid station input!");
	else return stringToInt(argument.substr(0, argument.find_first_of(' ')));
}

string SystemLoad::extractStationName(const string& argument) {
	try { 
		return argument.substr(argument.find_first_of(' ') + 1); 
	}
	catch (out_of_range error) {
		throw InvalidArgument("Invalid line input!");
	}
}


string SystemLoad::extractLineName(const string& argument) {
	if (argument.find_first_of(' ') == string::npos) throw InvalidArgument("Invalid line input!");
	else return argument.substr(0, argument.find_first_of(' '));
}

int SystemLoad::extractStation(const string& argument, int& pos) {
	string tmp = "";
	for (; pos < argument.size() && argument[pos] != ' ' && argument[pos] != '#'; pos++) {
		tmp += argument[pos];
	}
	return stringToInt(tmp);
}
