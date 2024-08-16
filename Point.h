#ifndef POINT_H
#define POINT_H
#include <iostream>

#pragma once


class Point
{

public:

    float coordenadaX;
    float coordenadaY;


public:
    Point(float x, float y);
    ~Point();
    float getX();
    float getY();
    void setX(float x);
    void setY(float y);

};

#endif