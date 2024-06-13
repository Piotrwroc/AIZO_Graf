#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include "Generate.h"
#include <string>
#include "Pair.h"

using namespace std;

class Graph_list 
{
public:
    int vertices;
    int edges;
    int* edgeCounts; // Tablica przechowuj¹ca liczbê krawêdzi dla ka¿dego wierzcho³ka
    My_pair<int, int>** adjacencyList; // Tablica tablic (lista s¹siedztwa)
    bool shouldDeleteData;

    Graph_list* next;
    Graph_list();
    ~Graph_list();

    void load_graph(string& filename, int mode);
    void save_graph();
    void display_graph();
    void populateFromGraph(Graph& graph);
    bool isGraphValid();
    
};

#endif GRAPH_LIST_H
