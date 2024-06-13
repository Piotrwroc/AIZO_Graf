#ifndef ALG_KRUSKAL
#define ALG_KRUSKAL

#include "Graph_matrix.h"
#include "Graph_list.h"

struct Krawedz
{
    int pocz, kon, waga;
};

struct Podzbior
{
    int poprzednik, rank;
};

class Alg_Kruskal
{
public:
    void Kruskal_matrix(Graph_matrix& graph, bool write);
    void Kruskal_list(Graph_list& graph, bool write);
private:
    int znajdz(Podzbior podzbiory[], int i);
    void zlacz(Podzbior subsets[], int x, int y);
};

#endif ALG_KRUSKAL


