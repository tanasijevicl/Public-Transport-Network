#include "System.h"
#include <iostream>
#include <string>
using namespace std;

// Loading the necessary information for the operation of the system
void loadSystem(System* system) {
	string file = "";

	cout << endl << "Please enter stations file location: ";
	cin >> file;
	system->loadStations(file + ".txt");

	cout << endl << "Please enter lines file location: ";
	cin >> file;
	system->loadLines(file + ".txt");
}

// System initialization
void startSystem(System* system) {
	
	cout << endl << "--------------------------------------------" << endl;
	cout << endl << "Options:" << endl;
	cout << "1. Load public transpot information" << endl;
	cout << "0. Exit" << endl << endl;
	cout << "Please chose option (enter number): ";

	int option = 0;
	cin >> option;
	
	try {
		switch (option)
		{
		case 1:
			loadSystem(system);
			cout << endl << "Informations loaded successfully!" << endl;
			break;
		case 0:
			delete system;
			exit(0);
		default:
			cout << endl << "Option doesn't exist. Please chose again." << endl;
			startSystem(system);
		}
	}
	catch (InvalidUserInput error) {
		cout << endl << error.what() << endl;
		startSystem(system);
	}
	catch (SystemError error) {
		cout << endl << error.what() << endl;
		delete system;
		exit(0);
	}
}

// Choosing a route strategy
void choseStrategy(System* system) {
	int start_id = 0, end_id = 0;
	int option = 0;

	cout << endl << "Please enter start station id: ";
	cin >> start_id;
	cout << endl << "Please enter end station id: ";
	cin >> end_id;

	cout << endl << "Strategies:" << endl;
	cout << "1. Any route" << endl;
	cout << "2. The fastest route" << endl;
	cout << "3. Route with least number of transfers" << endl;
	cout << "0. Exit" << endl << endl;
	cout << "Please chose strategy (enter number): ";
	cin >> option;

	switch (option)
	{
	case 1:
		system->getRoute(start_id, end_id);
		break;
	case 2:
		system->getFastRoute(start_id, end_id);
		break;
	case 3:
		system->getEasyRoute(start_id, end_id);
		break;
	case 0:
		delete system;
		exit(0);
	default:
		cout << endl << "Option doesn't exist. Please chose again." << endl;
		choseStrategy(system);
	}
}

// The part of the system through which information is displayed
void infoSystem(System* system) {
	int option = 0;

	cout << endl << "--------------------------------------------" << endl;
	cout << endl << "Options:" << endl;
	cout << "1. Station informations" << endl;
	cout << "2. Line informations" << endl;
	cout << "3. Statistical line data" << endl;
	cout << "4. Directions" << endl;
	cout << "0. Exit" << endl << endl;
	cout << "Please chose option (enter number): ";
	cin >> option;

	int id = 0;
	string line_name = "";

	try {
		switch (option)
		{
		case 1:
			cout << endl << "Please enter station id: ";
			cin >> id;
			system->stationInfo(id);
			break;
		case 2:
			cout << endl << "Please enter line name: ";
			cin >> line_name;
			system->lineInfo(line_name);
			break;
		case 3:
			cout << endl << "Please enter line name: ";
			cin >> line_name;
			system->statisticalLineData(line_name);
			break;
		case 4:
			choseStrategy(system);
			break;
		case 0:
			delete system;
			exit(0);
		default:
			cout << endl << "Option doesn't exist." << endl;
		}
	}
	catch (InvalidUserInput error) {
		cout << endl << error.what() << endl;
	}
	catch (SystemError error) {
		cout << endl << error.what() << endl;
	}
	infoSystem(system);
}

int main() {
	
	System* system = new System();
	
	cout << "Welcome to public transport simulation!" << endl;
	 
	startSystem(system);
	
	infoSystem(system);

	delete system;

	return 0;
}
