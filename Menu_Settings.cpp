#include "Menu_Settings.h"
#include "Graph_matrix.h"
#include "Graph_list.h"
#include "Generate.h"
#include "Alg_Prim.h"
#include "Alg_Kruskal.h"
#include "Alg_Dijkstra.h"
#include "Alg_Ford_Bellman.h"
#include "Simulation.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <chrono>

using namespace std;

void Menu_Settings::f_menu_settings(int mode)
{
    Graph_list list;
    Graph_matrix matrix;

    int wybor_funkcji = 0;
    bool y = true;
    while (y)
    {
        //system("cls");
        cout << endl;
        cout << "Wybierz funkcje programu: " << endl;
        cout << "1. Odczyt grafu z pliku" << endl;
        cout << "2. Zapis grafu do pliku " << endl;
        cout << "3. Generowanie grafu" << endl;
        cout << "4. Wyswietlenie grafu listowo i macierzowo" << endl;
        if (mode == 1)
        {
            cout << "5. Wybor algorytmu Prima" << endl;
            cout << "6. Wybor algorytmu Kruskala" << endl;
        }
        else if (mode == 2)
        {
            cout << "5. Wybor algorytmu Dijkstry" << endl;
            cout << "6. Wybor algorytmu Forda-Bellmana" << endl;
        }
        cout << "7. Tryb symulacji" << endl;
        cout << "8. Zmien problem" << endl;
        cout << "9. Wylaczenie programu" << endl;
        cout << endl;
        cin >> wybor_funkcji;

        switch (wybor_funkcji)
        {
        case 1:
        {
            string filename;
            cout << "Podaj nazwe pliku: ";
            cin >> filename;
            if (mode == 1)
            {
                matrix.load_graph(filename, 1);
                list.load_graph(filename, 1);
            }           
            else if (mode == 2)
            {
                matrix.load_graph(filename, -1);
                list.load_graph(filename, 2);
            }
            break;
        }

        case 2:
        {
            if (mode == 1)
            {
                matrix.save_graph_mst();
                list.save_graph();             
            }
            else if (mode == 2)
            {
                matrix.save_graph_naj();
                list.save_graph();               
            }
            break;
        }

        case 3:
        {
            int vertices;
            float density;
            cout << "Podaj liczbe wierzcholkow: ";
            cin >> vertices;
            cout << "Podaj gestosc grafu: 1. 25%" << endl;
            cout << "                     2. 50%" << endl;
            cout << "                     3. 99%" << endl;
            cout << endl;
            cin >> density;
            if (density == 1)
            {
                Graph graph;
                graph.generateGraph(vertices, 0.25);
                list.populateFromGraph(graph);
                if (mode == 1)
                {
                    matrix.populateFromGraph(graph, 1);
                }
                else if (mode == 2)
                {
                    matrix.populateFromGraph(graph, -1);
                }
            }
            else if (density == 2)
            {
                Graph graph;
                graph.generateGraph(vertices, 0.5);              
                list.populateFromGraph(graph);
                if (mode == 1)
                {
                    matrix.populateFromGraph(graph, 1);
                }
                else if (mode == 2)
                {
                    matrix.populateFromGraph(graph, -1);
                }
            }
            else if (density == 3)
            {
                Graph graph;
                graph.generateGraph(vertices, 0.99);
                list.populateFromGraph(graph);
                if (mode == 1)
                {
                    matrix.populateFromGraph(graph, 1);
                }
                else if (mode == 2)
                {
                    matrix.populateFromGraph(graph, -1);
                }
            }
            else
            {
                cout << "Bledna gestosc" << endl;
            }
            break;
        }
        case 4:
        {
            matrix.display_graph();
            matrix.shouldDeleteData = false;
            list.display_graph();
            list.shouldDeleteData = false;

                    
            break;
        }
        case 5:
        {
            if (mode == 1)
            {
                Alg_Prim prim;
                matrix.shouldDeleteData = false;
                list.shouldDeleteData = false;
                if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                {
                    cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                }
                else
                {
                    auto begin = chrono::high_resolution_clock::now();
                    prim.Prim_matrix(matrix, true);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);
                    cout << "Czas wykonania dla macierzy: " << elapsed.count() << " ms" << endl << endl;
                }

                if (list.vertices <= 0 || list.edgeCounts == nullptr || list.adjacencyList == nullptr)
                {
                    cout << "Lista sasiedztwa nie jest poprawnie zaladowana." << endl;
                }
                else
                {
                    auto begin = chrono::high_resolution_clock::now();
                    prim.Prim_list(list, true);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);
                    cout << "Czas wykonania dla listy: " << elapsed.count() << " ms" << endl << endl;
                }
                
            }
            else if (mode == 2)
            {
                Alg_Dijkstra dijkstra;
                matrix.shouldDeleteData = false;
                list.shouldDeleteData = false;

                int startV, endV;
                cout << "Podaj wierzcholek poczatkowy: ";
                cin >> startV;
                cout << "Podaj wierzcholek koncowy: ";
                cin >> endV;
                cout << endl;

                if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                {
                    cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                }
                else
                {
                    cout << "Macierz incydencji" << endl;
                    auto begin = chrono::high_resolution_clock::now();
                    dijkstra.Dijkstra_matrix(matrix, startV, endV, true);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);
                    cout << "Czas wykonania dla macierzy: " << elapsed.count() << " ms" << endl << endl;
                }

                if (list.vertices <= 0 || list.edgeCounts == nullptr || list.adjacencyList == nullptr)
                {
                    cout << "Lista sasiedztwa nie jest poprawnie zaladowana." << endl;
                }
                else
                {
                    cout << "Lista sasiedztwa" << endl;
                    auto begin = chrono::high_resolution_clock::now();
                    dijkstra.Dijkstra_list(list, startV, endV, true);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);
                    cout << "Czas wykonania dla listy: " << elapsed.count() << " ms" << endl << endl;
                }
            }
            break;
        }
        case 6:
        {
            if (mode == 1)
            {
                Alg_Kruskal kruskal;
                matrix.shouldDeleteData = false;
                list.shouldDeleteData = false;

                if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                {
                    cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                }
                else
                {

                    auto begin = chrono::high_resolution_clock::now();
                    kruskal.Kruskal_matrix(matrix, true);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);
                    cout << "Czas wykonania dla macierzy: " << elapsed.count() << " ms" << endl << endl;
                }

                if (list.vertices <= 0 || list.edgeCounts == nullptr || list.adjacencyList == nullptr)
                {
                    cout << "Lista sasiedztwa nie jest poprawnie zaladowana." << endl;
                }
                else
                {
                    auto begin = chrono::high_resolution_clock::now();
                    kruskal.Kruskal_list(list, true);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);
                    cout << "Czas wykonania dla listy: " << elapsed.count() << " ms" << endl << endl;
                }   
            }
            else if (mode == 2)
            {
                alg_Ford_Bellman ford_bellman;
                matrix.shouldDeleteData = false;
                list.shouldDeleteData = false;

                int startV, endV;
                cout << "Podaj wierzcholek poczatkowy: ";
                cin >> startV;
                cout << "Podaj wierzcholek koncowy: ";
                cin >> endV;
                cout << endl;

                if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                {
                    cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                }
                else
                {

                    auto begin = chrono::high_resolution_clock::now();
                    ford_bellman.Ford_Bellman_matrix(matrix, startV, endV, true);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);
                    cout << "Czas wykonania dla macierzy: " << elapsed.count() << " ms" << endl << endl;
                }

                if (list.vertices <= 0 || list.edgeCounts == nullptr || list.adjacencyList == nullptr)
                {
                    cout << "Lista sasiedztwa nie jest poprawnie zaladowana." << endl;
                }
                else
                {
                    
                    auto begin = chrono::high_resolution_clock::now();
                    ford_bellman.Ford_Bellman_list(list, startV, endV, true);
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);
                    cout << "Czas wykonania dla listy: " << elapsed.count() << " ms" << endl << endl;
                }     
            }
            break;
        }
        case 7:
        {
            Simulation simulation; 
            simulation.simulation_mode(1);
            simulation.simulation_mode(2);
            simulation.simulation_mode(3);
            simulation.simulation_mode(4);
        }

        case 8:
        {
            y = false;
            break;
        }

        case 9:
        {
            y = false;
            cout << "Zakonczono dzialanie programu" << endl;
            exit(0);
            break;
        }

        default:
        {
            cout << "Wybrano niepoprawna opcje" << endl;
            break;
        }
        }
    }

}
