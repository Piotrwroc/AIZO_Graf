#include "Graph_matrix.h"

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


Graph_matrix::Graph_matrix() : vertices(0), edges(0), incidenceMatrix(nullptr), weightsMatrix(nullptr), shouldDeleteData(true) 
{
    incidenceMatrix = new int* [vertices];
    for (int i = 0; i < vertices; ++i) 
    {
        incidenceMatrix[i] = new int[edges];
        for (int j = 0; j < edges; ++j) 
        {
            incidenceMatrix[i][j] = 0; 
        }
    }
    weightsMatrix = new int[edges];
    for (int i = 0; i < edges; ++i) 
    {
        weightsMatrix[i] = 0; 
    }
}

Graph_matrix::~Graph_matrix() 
{
    if (shouldDeleteData)
    {
        if (incidenceMatrix)
        {
            for (int i = 0; i < vertices; i++)
            {
                delete[] incidenceMatrix[i];
            }
            delete[] incidenceMatrix;
        }
        if (weightsMatrix) delete[] weightsMatrix;
    }
    //else shouldDeleteData = true;
}

void Graph_matrix::load_graph(string& filename, int type)
{
    ifstream file;
    file.open(filename);
    if (file.is_open())
    {
            file >> edges >> vertices;

            incidenceMatrix = new int* [vertices];
            weightsMatrix = new int[edges];
            for (int i = 0; i < vertices; i++)
            {
                incidenceMatrix[i] = new int[edges]();
            }

            for (int i = 0; i < edges; i++)
            {
                int startVertex = 0, endVertex = 0;
                file >> startVertex >> endVertex >> weightsMatrix[i];
                incidenceMatrix[startVertex][i] = 1;
                incidenceMatrix[endVertex][i] = type;
            }
            file.close();
            cout << "Odczyt dla macierzy udany" << endl;
    }
    else
    {
        cout << "Nie mozna odtworzyc pliku: " << filename << endl << endl;
    }
}

void Graph_matrix::display_graph()
{
    if (!isGraphValid())
    {
        cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
        return;
    }

    cout << "Macierz incydencji:" << endl;
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < edges; j++)
        {
            cout << setw(3) << incidenceMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Tablica wag : " << endl;
    for (int i = 0; i < edges; i++)
    {
        cout << setw(3) << weightsMatrix[i] << " ";
    }
    cout << endl;
}

bool Graph_matrix::isGraphValid()
{
    return incidenceMatrix != nullptr && weightsMatrix != nullptr;
}

void Graph_matrix::save_graph_naj()
{
    if (isGraphValid())
    {
        string filename;
        cout << "Podaj nazwe pliku do zapisania macierzy incydencji: " << endl;
        cin >> filename;
        filename += ".txt";
        ofstream file;

        file.open(filename);
        if (file.is_open()) {
            file << edges << " " << vertices << endl;
            for (int i = 0; i < edges; i++)
            {
                int j2 = 0;
                int startVertex = -1, endVertex = -1;
                for (int j1 = 0; j1 < vertices; j1++)
                {
                    if (incidenceMatrix[j1][i] == 1)
                    {
                        startVertex = j1;
                        j2 = j1;
                        break;
                    }
                }
                for (j2; j2 < vertices; j2++)
                {
                    if (incidenceMatrix[j2][i] == 1)
                    {
                        startVertex = j2;
                        break;
                    }
                }
                file << startVertex << " " << endVertex << " " << weightsMatrix[i] << endl;
            }
            file.close();
            cout << "Zapis udany" << endl;
        }
        else
        {
            cout << "Nie mozna otworzyc pliku do zapisu: " << filename << endl;
        }
    }
    else cout << "Macierz incydencji nie zostala poprawnie wczytana. Nie mozna zapisac grafu." << endl;
}

void Graph_matrix::save_graph_mst()
{
    if (isGraphValid())
    {
        string filename;
        cout << "Podaj nazwe pliku do zapisania macierzy incydencji: " << endl;
        cin >> filename;
        filename += ".txt";
        ofstream file;

        file.open(filename);
        if (file.is_open()) {
            file << edges << " " << vertices << endl;
            for (int i = 0; i < edges; i++)
            {
                int startVertex = -1, endVertex = -1;
                for (int j = 0; j < vertices; j++)
                {
                    if (incidenceMatrix[j][i] == 1) startVertex = j;
                    if (incidenceMatrix[j][i] == -1) endVertex = j;
                }
                file << startVertex << " " << endVertex << " " << weightsMatrix[i] << endl;
            }
            file.close();
            cout << "Zapis udany" << endl;
        }
        else
        {
            cout << "Nie mozna otworzyc pliku do zapisu: " << filename << endl;
        }
    }
    else cout << "Macierz incydencji nie zostala poprawnie wczytana. Nie mozna zapisac grafu." << endl;
}

void Graph_matrix::populateFromGraph(Graph& graph,int type)
{
    // Clean up previous matrices if they exist
    if (incidenceMatrix) 
    {
        for (int i = 0; i < vertices; ++i) 
        {
            delete[] incidenceMatrix[i];
        }
        delete[] incidenceMatrix;
    }
    delete[] weightsMatrix;

    vertices = graph.vertices;
    edges = graph.edges;

    incidenceMatrix = new int* [vertices];
    weightsMatrix = new int[edges];

    // Initialize incidence matrix with zeros
    for (int i = 0; i < vertices; ++i) 
    {
        incidenceMatrix[i] = new int[edges]();
    }

    // Populate incidence matrix and weights matrix
    for (int i = 0; i < edges; ++i) 
    {
        int startVertex = graph.startVertices[i];
        int endVertex = graph.endVertices[i];
        int weight = graph.weights[i];

        incidenceMatrix[startVertex][i] = 1;
        incidenceMatrix[endVertex][i] = type;
        weightsMatrix[i] = weight;
    }
}
