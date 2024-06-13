#include "Generate.h"

#include <iostream>
#include <fstream>
#include <random>

using namespace std;

Graph::Graph() : vertices(0), edges(0), startVertices(nullptr), endVertices(nullptr), weights(nullptr) 
{
    startVertices = new int[edges];
    endVertices = new int[edges];
    weights = new int[edges];
}

Graph::~Graph() 
{
    delete[] startVertices;
    delete[] endVertices;
    delete[] weights;
}

 bool Graph::isGraphValid()
 {
     return startVertices != nullptr && endVertices != nullptr && weights != nullptr;
 }

 void Graph::generateGraph(int vertices, float density)
 {
     std::random_device rd;
     std::mt19937 gen(rd());
     std::uniform_real_distribution<float> distribution((float)1, (float)vertices);

     this->vertices = vertices;
     edges = static_cast<int>(density * vertices * (vertices - 1) / 2);


     startVertices = new int[edges];
     endVertices = new int[edges];
     weights = new int[edges];

     // Generowanie drzewa rozpinaj¹cego 
     bool* visited = new bool[vertices]; // Zaktualizowane: zarezerwuj miejsce dla zerowego wierzcho³ka
     visited[0] = true; // Zaktualizowane: oznacz zerowy wierzcho³ek jako odwiedzony

     for (int i = 1; i < vertices; ++i) // Zaktualizowane: oznacz zerowy wierzcho³ek jako odwiedzony
         visited[i] = false;

     int* stack = new int[vertices];
     int stackTop = -1;

     stack[++stackTop] = 0;

     int edgeCount = 0;
     while (stackTop >= 0 && edgeCount < vertices - 1)
     {
         int currentVertex = stack[stackTop--];

         for (int i = vertices - 1; i >= 0; --i)
         {
             if (currentVertex != i && !visited[i])
             {
                 startVertices[edgeCount] = currentVertex;
                 endVertices[edgeCount] = i;
                 weights[edgeCount] = distribution(gen);
                 edgeCount++;

                 stack[++stackTop] = i;
                 visited[i] = true;
             }
         }
     }

     delete[] stack;

     // Dodaj pozosta³e krawêdzie, aby osi¹gn¹æ ¿¹dan¹ gêstoœæ i zapewniæ spójnoœæ
     for (int i = 1; i < vertices; ++i) 
     {

         if (edgeCount >= edges)
             break;

         if (!visited[i])
         {
             int startV = std::uniform_int_distribution<int>(0, i - 1)(gen); 
             startVertices[edgeCount] = startV;
             endVertices[edgeCount] = i;
             weights[edgeCount] = distribution(gen);
             edgeCount++;

             visited[i] = true;
         }
     }

     // Dodaj pozosta³e krawêdzie, aby osi¹gn¹æ ¿¹dan¹ gêstoœæ
     while (edgeCount < edges)
     {
         int startV = std::uniform_int_distribution<int>(0, vertices - 1)(gen);
         int endV = std::uniform_int_distribution<int>(0, vertices - 1)(gen);
         if (startV != endV)
         {
             startVertices[edgeCount] = startV;
             endVertices[edgeCount] = endV;
             weights[edgeCount] = distribution(gen);
             edgeCount++;
         }
     }
     delete[] visited;
 }

