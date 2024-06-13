#include "alg_Dijkstra.h"

#include <iostream>
#include <iomanip>

void Alg_Dijkstra::Dijkstra_list(Graph_list& graph, int start, int end, bool write) 
{
    int vertices = graph.vertices;

    My_pair<int, int>* pq = new My_pair<int, int>[vertices];
    int* dist = new int[vertices];
    int* predecessors = new int[vertices];
    int size = vertices;

    for (int i = 0; i < vertices; ++i) 
    {
        dist[i] = INT_MAX;
        pq[i] = my_make_pair(INT_MAX, i);
        predecessors[i] = -1; // Initialize predecessors
    }

    dist[start] = 0;
    pq[start] = my_make_pair(0, start);
    heapify(pq, dist, size, 0);

    while (size > 0) 
    {
        My_pair<int, int> minPair = extractMin(pq, dist, size);
        int u = minPair.second;

        for (int i = 0; i < graph.edgeCounts[u]; ++i) 
        {
            My_pair<int, int> neighbor = graph.adjacencyList[u][i];
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) 
            {
                dist[v] = dist[u] + weight;
                predecessors[v] = u; // Set predecessor
                decreaseKey(pq, dist, size, v, dist[v]);
            }
        }
    }

    if (write == true)
    {
        cout << "Koszt najkrotszej sciezki z wierzcholka " << start << " do wierzcholka " << end << " wynosi: " << dist[end] << endl;
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


    delete[] pq;
    delete[] dist;
    delete[] predecessors;
}

void Alg_Dijkstra::swap(My_pair<int, int>& a, My_pair<int, int>& b) 
{
    My_pair<int, int> temp = a;
    a = b;
    b = temp;
}

void Alg_Dijkstra::heapify(My_pair<int, int>* pq, int* dist, int n, int i) 
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && dist[pq[left].second] < dist[pq[smallest].second]) 
    {
        smallest = left;
    }

    if (right < n && dist[pq[right].second] < dist[pq[smallest].second]) 
    {
        smallest = right;
    }

    if (smallest != i) {
        swap(pq[i], pq[smallest]);
        heapify(pq, dist, n, smallest);
    }
}

My_pair<int, int> Alg_Dijkstra::extractMin(My_pair<int, int>* pq, int* dist, int& size) 
{
    if (size <= 0) 
    {
        return my_make_pair(INT_MAX, -1);
    }

    if (size == 1) {
        size--;
        return pq[0];
    }

    My_pair<int, int> root = pq[0];
    pq[0] = pq[size - 1];
    size--;
    heapify(pq, dist, size, 0);

    return root;
}

void Alg_Dijkstra::decreaseKey(My_pair<int, int>* pq, int* dist, int size, int vertex, int newDist) 
{
    int i;
    for (i = 0; i < size; ++i) 
    {
        if (pq[i].second == vertex) 
        {
            pq[i].first = newDist;
            break;
        }
    }

    while (i != 0 && dist[pq[i].second] < dist[pq[(i - 1) / 2].second]) 
    {
        swap(pq[i], pq[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void Alg_Dijkstra::Dijkstra_matrix(Graph_matrix& graph, int start, int end, bool write) {
    int vertices = graph.vertices;

    int* pq = new int[vertices];
    int* dist = new int[vertices];
    int* predecessors = new int[vertices];
    int size = vertices;

    for (int i = 0; i < vertices; ++i) 
    {
        dist[i] = INT_MAX;
        pq[i] = i;
        predecessors[i] = -1; // Initialize predecessors
    }

    dist[start] = 0;
    heapify(pq, dist, size, 0);

    while (size > 0) 
    {
        int u = extractMin(pq, dist, size);

        for (int i = 0; i < graph.edges; ++i) 
        {
            if (graph.incidenceMatrix[u][i] == 1) 
            {
                for (int v = 0; v < vertices; ++v) 
                {
                    if (v != u && graph.incidenceMatrix[v][i] == -1) 
                    {
                        int weight = graph.weightsMatrix[i];

                        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                            dist[v] = dist[u] + weight;
                            predecessors[v] = u; // Set predecessor
                            decreaseKey(pq, dist, size, v, dist[v]);
                        }
                    }
                }
            }
        }
    }

    if (write == true)
    {
        cout << "Koszt najkrotszej sciezki z wierzcholka " << start << " do wierzcholka " << end << " wynosi: " << dist[end] << endl;
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


    delete[] pq;
    delete[] dist;
    delete[] predecessors;
}

void Alg_Dijkstra::swap(int& a, int& b) 
{
    int temp = a;
    a = b;
    b = temp;
}

void Alg_Dijkstra::heapify(int* pq, int* dist, int n, int i) 
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && dist[pq[left]] < dist[pq[smallest]]) 
    {
        smallest = left;
    }

    if (right < n && dist[pq[right]] < dist[pq[smallest]])
    {
        smallest = right;
    }

    if (smallest != i) 
    {
        swap(pq[i], pq[smallest]);
        heapify(pq, dist, n, smallest);
    }
}

int Alg_Dijkstra::extractMin(int* pq, int* dist, int& size) 
{
    if (size <= 0) 
    {
        return -1;
    }

    if (size == 1) 
    {
        size--;
        return pq[0];
    }

    int root = pq[0];
    pq[0] = pq[size - 1];
    size--;
    heapify(pq, dist, size, 0);

    return root;
}

void Alg_Dijkstra::decreaseKey(int* pq, int* dist, int size, int vertex, int newDist) 
{
    int i;
    for (i = 0; i < size; ++i) 
    {
        if (pq[i] == vertex) 
        {
            dist[vertex] = newDist;
            break;
        }
    }

    while (i != 0 && dist[pq[i]] < dist[pq[(i - 1) / 2]]) 
    {
        swap(pq[i], pq[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
