#include "Alg_Prim.h"

#include <iostream>
#include <iomanip>

void Alg_Prim::Prim_list(Graph_list& graph, bool write)
{
    int vertices = graph.vertices;
    My_pair<int, int>*** adjacencyList = new My_pair<int, int>** [vertices];
    for (int i = 0; i < vertices; ++i) 
    {
        adjacencyList[i] = new My_pair<int, int>* [graph.edgeCounts[i]];
        for (int j = 0; j < graph.edgeCounts[i]; ++j) 
        {
            adjacencyList[i][j] = &graph.adjacencyList[i][j];
        }
    }

    int* predecessor = new int[vertices];
    int* key = new int[vertices];
    bool* inMST = new bool[vertices];

    for (int i = 0; i < vertices; ++i) 
    {
        predecessor[i] = -1;
        key[i] = INT_MAX;
        inMST[i] = false;
    }

    int u = 0;
    int v = 0;
    int weight = 0;

    key[0] = 0;

    for (int i = 0; i < vertices - 1; ++i) 
    {
        u = minKey(key, inMST, vertices);
        inMST[u] = true;

        for (int j = 0; j < graph.edgeCounts[u]; ++j) 
        {
            My_pair<int, int>* neighbor = adjacencyList[u][j];
            v = neighbor->first;
            weight = neighbor->second;

            if (!inMST[v] && weight < key[v]) 
            {
                predecessor[v] = u;
                key[v] = weight;
            }
        }
    }

    if (write == true)
    {
        cout << "Krawedz Waga" << endl;
        for (int i = 1; i < vertices; ++i)
        {
            if (predecessor[i] != -1)
            {
                cout << setw(3) << predecessor[i] << ":" << i << setw(5) << key[i] << endl;
            }
        }
    }

    for (int i = 0; i < vertices; ++i) 
    {
        delete[] adjacencyList[i];
    }
    delete[] adjacencyList;
    delete[] predecessor;
    delete[] key;
    delete[] inMST;   
}

void Alg_Prim::Prim_matrix(Graph_matrix& graph, bool write)
{
    int vertices = graph.vertices;
    int edges = graph.edges;

    int* predecessor = new int[vertices];
    int* key = new int[vertices];
    bool* inMST = new bool[vertices];

    for (int i = 0; i < vertices; ++i)
    {
        predecessor[i] = -1;
        key[i] = INT_MAX;
        inMST[i] = false;
    }

    key[0] = 0;

    for (int count = 0; count < vertices - 1; ++count)
    {
        int u = minKey(key, inMST, vertices);
        inMST[u] = true;

        for (int j = 0; j < edges; ++j)
        {
            if (graph.incidenceMatrix[u][j] == 1)
            {
                int v = -1;
                for (int i = 0; i < vertices; ++i)
                {
                    if (graph.incidenceMatrix[i][j] == 1 && i != u)
                    {
                        v = i;
                        break;
                    }
                }
                if (v != -1 && !inMST[v] && graph.weightsMatrix[j] < key[v])
                {
                    key[v] = graph.weightsMatrix[j];
                    predecessor[v] = u;
                }
            }
        }
    }
    if (write == true)
    {
        cout << "Krawedz Waga" << endl;
        for (int i = 1; i < vertices; ++i)
        {
            if (predecessor[i] != -1)
            {
                cout << setw(3) << predecessor[i] << ":" << i << setw(5) << key[i] << endl;
            }
        }
    }

    delete[] predecessor;
    delete[] key;
    delete[] inMST;
}

int Alg_Prim::minKey(int key[], bool inMST[], int vertices)
{
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < vertices; ++v)
    {
        if (!inMST[v] && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

