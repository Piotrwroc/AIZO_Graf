#include "Graph_list.h"
#include "Generate.h"

#include <iostream>
#include <fstream>
#include <fstream>

using namespace std;

Graph_list::Graph_list() : vertices(0), edges(0), edgeCounts(nullptr), adjacencyList(nullptr), shouldDeleteData(true) 
{   
    edgeCounts = new int[vertices];
    for (int i = 0; i < vertices; ++i) 
    {
        edgeCounts[i] = 0; 
    }

    adjacencyList = new My_pair<int, int>* [vertices];
    for (int i = 0; i < vertices; ++i) 
    {
        adjacencyList[i] = new My_pair<int, int>[edgeCounts[i]];
        for (int j = 0; j < edgeCounts[i]; ++j) 
        {
            adjacencyList[i][j] = My_pair<int, int>(0, 0); 
        }
    }
}


Graph_list::~Graph_list()
{
    if (shouldDeleteData)
    {
        if (adjacencyList)
        {
            for (int i = 0; i < vertices; i++)
            {
                delete[] adjacencyList[i];
            }
            delete[] adjacencyList;
        }
        if (edgeCounts) delete[] edgeCounts;
    }
    //shouldDeleteData = true;    
}

void Graph_list::load_graph(string& filename, int mode)
{
    ifstream file;
    file.open(filename);
    if (file.is_open())
    {
        file >> edges >> vertices;

        edgeCounts = new int[vertices]();
        adjacencyList = new My_pair<int, int>* [vertices];

        // Najpierw policzmy liczbê krawêdzi wychodz¹cych z ka¿dego wierzcho³ka
        for (int i = 0; i < edges; i++)
        {
            int startVertex, endVertex, weight;
            file >> startVertex >> endVertex >> weight;
            edgeCounts[startVertex]++;
            if (mode == 1)
            {
                edgeCounts[endVertex]++;
            }
        }

        // Teraz alokujemy tablice dla ka¿dej listy s¹siedztwa
        for (int i = 0; i < vertices; i++)
        {
            adjacencyList[i] = new My_pair<int, int>[edgeCounts[i]];
            edgeCounts[i] = 0; // Zresetuj licznik, aby u¿yæ go ponownie podczas wczytywania krawêdzi
        }

        // Wczytaj plik ponownie, aby wype³niæ listy s¹siedztwa
        file.clear();
        file.seekg(0, ios::beg);
        file >> edges >> vertices; // Ponownie wczytaj nag³ówek

        for (int i = 0; i < edges; i++)
        {
            int startVertex, endVertex, weight;
            file >> startVertex >> endVertex >> weight;
            adjacencyList[startVertex][edgeCounts[startVertex]] = My_pair<int, int>(endVertex, weight);
            edgeCounts[startVertex]++;
            if (mode == 1)
            {
                adjacencyList[endVertex][edgeCounts[endVertex]] = My_pair<int, int>(startVertex, weight);
                edgeCounts[endVertex]++;


            }
        }
        file.close();
        cout << "Odczyt dla listy udany" << endl;
    }
    else
    {
        cout << "Nie mozna odtworzyc pliku: " << filename << endl << endl;
    }
}


void Graph_list::display_graph()
{
    if (!isGraphValid())
    {
        cout << "Lista sasiedztwa nie jest poprawnie zaladowana." << endl;
        return;
    }

    cout << "Lista sasiedztwa:" << endl;
    for (int i = 0; i < vertices; i++)
    {
        cout << "Wierzcholek " << i << ": ";
        for (int j = 0; j < edgeCounts[i]; j++)
        {
            // Wyœwietlanie krawêdzi w kierunku zdefiniowanym w grafie
            cout << "(" << adjacencyList[i][j].first << ", " << adjacencyList[i][j].second << ") ";
        }
        cout << endl;
    }
}


bool Graph_list::isGraphValid()
{
    return adjacencyList != nullptr && edgeCounts != nullptr;
}

void Graph_list::save_graph()
{
    if (isGraphValid())
    {
        string filename;
        cout << "Podaj nazwe pliku do zapisania listy sasiedztwa: " << endl;
        cin >> filename;
        filename += ".txt";
        ofstream file;

        file.open(filename);
        if (file.is_open())
        {
            file << edges << " " << vertices << endl;

            for (int i = 0; i < vertices; i++)
            {
                for (int j = 0; j < edgeCounts[i]; j++)
                {
                    file << i << " " << adjacencyList[i][j].first << " " << adjacencyList[i][j].second << endl;
                }
            }
            file.close();
            cout << "Zapis udany" << endl;
        }
        else
        {
            cout << "Nie mozna otworzyc pliku do zapisu: " << filename << endl;
        }
    }
    else cout << "Lista sasiedztwa nie zostala poprawnie wczytana. Nie mo¿na zapisac grafu." << endl;
}

void Graph_list::populateFromGraph(Graph& graph)
{
    //Clean up previous adjacency list if it exists
    if (adjacencyList) 
    {
        for (int i = 0; i < vertices; ++i) 
        {
            delete[] adjacencyList[i];
        }
        delete[] adjacencyList;
    }
    delete[] edgeCounts;

    vertices = graph.vertices;
    edges = graph.edges;

    edgeCounts = new int[vertices]();

    // Initialize adjacency list array
    adjacencyList = new My_pair<int, int>* [vertices];
    for (int i = 0; i < vertices; ++i) 
    {
        adjacencyList[i] = new My_pair<int, int>[edges];
    }

    // Fill the adjacency list and edgeCounts
    for (int i = 0; i < edges; ++i) 
    {
        int startVertex = graph.startVertices[i];
        int endVertex = graph.endVertices[i];
        int weight = graph.weights[i];
        adjacencyList[startVertex][edgeCounts[startVertex]] = My_pair<int, int>(endVertex, weight);
        edgeCounts[startVertex]++;
    }
}

