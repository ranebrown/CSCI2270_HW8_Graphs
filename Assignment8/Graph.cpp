#include "Graph.h"
#include <vector>
#include <queue>
#include <algorithm>

Graph::Graph() {
	numCities = 0;
	district = 0;
}

Graph::~Graph() {
    //dtor
}

// Public
void Graph::AddEdge(std::string v1, std::string v2, int weight){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}

void Graph::AddVertex(std::string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            std::cout<<vertices[i].name<<" found."<<std::endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
		v.visited = false;
		v.districtID = -1;
        vertices.push_back(v);

    }
}

void Graph::DisplayEdges(){
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        std::cout<<vertices[i].districtID<<":"<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
			std::cout<<vertices[i].adj[j].v->name;
			if(j != vertices[i].adj.size()-1)
				std::cout<<"***";
        }
        std::cout<<std::endl;
    }

}

bool Graph::EdgeExists(std::string city1, std::string city2) {
	vertex *startingCity = nullptr;
	int i;
	
	// find city1
	for(i = 0; i<vertices.size(); i++) {
		if(vertices[i].name == city1){
			startingCity = &vertices[i];
			break;
		}
	}
	
	// if vertex of city1 not found return error message
	if(startingCity == nullptr) {
		std::cout<<"City1 not found -> vertex not created\n";
		return false;
	}
	else {
		// check if edge exists between city1 and city2
		for(i=0; i<startingCity->adj.size(); i++) {
			if(startingCity->adj[i].v->name == city2)
				return true;
		}
		return false; // if match not found
	}
}

void Graph::FindDistricts() {
	std::string city;
	
	while(!citiesVector.empty()) {
		district++; // increment the current district number (initially set to 0)
		city = citiesVector.front();
		citiesVector.erase(citiesVector.begin()); // remove front element
		BFTraversal(city);
	}
}

void Graph::FindShortestPath(std::string startCity, std::string endCity) {
	vertex *start = nullptr, *end = nullptr;
	int i;
	
	// find start vertex
	for(i=0; i<vertices.size(); i++)
		if(vertices[i].name == startCity) {
			start = &vertices[i];
			break;
		}
	// find end vertex
	for(i=0; i<vertices.size(); i++)
		if(vertices[i].name == endCity) {
			end = &vertices[i];
			break;
		}
	
	// check if cities were found
	if(start == nullptr || end == nullptr) {
		std::cout << "One or more cities doesn't exist" << std::endl;
		return;
	}
	
	// check if cities are in the same district
	if(start->districtID != end->districtID) {
		std::cout << "No safe path between cities" << std::endl;
		return;
	}
	
	// check if districts have been set
	if(start->districtID == -1 || end->districtID == -1) {
		std::cout << "Please identify the districts before checking distances" << std::endl;
		return;
	}
	
	else {
		BFS(start, end);
	}
}

void Graph::BFS(vertex *startV, vertex *endV) {
	int i;
	struct queueVertex{
		int distance;   //number of edges on path
		std::vector<vertex*> path;   //vertices on the path
	};
	queueVertex qv; // struct to hold distance and path
	std::queue<queueVertex> structQueue; // queue to hold elements of struct
	std::vector<vertex*> pathParent;
	int distance;
	
	// set all vertices to show not visited
	for(i = 0; i < vertices.size(); i++)
		vertices[i].visited = false;
	
	// save parameters for starting vertex
	startV->visited = true;
	
	// add initial info to struct
	qv.distance = 0;
	qv.path.push_back(startV);
	
	// add struct to queue
	structQueue.push(qv);
	
	while(!structQueue.empty()) {
		qv = structQueue.front();
		structQueue.pop();
		startV->adj.size();
		for(i=0; i<qv.path.back()->adj.size(); i++) {
			vertex *v = qv.path.back()->adj[i].v;
			if(v->visited == false) {
				pathParent = qv.path;
				v->visited = true;
				distance = qv.distance+1;
				pathParent.push_back(v);
				queueVertex temp;
				temp.path = pathParent;
				temp.distance = distance;
				if(v == endV) {
					std::cout<<temp.distance<<",";
					for(i=0; i<temp.path.size(); i++) {
						if(temp.path[i] == endV)
							std::cout<<temp.path[i]->name;
						else
							std::cout<<temp.path[i]->name<<",";
					}
					std::cout<<"\n";
				}
				else
					structQueue.push(temp);
			}
		}
	}
}

void Graph::FindShortestDistance(std::string startCity, std::string endCity) {
	vertex *start = nullptr, *end = nullptr;
	int i;
	
	// find start vertex
	for(i=0; i<vertices.size(); i++)
		if(vertices[i].name == startCity) {
			start = &vertices[i];
			break;
		}
	// find end vertex
	for(i=0; i<vertices.size(); i++)
		if(vertices[i].name == endCity) {
			end = &vertices[i];
			break;
		}
	
	// check if cities were found
	if(start == nullptr || end == nullptr) {
		std::cout << "One or more cities doesn't exist" << std::endl;
		return;
	}
	
	// check if cities are in the same district
	if(start->districtID != end->districtID) {
		std::cout << "No safe path between cities" << std::endl;
		return;
	}
	
	// check if districts have been set
	if(start->districtID == -1 || end->districtID == -1) {
		std::cout << "Please identify the districts before checking distances" << std::endl;
		return;
	}
	
	else {
		DijkstraShortestPath(start, end);
	}
}

// Private
void Graph::BFTraversal(std::string startingCity) {
	std::queue<vertex*> bfq;
	vertex *start;
	int i = 0;
	
	// set all vertices to show not visited
	for(i = 0; i < vertices.size(); i++)
		vertices[i].visited = false;
	
	// find the starting city
	for(i=0; i<vertices.size();i++) {
		if (startingCity==vertices[i].name) {
			start = &vertices[i];
			break;
		}
	}
	
	// update starting vertex parameters
	//std::cout<<start->name<<std::endl;
	start->visited = true;
	start->districtID = district; // update district
	bfq.push(start);
	
	// loop through connected vertices breadth first
	while (!bfq.empty()) {
		start = bfq.front();
		bfq.pop();
		for(i=0;i<start->adj.size();i++) {
			if (start->adj[i].v->visited==false) {
				start->adj[i].v->visited = true;
				bfq.push(start->adj[i].v);
				start->adj[i].v->districtID = district; // update district
				
				// remove cities from vector of all cities to avoid changing district number later
				for(int j=0; j<citiesVector.size(); j++) {
					if(start->adj[i].v->name == citiesVector[j])
						citiesVector.erase(citiesVector.begin()+j);
				}
				//std::cout<<start->adj[i].v->name<<std::endl;
			}
		}
	}
}

void Graph::DijkstraShortestPath(vertex *startV, vertex *endV) {
	int i; // index
	int minDistance = INT_MAX; // current min distance
	vertex *v_q = nullptr; // each vertex in solved queue
	vertex *min = nullptr; // vertex with minimum distance from previous
	vertex *current = nullptr; // adjacent
	std::vector<vertex*> solved; // queue to hold solved vertices
	
	// initialize vertice parameters
	for(i = 0; i < vertices.size(); i++) {
		vertices[i].visited = false;
		vertices[i].distance = INT_MAX; // maximum integer size in C++, could use infinity
		vertices[i].previous = nullptr;
	}
	
	// save info for starting vertex
	startV->visited = true;
	startV->distance = 0;
	
	// add start to vector
	solved.push_back(startV);
	
	// loop until the destination is reached
	while(endV->visited == false) {
		minDistance = INT_MAX; // initialize distance
		for(i=0; i<solved.size(); i++) {
			v_q = solved[i];
			
			// check adjacent vertices for minimum distance
			for(int j=0; j<v_q->adj.size(); j++) {
				current = v_q->adj[j].v;
				
				// visited means the vertex has been added to solved vector
				if(current->visited == false) {
					int tempDistance = v_q->adj[j].weight + v_q->distance;
					
					// find the minimum vertex and distance
					if(tempDistance < minDistance) {
						minDistance = tempDistance;
						min = current;
						min->previous = v_q;
					}
				}
			}
		}
		// save min vertex
		min->distance = minDistance;
		min->visited = true;
		solved.push_back(min);
		
	}
	
	// the solved vector contains all vertices with shortest path, not only desired path
	
	// Print results
	std::vector<vertex*> output;
	vertex *x = endV;
	while(x!= nullptr) {
		output.push_back(x);
		x=x->previous;
	}
	std::reverse(output.begin(), output.end());
	std::cout<<endV->distance<<",";
	for(i=0; i<output.size(); i++) {
		if(output[i] == endV)
			std::cout<<output[i]->name;
		else
			std::cout<<output[i]->name<<",";
	}
	std::cout<<std::endl;
}
