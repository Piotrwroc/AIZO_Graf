#ifndef ALG_DIJKSTRA
#define ALG_DIJKSTRA

#include "Graph_matrix.h"
#include "Graph_list.h"

class Alg_Dijkstra
{
public:
    void Dijkstra_matrix(Graph_matrix& graph, int start, int end, bool write);
    void Dijkstra_list(Graph_list& graph, int start, int end, bool write);
private:
    void swap(int& a, int& b);
    void heapify(int* pq, int* dist, int n, int i);
    int extractMin(int* pq, int* dist, int& size);
    void decreaseKey(int* pq, int* dist, int size, int vertex, int newDist);

    void swap(My_pair<int, int>& a, My_pair<int, int>& b);
    void heapify(My_pair<int, int>* pq, int* dist, int n, int i);
    My_pair<int, int> extractMin(My_pair<int, int>* pq, int* dist, int& size);
    void decreaseKey(My_pair<int, int>* pq, int* dist, int size, int vertex, int newDist);


};

#endif ALG_DIJKSTRA


