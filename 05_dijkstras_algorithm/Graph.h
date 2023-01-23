#ifndef GRAPH_H
#define GRAPH_H

#include "LocatorHeap.h"
#include <float.h>

#include <vector>
#include <climits>
using std::vector;


class Edge;

class Vertex
{
public:
    int label;
    vector<Edge*> edges;

    // helpers stored inside a vertex to help with path finding
    // you can use different auxilliary structures if desired
    bool visited;
    float distanceTo;
    vector<Vertex*> pathTo;
    Heap<Vertex*>::Locator locator;
    bool operator < ( const Vertex &v ) const 
    { 
        // TODO for locator heap implementation
        return distanceTo < v.distanceTo;
    }

    Vertex ( int l ) : label (l) { }
};

class Edge
{
public:
    Vertex *v1, *v2;
    float weight;

    Edge ( Vertex *nv1, Vertex *nv2, float newWeight ) : v1 ( nv1 ), v2 ( nv2 ), weight ( newWeight ) { }
};


class Graph
{
protected:
    // TODO: store the vertices and edges in the graph
    vector<Vertex*> vertices;
    vector<Edge*> graphEdges;

public:
    Graph () {}

    ~Graph ()
    {
        // TODO
        for(int i = 0; i < vertices.size(); i++) {
            delete vertices[i];
        }
        for(int i = 0; i < graphEdges.size(); i++) {
            delete graphEdges[i];
        }
        vertices.clear();
        graphEdges.clear();
    }

    // TODO: complete rule of 3
    Graph ( const Graph &g ) {
        for (int i = 0; i < g.vertices.size(); i++) {
            insertVertex(g.vertices.at(i)->label);
        }
        for (int i = 0; i < g.graphEdges.size(); i++) {
            insertEdge(g.graphEdges.at(i)->v1->label, g.graphEdges.at(i)->v2->label, g.graphEdges.at(i)->weight);
        }
    }

    Graph& operator=( const Graph &g ) {
        for(int i = 0; i < vertices.size(); i++) {
            delete vertices[i];
        }
        for(int i = 0; i < graphEdges.size(); i++) {
            delete graphEdges[i];
        }
        vertices.clear();
        graphEdges.clear();
        for (int i = 0; i < g.vertices.size(); i++) {
            insertVertex(g.vertices.at(i)->label);
        }
        for (int i = 0; i < g.graphEdges.size(); i++) {
            insertEdge(g.graphEdges.at(i)->v1->label, g.graphEdges.at(i)->v2->label, g.graphEdges.at(i)->weight);
        }
        return *this;
    }

    void insertVertex ( int label )
    {
        // TODO
        Vertex* newVertex = new Vertex(label);
        vertices.push_back(newVertex);
    }

    void insertEdge ( int l1, int l2, float weight )
    {
        // TODO
        Edge* newEdge = new Edge(vertices.at(l1), vertices.at(l2), weight);
        graphEdges.push_back(newEdge);
        vertices.at(l1)->edges.push_back(newEdge);
    }

    vector<Vertex*> shortestPath ( int start, int end )
    {
        // TODO: Dijkstra's algorithm

        for (auto i = vertices.begin(); i != vertices.end(); i++) {
            // set all visited to false, clear pathTo, reset distanceTo to infinite
            (*i)->visited = false;
            (*i)->pathTo.clear();
            (*i)->distanceTo = FLT_MAX;
        }

        Vertex* curr = vertices[start];
        curr->distanceTo = 0;
        curr->pathTo.push_back(curr);
        Heap<Vertex*> locatorHeap;
        // curr->locator = locatorHeap.insertElement(curr);

        for (int i = 0; i < vertices.size(); i++) {
            vertices.at(i)->locator = locatorHeap.insertElement(vertices.at(i));
        }

        while (vertices.at(end)->visited == false) {
            curr = locatorHeap.removeMin();
            for (int i = 0; i < curr->edges.size(); i++) {
                // opposite = curr->edges[i]->v2;
                if (curr->edges[i]->v2->distanceTo > curr->distanceTo + curr->edges[i]->weight) {
                    curr->edges[i]->v2->distanceTo = curr->distanceTo + curr->edges[i]->weight;
                    curr->edges[i]->v2->pathTo = curr->pathTo;
                    curr->edges[i]->v2->pathTo.push_back(curr->edges[i]->v2);
                    locatorHeap.update(curr->edges[i]->v2->locator);
                }
            }
            curr->visited = true;
        }
        return curr->pathTo;
    }
};

#endif
