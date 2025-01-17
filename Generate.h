#ifndef GENERATE_H
#define GENERATE_H

#include <string>

class Graph 
{
public:
    int vertices;
    int edges;
    int* startVertices; // Tablica przechowująca początki krawędzi
    int* endVertices;   // Tablica przechowująca końce krawędzi
    int* weights;       // Tablica przechowująca wagi krawędzi

    Graph();
    ~Graph();

    void generateGraph(int vertices, float density);
    bool isGraphValid();


};

#endif GENERATE_H


