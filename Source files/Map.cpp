#include "Map.h"

Map::Map() : route_cnt_(0) {}

Map::~Map() {
	for (auto& tmp : map_) {
		for (Connection* connection : tmp.second) delete connection;
	}

	map_.clear();
}

void Map::updateMap(const vector<Line*>& lines, const vector<Station*>& stations) {
	if (lines.empty() || stations.empty()) throw InvalidUserInput("Lines weren't loaded!");

	// Go through all the lines in the system
	for (Line* line : lines) {

		// Going through the stations of the line
		vector <Station*> stations = line->getLineStations();
		for (int i = 0; i + 1 < stations.size(); i++) {

			if (stations[i] == stations[i + 1]) continue;

			// Forming connection (next station, line with which stations are connected)
			Connection* connection = new Connection(stations[i + 1], line);

			// The link is added to the current station in the map
			map_[stations[i]].push_back(connection);
		}
	}
}

void Map::findCommonLines(Line* line, map<Line*, int>& common_lines) const {
	vector <Station*> stations = line->getLineStations();

	// Go through all the stations where the line stops
	for (Station* station : stations) {

		// Add common station lines
		// If the line has already been added, the number of shared stations is incremented
		vector <Line*> lines = station->getStationLines();
		for (Line* tmp : lines) {
			if (tmp == line) continue;
			common_lines[tmp]++;	
		}
	}
}


const vector<Connection*>& Map::findRoute(Station* start, Station* end) {
	setDefault();				// The initial values of auxiliary data are established
	getRoutes(start, end);		// Finding routes

	// Throw an exception if no route is found
	if (routes_.empty()) throw NotFound("Stations aren't connected");

	// Return first found route
	return routes_[0];
}

const vector<Connection*>& Map::findFastRoute(Station* start, Station* end) {
	setDefault();				// The initial values of auxiliary data are established
	getRoutes(start, end);		// Finding routes

	// Throw an exception if no route is found
	if (routes_.empty()) throw NotFound("Stations aren't connected");	

	int min = -1;
	int fast_route = -1;

	// Go through all found routes
	for (auto& route : routes_) {

		// Broj stanica kroz koje se prolazi (broj veza)
		int distance = route.second.size();	

		// Number of stations passed through (number of connections)
		if (distance < min || min == -1) {
			min = distance;
			fast_route = route.first;
		}
	}

	return routes_[fast_route];
}

const vector<Connection*>& Map::findEasyRoute(Station* start, Station* end) {
	setDefault();				// The initial values of auxiliary data are established
	getRoutes(start, end);		// Finding routes

	// Throw an exception if no route is found
	if (routes_.empty()) throw NotFound("Stations aren't connected");

	int min = -1;
	int easy_route = -1;

	// Go through all found routes
	for (auto& route : routes_) {
		int cnt = 0;

		// Find the number of transitions
		for (int pos = 0; pos + 1 < route.second.size(); pos++) {
			if (route.second[pos]->getLine() != route.second[pos + 1]->getLine()) cnt++;
		}

		// Finding the route with the fewest transfers
		if (cnt < min || min == -1) {
			min = cnt;
			easy_route = route.first;
		}
	}
	
	return routes_[easy_route];
}


// Helper functions

void Map::setDefault() {
	route_cnt_ = 0;
	routes_.clear();
}

void Map::getRoutes(Station* start, Station* end) {
	vector <Station*> visited_stations;
	vector <Connection*> route;
	stack <Connection*> stack;

	Station* curr_station = start;
	for (Connection* connection : map_[curr_station]) stack.push(connection);

	while (!stack.empty()) {
		// Check for separator
		while (stack.top() == nullptr) {
			stack.pop();
			if (!route.empty()) route.pop_back();
			if (!visited_stations.empty()) visited_stations.pop_back();
			if (stack.empty()) break;
		}
		if (stack.empty()) break;

		// Take one connection form the stack
		curr_station = stack.top()->getStation();
		route.push_back(stack.top());
		stack.pop();
		
		// A route is formed if the last station has been reached
		if (curr_station == end) {
			routes_[route_cnt_] = route;
			route_cnt_++;
			if (!route.empty()) route.pop_back();
			continue;
		}

		// Check if the station is already visited
		bool visited = false;
		for (Station* visited_station : visited_stations) {
			if (curr_station == visited_station) {
				visited = true;
				break;
			}
		}
		if (visited) {
			if (!route.empty()) route.pop_back();
			continue;
		}
		// Add the current station to the list visited stations
		visited_stations.push_back(curr_station);

		// Add separator to the stack (separates the connections of different stations)
		stack.push(nullptr);
		// Go through all the connections of the station and add the connection to the stack
		for (Connection* connection : map_[curr_station]) stack.push(connection);
	}
}
