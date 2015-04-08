/*
 *  Assignment8.cpp
 *  Assignment8
 *
 *  Created by Rane on 4/7/15.
 *	Graph.h file and Graph.cpp modified from CSCI provided file
*/

#include "Graph.h"
#include <fstream>
#include <sstream>

void DisplayMenu() {
	std::cout << "======Main Menu=====" << std::endl;
	std::cout << "1. Print vertices" << std::endl;
	std::cout << "2. Find districts" << std::endl;
	std::cout << "3. Find shortest path" << std::endl;
	std::cout << "4. Find shortest distance" << std::endl;
	std::cout << "5. Extra credit" << std::endl;
	std::cout << "6. Quit" << std::endl;
}

void BuildGraph(Graph *zCitiesGraph, const char *file) {
	std::string city;
	std::vector<std::string> lineVector;
	std::string edgeString;
	int edgeInt;
	
	// open text file to read in data
	std::ifstream txtFile(file);
	if (!txtFile.is_open())
		std::cout << "Could not open file\n";
	
	// read in each line and count the total number of cities
	while(getline(txtFile, city)) {
		lineVector.push_back(city);
		zCitiesGraph->numCities++;
	}
	zCitiesGraph->numCities--; // subtract 1 to count for first line that is list of all cities
	
	// create graph
	for(int i=0;i<zCitiesGraph->numCities;i++) {
		if(i == 0) { // first time through add each vertex
			std::istringstream ss(lineVector[i]);
			while(getline(ss, city, ',')) {
				if(city == "cities"); // don't create a vertex for cities identifier
				else {
					zCitiesGraph->citiesVector.push_back(city); // store each city in a vector
					zCitiesGraph->AddVertex(city); // add each city as a vertex in graph
				}
			}
		}
		else { // create edges between cities
			int j=0; // index to track which city the edge is being added to
			std::string city2;
			bool edgeExists;
			std::istringstream ss(lineVector[i]);
			getline(ss, city, ','); // get the city for current edge
			// edge is created between this city and each other city
			while(getline(ss, edgeString, ',')) {
				edgeInt = atoi(edgeString.c_str()); // convert edge cost to an integer
				city2 = zCitiesGraph->citiesVector[j]; // extract the terminating city from the vector
				j++; // increment index
				edgeExists = zCitiesGraph->EdgeExists(city, city2);
				if(edgeInt != 0 && edgeInt != -1 && !edgeExists) {
					zCitiesGraph->AddEdge(city, city2, edgeInt); // add edge to graph
					//std::cout<<city<<"--"<<city2<<": "<<edgeInt<<std::endl;
				}
			}
		}
	}
}

int main(int argc, const char * argv[]) {
	Graph *zCitiesGraph = new Graph;; // allocate memory for graph
	int selection = 0;
	bool quit = false;
	std::string start, end;
	
	// Create graph, filename is command line arg.
	BuildGraph(zCitiesGraph, argv[1]);
	
	// get user input for menu selection
	while(!quit) {
		DisplayMenu();
		std::cin>>selection;
		std::cin.clear();
		std::cin.ignore(1000,'\n');
		switch (selection) {
			case 1: // print vertices
				zCitiesGraph->DisplayEdges();
				break;
			case 2: // find districts
				zCitiesGraph->FindDistricts();
				break;
			case 3: // find shortest path
				std::cout << "Enter a starting city:" << std::endl;
				getline(std::cin, start);
				std::cout << "Enter an ending city:" << std::endl;
				getline(std::cin, end);
				zCitiesGraph->FindShortestPath(start, end);
				break;
			case 4: // find shortest distance
				std::cout << "Enter a starting city:" << std::endl;
				getline(std::cin, start);
				std::cout << "Enter an ending city:" << std::endl;
				getline(std::cin, end);
				zCitiesGraph->FindShortestDistance(start, end);
				break;
			case 5: // extra credit
				std::cout << "Enter a starting city:" << std::endl;
				getline(std::cin, start);
				break;
			case 6: // quit
				std::cout << "Goodbye!" << std::endl;
				quit = true;
				break;
			default:
				std::cout<<"Invalid input\n";
				std::cin.clear();
				std::cin.ignore(1000,'\n');
				break;
		}
	}
    return 0;
}
