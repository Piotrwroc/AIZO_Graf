#include "alg_Kruskal.h"

#include <algorithm> 
#include <iostream>
#include <iomanip>

void Alg_Kruskal::Kruskal_list(Graph_list& graph, bool write)
{
    int totalEdges = 0;
    for (int i = 0; i < graph.vertices; ++i)
    {
        totalEdges += graph.edgeCounts[i];
    }
    Krawedz* krawedzie = new Krawedz[totalEdges];
    int krawedzieIndex = 0;

    for (int u = 0; u < graph.vertices; ++u)
    {
        for (int j = 0; j < graph.edgeCounts[u]; ++j)
        {
            auto pCrawl = graph.adjacencyList[u][j];
            if (u < pCrawl.first) 
            {
                krawedzie[krawedzieIndex++] = { u, pCrawl.first, pCrawl.second };
            }
        }
    }

    sort(krawedzie, krawedzie + krawedzieIndex, [](Krawedz a, Krawedz b) {
        return a.waga < b.waga;
        });

    Podzbior* podzbiory = new Podzbior[graph.vertices];
    for (int v = 0; v < graph.vertices; ++v) 
    {
        podzbiory[v].poprzednik = v;
        podzbiory[v].rank = 0;
    }

    Krawedz* wynik = new Krawedz[graph.vertices - 1];
    int e = 0;
    int i = 0;

    while (e < graph.vertices - 1 && i < krawedzieIndex)
    {
        Krawedz nastepna_krawedz = krawedzie[i++];
        int x = znajdz(podzbiory, nastepna_krawedz.pocz);
        int y = znajdz(podzbiory, nastepna_krawedz.kon);

        if (x != y)
        {
            wynik[e++] = nastepna_krawedz;
            zlacz(podzbiory, x, y);
        }
    }
    if (write == true)
    {
        cout << "Krawedz Waga" << endl;
        for (int i = 0; i < e; i++)
        {
            cout << setw(3) << wynik[i].pocz << ":" << wynik[i].kon << setw(5) << wynik[i].waga << endl;
        }
    }
    delete[] podzbiory;
    delete[] krawedzie;
    delete[] wynik;
}

void Alg_Kruskal::Kruskal_matrix(Graph_matrix& graph, bool write)
{
    Krawedz* krawedzie = new Krawedz[graph.edges];
    int krawedzieIndex = 0;

    for (int j = 0; j < graph.edges; j++) 
    {
        int src = -1, dest = -1, weight = 0;
        for (int i = 0; i < graph.vertices; i++) 
        {
            if (graph.incidenceMatrix[i][j] != 0) 
            {
                if (src == -1) 
                {
                    src = i;
                    weight = graph.weightsMatrix[j];
                }
                else 
                {
                    dest = i;
                    break;
                }
            }
        }
        if (src != -1 && dest != -1) 
        {
            krawedzie[krawedzieIndex++] = { src, dest, weight };
        }
    }

    sort(krawedzie, krawedzie + krawedzieIndex, [](Krawedz a, Krawedz b) 
        {
        return a.waga < b.waga;
        });

    Podzbior* podzbiory = new Podzbior[graph.vertices];
    for (int v = 0; v < graph.vertices; ++v) 
    {
        podzbiory[v].poprzednik = v;
        podzbiory[v].rank = 0;
    }

    Krawedz* wynik = new Krawedz[graph.vertices - 1];
    int e = 0;
    int i = 0;

    while (e < graph.vertices - 1 && i < krawedzieIndex) 
    {
        Krawedz nastepna_krawedz = krawedzie[i++];
        int x = znajdz(podzbiory, nastepna_krawedz.pocz);
        int y = znajdz(podzbiory, nastepna_krawedz.kon);

        if (x != y) 
        {
            wynik[e++] = nastepna_krawedz;
            zlacz(podzbiory, x, y);
        }
    }
    if (write == true)
    {
        cout << "Krawedz Waga" << endl;
        for (int i = 0; i < e; i++)
        {
            cout << setw(3) << wynik[i].pocz << ":" << wynik[i].kon << setw(5) << wynik[i].waga << endl;
        }
    }

    delete[] podzbiory;
    delete[] krawedzie;
    delete[] wynik;
}

int Alg_Kruskal::znajdz(Podzbior podzbiory[], int i)
{
    if (podzbiory[i].poprzednik != i)
        podzbiory[i].poprzednik = znajdz(podzbiory, podzbiory[i].poprzednik);
    return podzbiory[i].poprzednik;
}

void Alg_Kruskal::zlacz(Podzbior subsets[], int x, int y) 
{
    int xroot = znajdz(subsets, x);
    int yroot = znajdz(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
    {
        subsets[xroot].poprzednik = yroot;
    }
    else if (subsets[xroot].rank > subsets[yroot].rank)
    {
        subsets[yroot].poprzednik = xroot;
    }
    else 
    {
        subsets[yroot].poprzednik = xroot;
        subsets[xroot].rank++;
    }
}
