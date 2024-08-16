#ifndef QuadTree_H
#define QuadTree_H

#include "Nodo.h"
#include <string>
#include <vector>

#pragma once

class QuadTree{

public:
    
    int tam;//Tamaño del lado
    int points;
    int suma=0;
    Point topLeft;
    Point botRight;
    std::vector<Nodo*> lista;
 
    Nodo* n;

    QuadTree* PrimerCuad;
    QuadTree* SegundoCuad;
    QuadTree* TercerCuad;
    QuadTree* CuartoCuad;

public:
    QuadTree(int size, Point t, Point b);
    ~QuadTree();
    int totalPoints(QuadTree* quad);
    int preOrderTotalPoints(QuadTree* quad, int tam);
    int totalNodes(QuadTree* quad);
    int preOrderTotalNodes(QuadTree* quad, int tam);
    void insert(Point p, int data);
    void insertQuad(Point p, int data, QuadTree* quad);
    std::vector<Nodo* > list();
    void preOrderList(QuadTree* qtree, QuadTree* original);
    int countRegion(Point p, int d);
    int preOrderCountRegion(QuadTree* qtree, int dxLeft, int dxRight, int dyUp, int dyDown);
    int AggregateRegion(Point p, int d);
    int preOrderAggregateRegion(QuadTree* qtree, int dxLeft, int dxRight, int dyUp, int dyDown);
    void pushLista(Nodo* n);

};


#endif