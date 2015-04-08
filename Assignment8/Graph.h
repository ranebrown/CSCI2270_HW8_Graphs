#ifndef GRAPH_H
#define GRAPH_H

#include<vector>
#include<iostream>
#include <climits>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
	std::string name;
	bool visited;
	int distance;
	vertex *previous;
	std::vector<adjVertex> adj;
	int districtID;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void AddEdge(std::string v1, std::string v2, int weight);
		bool EdgeExists(std::string city1, std::string city2);
        void AddVertex(std::string name);
        void DisplayEdges();
		void FindDistricts();
		void FindShortestPath(std::string startCity, std::string endCity);
		void FindShortestDistance(std::string startCity, std::string endCity);
		std::vector<std::string> citiesVector; // vector of all city names
		int numCities; // count of the total number of cities             
    protected:
    private:
		void BFS(vertex *startV, vertex *endV);
		void BFTraversal(std::string city);
		void DijkstraShortestPath(vertex *startV, vertex *endV);
        std::vector<vertex> vertices;
		int	district;

};

#endif // GRAPH_H
