
#ifndef ALG_FORD_BELLMAN
#define ALG_FORD_BELLMAN

#include "Graph_matrix.h"
#include "Graph_list.h"

class alg_Ford_Bellman
{
public:
    void Ford_Bellman_matrix(Graph_matrix& graph, int start, int end, bool write);
    void Ford_Bellman_list(Graph_list& graph, int start, int end, bool write);
};

#endif ALG_FORD_BELLMAN


