#include "Simulation.h"
#include "Alg_Prim.h"
#include "Alg_Kruskal.h"
#include "Alg_Dijkstra.h"
#include "Alg_Ford_Bellman.h"
#include "Generate.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <chrono>

#define REPETITION 50
#define UNIT 1000


void Simulation::simulation_mode(int algnum)
{

    //int vertexCounts[] = {40, 80, 160, 320, 640, 1280, 2560 }; // liczby wierzcho³ków
    //int vertexCounts[] = {20, 50, 100, 200, 400, 600, 800}; // liczby wierzcho³ków
    int vertexCounts[] = { 10, 20, 50, 100, 200, 500, 1000 }; // liczby wierzcho³ków
    float densities[] = { 0.25, 0.50, 0.99 }; // gêstoœci grafu


    if (algnum == 1)
    {
        Alg_Prim prim;
        cout << mode_name(algnum) << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << "----- gestosc " << densities[i] << endl;
            for (int j = 0; j < 7; j++)
            {
                cout << "--- rozmiar " << vertexCounts[j] << endl;

                int ver = vertexCounts[j];
                float den = densities[i];
                std::chrono::duration<double> czas1{};

                for (int n = 0; n < REPETITION; n++)
                {
                    Graph_list list;
                    Graph graph;
                    graph.generateGraph(ver, den);
                    list.populateFromGraph(graph);

                    auto begin = chrono::high_resolution_clock::now();
                    prim.Prim_list(list, false);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
                    czas1 += elapsed;
                }
                cout << "Czas dla listy wyniosl: " << czas1.count() * UNIT / REPETITION << " ms" << endl;

                std::chrono::duration<double> czas2{};
                for (int n = 0; n < REPETITION; n++)
                {
                    Graph_matrix matrix;
                    Graph graph;
                    graph.generateGraph(ver, den);
                    matrix.populateFromGraph(graph, 1);

                    auto begin = chrono::high_resolution_clock::now();
                    prim.Prim_matrix(matrix, false);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
                    czas2 += elapsed;

                }
                cout << "Czas dla macierzy wyniosl: " << czas2.count() * UNIT / REPETITION << " ms" << endl;
            }
        }
    }

    if (algnum == 2)
    {
        Alg_Kruskal kruskal;
        cout << mode_name(algnum) << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << "----- gestosc " << densities[i] << endl;
            for (int j = 0; j < 7; j++)
            {
                cout << "--- rozmiar " << vertexCounts[j] << endl;

                int ver = vertexCounts[j];
                float den = densities[i];

                std::chrono::duration<double> czas1{};
                for (int n = 0; n < REPETITION; n++)
                {
                    Graph_list list;
                    Graph graph;
                    graph.generateGraph(ver, den);
                    list.populateFromGraph(graph);


                    auto begin = chrono::high_resolution_clock::now();
                    kruskal.Kruskal_list(list, false);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
                    czas1 += elapsed;

                }
                cout << "Czas dla listy wyniosl: " << czas1.count() * UNIT / REPETITION << " ms" << endl;

                std::chrono::duration<double> czas2{};
                for (int n = 0; n < REPETITION; n++)
                {
                    Graph_matrix matrix;
                    Graph graph;
                    graph.generateGraph(ver, den);
                    matrix.populateFromGraph(graph, 1);

                    auto begin = chrono::high_resolution_clock::now();
                    kruskal.Kruskal_matrix(matrix, false);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
                    czas2 += elapsed;

                }
                cout << "Czas dla macierzy wyniosl: " << czas2.count() * UNIT / REPETITION << " ms" << endl;
            }
        }
    }

    if (algnum == 3)
    {
        Alg_Dijkstra dijkstra;
        cout << mode_name(algnum) << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << "----- gestosc " << densities[i] << endl;
            for (int j = 0; j < 7; j++)
            {
                cout << "--- rozmiar " << vertexCounts[j] << endl;

                int ver = vertexCounts[j];
                float den = densities[i];

                std::chrono::duration<double> czas1{};
                for (int n = 0; n < REPETITION; n++)
                {
                    Graph_list list;
                    Graph graph;
                    graph.generateGraph(ver, den);
                    list.populateFromGraph(graph);


                    auto begin = chrono::high_resolution_clock::now();
                    dijkstra.Dijkstra_list(list, 0, ver, false);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
                    czas1 += elapsed;

                }
                cout << "Czas dla listy wyniosl: " << czas1.count() * UNIT / REPETITION << " ms" << endl;

                std::chrono::duration<double> czas2{};
                for (int n = 0; n < REPETITION; n++)
                {
                    Graph_matrix matrix;
                    Graph graph;
                    graph.generateGraph(ver, den);
                    matrix.populateFromGraph(graph, -1);

                    auto begin = chrono::high_resolution_clock::now();
                    dijkstra.Dijkstra_matrix(matrix, 0, ver, false);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
                    czas2 += elapsed;

                }
                cout << "Czas dla macierzy wyniosl: " << czas2.count() * UNIT / REPETITION << " ms" << endl;
            }
        }
    }

    if (algnum == 4)
    {
        alg_Ford_Bellman ford_bellman;
        cout << mode_name(algnum) << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << "----- gestosc " << densities[i] << endl;
            for (int j = 0; j < 7; j++)
            {
                cout << "--- rozmiar " << vertexCounts[j] << endl;

                int ver = vertexCounts[j];
                float den = densities[i];

                std::chrono::duration<double> czas1{};
                for (int n = 0; n < REPETITION; n++)
                {
                    Graph_list list;
                    Graph graph;
                    graph.generateGraph(ver, den);
                    list.populateFromGraph(graph);


                    auto begin = chrono::high_resolution_clock::now();
                    ford_bellman.Ford_Bellman_list(list, 0, ver, false);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
                    czas1 += elapsed;
                }
                cout << "Czas dla listy wyniosl: " << czas1.count() * UNIT / REPETITION << " ms" << endl;

                std::chrono::duration<double> czas2{};
                for (int n = 0; n < REPETITION; n++)
                {
                    Graph_matrix matrix;
                    Graph graph;
                    graph.generateGraph(ver, den);
                    matrix.populateFromGraph(graph, -1);

                    auto begin = chrono::high_resolution_clock::now();
                    ford_bellman.Ford_Bellman_matrix(matrix, 0, ver, false);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
                    czas2 += elapsed;

                }
                cout << "Czas dla macierzy wyniosl: " << czas2.count() * UNIT / REPETITION << " ms" << endl;
            }
        }
    }

    cout << endl << endl << endl;
}

const char* Simulation::mode_name(int algnum)
{
    switch (algnum) 
    {
    case 1:
    {
        return "Algorytm Prima";
        break;
    }
    case 2:
    {
        return "Algorytm Kruskala";
        break;
    }
    case 3:
    {
        return "Algorytm Dijkstry";
        break;
    }
    case 4:
    {
        return "Algorytm Forda-Bellmana";
        break;
    }
    {
    deafult:
        return "error";
    }
    }
}
