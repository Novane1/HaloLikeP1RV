#pragma once

#ifndef Geometry_h
#define Geometry_h
// Librairies
#pragma once
#include "windows.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <GL/gl.h>
#include <glut.h>
using namespace std;



struct Vertex { // Point
    float x, y, z;
    float r, v, b;
};

struct Face { // Face Triangulaire composé de ses 3 points
    int v1, v2, v3;
};

#endif once
