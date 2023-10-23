#pragma once

#ifndef Geometry_h
#define Geometry_h

#include "glm/glm/glm.hpp"

struct Vertex { // Point
    float x, y, z;
    float r, v, b;
};
struct Tex {
    float v1, v2;
};

struct Face { // Face Triangulaire composé de ses 3 points
    int v1, v2, v3;
    int vt1, vt2, vt3;
    int normal;
};


#endif 
