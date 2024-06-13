#ifndef GENERATE_H
#define GENERATE_H

#include <string>

class Graph 
{
public:
    int vertices;
    int edges;
    int* startVertices; // Tablica przechowuj¹ca pocz¹tki krawêdzi
    int* endVertices;   // Tablica przechowuj¹ca koñce krawêdzi
    int* weights;       // Tablica przechowuj¹ca wagi krawêdzi

    Graph();
    ~Graph();

    void generateGraph(int vertices, float density);
    bool isGraphValid();


};

#endif GENERATE_H


