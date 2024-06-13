#include "alg_Ford_Bellman.h"

#include <iostream>
#include <iomanip>

void alg_Ford_Bellman::Ford_Bellman_list(Graph_list& graph, int start, int end, bool write)
{
    int vertices = graph.vertices;
    int edges = graph.edges;
    int* edgeCounts = graph.edgeCounts;
    My_pair<int, int>** adjacencyList = graph.adjacencyList;

    int* distance = new int[vertices]; // minimalne koszty dojœcia
    int* predecessors = new int[vertices]; // numery wierzcho³ków-poprzedników

    // inicjalizacja pocz¹tkowa
    for (int i = 0; i < vertices; i++)
    {
        distance[i] = INT_MAX; // odpowiednik nieskoñczonoœci
        predecessors[i] = -1;      // nieznany poprzednik
    }
    distance[start] = 0;

    // relaksacja krawêdzi
    bool isChanged;
    for (int i = 1; i < vertices; i++)
    {
        isChanged = false;
        for (int u = 0; u < vertices; u++)
        {
            for (int j = 0; j < edgeCounts[u]; j++)
            {
                int v = adjacencyList[u][j].first;
                int weight = adjacencyList[u][j].second;

                if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
                {
                    isChanged = true;
                    distance[v] = distance[u] + weight;
                    predecessors[v] = u;
                }
            }
        }
        if (!isChanged)
            break;
    }

    if (write == true)
    {
        cout << "Koszt najkrotszej sciezki z wierzcholka " << start << " do wierzcholka " << end << " wynosi: " << distance[end] << endl;
        cout << "Znaleziona sciezka: ";
        int currentVertex = end;
        while (currentVertex != -1)
        {
            cout << currentVertex;
            currentVertex = predecessors[currentVertex];
            if (currentVertex != -1)
                cout << " -> ";
        }
        cout << endl;
    }

    delete[] distance;
    delete[] predecessors;
}

void alg_Ford_Bellman::Ford_Bellman_matrix(Graph_matrix& graph, int start, int end, bool write)
{
    int vertices = graph.vertices;
    int edges = graph.edges;
    int** incidenceMatrix = graph.incidenceMatrix;
    int* weightsMatrix = graph.weightsMatrix;

    int* distance = new int[vertices]; // minimalne koszty dojœcia
    int* predecessors = new int[vertices]; // numery wierzcho³ków-poprzedników

    // inicjalizacja pocz¹tkowa
    for (int i = 0; i < vertices; i++) 
    {
        distance[i] = INT_MAX; // odpowiednik nieskoñczonoœci
        predecessors[i] = -1;      // nieznany poprzednik
    }
    distance[start] = 0;

    // relaksacja krawêdzi
    bool isChanged;
    for (int i = 1; i < vertices; i++) 
    {
        isChanged = false;
        for (int j = 0; j < edges; j++) 
        { // przejœcie po wszystkich krawêdziach

            int u = -1, v = -1, weight = -1;
            // znalezienie wierzcho³ków u i v oraz ich wagi
            for (int k = 0; k < vertices; k++) 
            {
                if (incidenceMatrix[k][j] == 1)
                    u = k;
                else if (incidenceMatrix[k][j] == -1)
                    v = k;
            }
            weight = weightsMatrix[j];

            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) 
            {
                isChanged = true;
                distance[v] = distance[u] + weight;
                predecessors[v] = u;
            }
        }
        if (!isChanged)
            break;
    }
    if (write == true)
    {
        cout << "Koszt najkrotszej sciezki z wierzcholka " << start << " do wierzcholka " << end << " wynosi: " << distance[end] << endl;
        cout << "Znaleziona sciezka: ";
        int currentVertex = end;
        while (currentVertex != -1)
        {
            cout << currentVertex;
            currentVertex = predecessors[currentVertex];
            if (currentVertex != -1)
                cout << " -> ";
        }
        cout << endl;
    }

    delete[] distance;
    delete[] predecessors;
}

