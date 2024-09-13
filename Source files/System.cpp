#include "System.h"

System::System() {
	// Create instances of helper classes
	loader_ = new SystemLoad();
	map_ = new Map();
}

System::~System() {
	// Delete all stations from the system
	for (Station* station : stations_) delete station;
	stations_.clear();

	// Delete all lines from the system
	for (Line* line : lines_) delete line;
	lines_.clear();

	// Delete instances of helper classes
	delete loader_;
	delete map_;
}


void System::loadStations(const string& stations) {
	fstream input_file(stations, ios::in);
	if (input_file.is_open()) {
		string argument = "";

		// One station at a time (line of text) is read from the file
		while (getline(input_file, argument)) {
			try {
				Station* station = loader_->loadStation(argument);		// Loading station
				checkStation(station);									// Checking if the station already exists
				stations_.push_back(station);							// Adding a station to the system
			}
			catch (InvalidArgument error) {
				cout << endl << error.what() << " (Invalid file line: " << argument << ')' << endl;
			}
			catch (StationAlreadyExist error) {
				delete error.getStation();
				cout << endl << error.what() << " (Invalid file line: " << argument << ')' << endl;
			}
		}
		input_file.close();

		if (stations_.empty()) throw InvalidUserInput("No stations loaded!");
	}
	else throw InvalidUserInput("File not found!");
}

void System::loadLines(const string& lines) {
	fstream input_file(lines, ios::in);
	if (input_file.is_open()) {
		string argument = "";

		// One line at a time (line of text) is read from the file
		while (getline(input_file, argument)) {
			try {
				Line* line = loader_->loadLine(argument, stations_);	// Loading line
				checkLine(line);										// Checking if the line already exists
				lines_.push_back(line);									// Adding a line to the system
			}
			catch (InvalidArgument error) {
				cout << endl << error.what() << " (Invalid file line: " << argument << ')' << endl;
			}
			catch (LineAlreadyExist error) {
				delete error.getLine();
				cout << endl << error.what() << " (Invalid file line: " << argument << ')' << endl;
			}
		}
		input_file.close();
		if (lines_.empty()) throw InvalidUserInput("No lines loaded!");
		
		// Creating a map based on the loaded stations and lines
		map_->updateMap(lines_, stations_);
	}
	else throw InvalidUserInput("File not found!");
}


void System::stationInfo(int id) const {
	try {
		// Find a station in the system
		Station* station = findStation(id);
		string info = to_string(id) + ' ' + station->getStationName() + " [";
		
		// The station lines are fetched and sorted
		vector <Line*> lines = station->getStationLines();
		vector <string> lines_names;

		for (Line* line : lines) {
			lines_names.push_back(line->getLineName());
		}
		
		sort(lines_names.begin(), lines_names.end());

		for (string line_name : lines_names) {
			info += line_name + ' ';
		}

		info.pop_back();
		info += ']';

		printOutput("station_" + to_string(id) + ".txt", info);
	}
	catch (NotFound error) {
		throw InvalidUserInput(error.what());
	}
}

void System::lineInfo(const string& line_name) const {
	try {
		// Find a line in the system
		Line* line = findLine(line_name);
		string info = line_name + ' ' + line->getLineStart()->getStationName()
					+ "->" + line->getLineEnd()->getStationName() + '\n';

		// The data of all stations of the line are printed in order
		vector <Station*> stations = line->getLineStations();
		for (Station* station : stations) {
			info += to_string(station->getStationId()) + ' ' + station->getStationName() + '\n';
		}
		info.pop_back();
		
		printOutput("line_" + line_name + ".txt", info);
	}
	catch (NotFound error) {
		throw InvalidUserInput(error.what());
	}
}

void System::statisticalLineData(const string& line_name) const {
	try {
		// Find a line in the system
		Line* line = findLine(line_name);
		string info = line_name + '\n';

		map <Line*, int> common_lines;
		vector <string> most_common;
		vector <string>	lines_names;
		int max = 0;

		// The map records data about lines with common stations
		map_->findCommonLines(line, common_lines);
		
		// Data processing
		for (auto& tmp : common_lines) {
			lines_names.push_back(tmp.first->getLineName());

			// Finding the line with the most common stops
			if (tmp.second > max) {
				most_common.clear();
				most_common.push_back(tmp.first->getLineName());
				max = tmp.second;
			}
			else if (tmp.second == max) {
				most_common.push_back(tmp.first->getLineName());
			}
		}

		sort(lines_names.begin(), lines_names.end());
		sort(most_common.begin(), most_common.end());

		// Print lines with common stops
		for (string line : lines_names) {
			info += line + ' ';
		}

		info.pop_back();
		info += '\n';

		// Print lines with the most common stops
		for (string line : most_common) {
			info += line + ", ";
		}

		info.pop_back();
		info.pop_back();
		
		printOutput("statistics_" + line_name + ".txt", info);
	}
	catch (NotFound error) {
		throw InvalidUserInput(error.what());
	}
}


void System::getRoute(int start_id, int end_id) const {
	try {
		Station* start = findStation(start_id);
		Station* end = findStation(end_id);

		vector <Connection*> route = map_->findRoute(start, end);	// A route is found through the map (array of links)
		string info = getInfo(start, route);						// Route processing

		printOutput("path_" + to_string(start_id) + '_' + to_string(end_id) + ".txt", info);
	}
	catch (NotFound error) {
		throw InvalidUserInput(error.what());
	}
	catch (NotUpdated error) {
		throw SystemError(error.what());
	}
}

void System::getFastRoute(int start_id, int end_id) const {
	try {
		Station* start = findStation(start_id);
		Station* end = findStation(end_id);

		// The route is found via the map and then the it is processed
		vector <Connection*> route = map_->findFastRoute(start, end);
		string info = getInfo(start, route);							

		printOutput("path_" + to_string(start_id) + '_' + to_string(end_id) + ".txt", info);
	}
	catch (NotFound error) {
		throw InvalidUserInput(error.what());
	}
	catch (NotUpdated error) {
		throw SystemError(error.what());
	}
}

void System::getEasyRoute(int start_id, int end_id) const {
	try {
		Station* start = findStation(start_id);
		Station* end = findStation(end_id);

		vector <Connection*> route = map_->findEasyRoute(start, end);	// A route is found through the map (array of links)
		string info = getInfo(start, route);							// Route processing

		printOutput("path_" + to_string(start_id) + '_' + to_string(end_id) + ".txt", info);
	}
	catch (NotFound error) {
		throw InvalidUserInput(error.what());
	}
	catch (NotUpdated error) {
		throw SystemError(error.what());
	}
}


// Helper functions

Station* System::findStation(int id) const {
	for (Station* station : stations_) {
		if (station->getStationId() == id) return station;
	}
	throw NotFound("Station doesn't exist");
}

Line* System::findLine(const string& name) const {
	for (Line* line : lines_) {
		if (line->getLineName() == name) return line;
	}
	throw NotFound("Line doesn't exist");
}

void System::checkStation(Station* station) const {
	for (Station* tmp : stations_) {
		if (tmp->getStationId() == station->getStationId())
			throw StationAlreadyExist(station, "Station with same id already added!");
	}
}

void System::checkLine(Line* line) const {
	for (Line* tmp : lines_) {
		if (tmp->getLineName() == line->getLineName())
			throw LineAlreadyExist(line, "Line with same name already added!");
	}
}


string System::getInfo(Station* start, const vector <Connection*>& route) const {
	string info = "";
	Line* curr_line = nullptr;			// Current line
	Station* curr_station = start;		// Current station

	// Go through the route links and print the information in the given format
	for (Connection* connection : route) {
		if (connection->getLine() == nullptr) {
			curr_station = connection->getStation();
			continue;
		}
		if (connection->getLine() == curr_line) {
			info += to_string(connection->getStation()->getStationId()) + ' ';
		}
		else if (curr_line == nullptr) {
			info += "->" + connection->getLine()->getLineName() + '\n';
			info += to_string(curr_station->getStationId()) + ' ' + to_string(connection->getStation()->getStationId()) + ' ';
		}
		else {
			info.pop_back();
			info += '\n' + curr_line->getLineName() + "->" + connection->getLine()->getLineName() + '\n';
			info += to_string(curr_station->getStationId()) + ' ' + to_string(connection->getStation()->getStationId()) + ' ';
		}

		curr_line = connection->getLine();
		curr_station = connection->getStation();
	}
	return info;
}

void System::printOutput(const string& file_name, const string& output) const {
	
	// Open the file and print a given information
	fstream output_file(file_name, ios::out);
	
	if (output_file.is_open()) {
		output_file << output;
		output_file.close();
	}
	else throw SystemError("Error opening output file!");

	cout << endl << "Output file created successfully." << endl;
}
