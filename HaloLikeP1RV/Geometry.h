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

struct vraiFace {
    glm::vec3 vertexA;
    glm::vec3 vertexB;
    glm::vec3 vertexC;
    //glm::vec2 texCoords;
    glm::vec3 normal;
};

struct PointText { // On a un point avec sa coordonnées de texture (pas indices, coordonnée)
    glm::vec3 position;
    float u, v;
    glm::vec3 normal;
};

#endif 
