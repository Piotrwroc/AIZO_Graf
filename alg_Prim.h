#ifndef ALG_PRIM
#define ALG_PRIM

#include "Graph_matrix.h"
#include "Graph_list.h"

class Alg_Prim
{
public:
    void Prim_matrix(Graph_matrix& graph, bool write);
    void Prim_list(Graph_list& graph, bool write);
private:
    int minKey(int key[], bool inMST[], int vertices);
};

#endif ALG_PRIM


