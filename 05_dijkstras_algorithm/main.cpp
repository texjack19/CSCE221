#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

#include "Graph.h"

int main(int argc, const char * argv[]) {
    cout << "Filename of graph to load: ";

    // TODO: next five code snippets
    // Snippet 1: read filename and open file
    fstream fs;
    string filename;
    cin >> filename;
    fs.open(filename);

    // Snippet 2: get number graph size
    int vertices, edges;
    fs >> vertices;
    fs >> edges;
    
    // Snippet 3: create graph
    Graph g;
    for (int i = 0; i < vertices; i++) {
        g.insertVertex(i);
    }

    // Snippet 4: read edges
    int l1, l2; 
    float weight;
    for (int i = 0; i < edges; i++) {
        fs >> l1;
        fs >> l2;
        fs >> weight;
        g.insertEdge(l1, l2, weight);
        g.insertEdge(l2, l1, weight);
    }

    // Snippet 5: read start and end of path
    int startVertex, endVertex;
    fs >> startVertex;
    fs >> endVertex;
    
    cout << "Shortest path from " << startVertex << " to " << endVertex << ":" << endl;

    vector<Vertex*> path;

    // TODO: call shortest path on your graph for the start and end verices and save result to path
    path = g.shortestPath(startVertex, endVertex);
    
    for (auto i : path) { // this is a for-each loop
        cout << i->label << " ";
    }
    // cout endline at very end
    cout << endl;
    return 0;
}
