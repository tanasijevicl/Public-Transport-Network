# Public Transport Network Simulation

## Overview

This project implements a simulation for a city's public transportation network using C++. The system models a network of bus stops and lines, allowing various operations to retrieve and display information about the network, including bus stops, lines, and statistics. The simulator also provides functionality to calculate routes between bus stops using different strategies and includes an interactive user interface.

## Features

- **Loading Network Data**: Import bus stop and line data from text files.
- **Display Information**:
  - Bus stop details, including lines passing through the stop.
  - Line details, including start and end stops and all stops in both directions.
  - Statistical information about lines, including common stops and the line with the most common stops.
- **Finding routes**: Compute routes between two bus stops using different strategies:
  - Any route.
  - Route with the fewest stops.
  - Route with the fewest transfers.
- **Interactive User Interface**: A menu-driven system for interacting with the simulator.

## Project Files

- **`UserInteraction.cpp`**: The part of the code responsible for interacting with the user
- **`System.cpp`** & **`System.h`**: System class for managing and processing data related to stations and lines
- **`SystemLoad.cpp`** & **`SystemLoad.h`**: SystemLoad class responsible for loading station and line data, including parsing and validating input strings to create Station and Line objects
- **`Map.cpp`** & **`Map.h`**: Map class for managing station connections, updating routes, and finding routes based on different criteria
- **`Connection.cpp`** & **`Connection.h`**: Connection class representing a link between two stations via a specific line
- **`Station.cpp`** & **`Station.h`**: Station class representing a station with an ID and name, which provides methods to access the station's lines and manage the lines that stop at the station
- **`Line.cpp`** & **`Line.h`**: Line class representing a bus line with a name and the stations it passes through, including methods to access the start and end stations, and manage the line's stations.
- **`Exceptions.cpp`**: This part of the code defines exception classes for error handling.

## Data Files

- **`stations.txt`**: Input file containing bus stop information in the format `station_id station_name`.
- **`lines.txt`**: Input file containing line information in the format `line_id stations_direction_A#stations_direction_B`.
- **`line_<line_id>.txt`**: Output file with basic information about a specific line.
- **`station_<station_id>.txt`**: Output file with information about a specific bus stop.
- **`statistics_<line_id>.txt`**: Output file with statistical information about a specific line.
- **`path_<start_station_id>_<end_station_id>.txt`**: Output file with the computed path between two bus stops.

## Usage

1. **Compile the Project**: Use your preferred C++ compiler to build the project.
2. **Run the Simulator**: Execute the compiled program. Follow the on-screen menu to load data and perform operations.

## Dependencies

- **C++ Compiler**: Visual Studio 2019 (or newer) is recommended for building this project.