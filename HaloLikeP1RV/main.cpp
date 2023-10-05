#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glut.h>
#include <gl\GL.h>

struct Vertex {
    float x, y, z;
};

struct Face {
    int v1, v2, v3;
};

std::vector<Vertex> vertices;
std::vector<Face> faces;

void LoadOBJ(const char* filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        iss >> token;

        if (token == "v") {
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        }
        else if (token == "f") {
            Face face;
            iss >> face.v1 >> face.v2 >> face.v3;
            faces.push_back(face);
        }
    }
    file.close();
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Render the loaded object
    glBegin(GL_TRIANGLES);
    for (const Face& face : faces) {
        glVertex3f(vertices[face.v1 - 1].x, vertices[face.v1 - 1].y, vertices[face.v1 - 1].z);
        glVertex3f(vertices[face.v2 - 1].x, vertices[face.v2 - 1].y, vertices[face.v2 - 1].z);
        glVertex3f(vertices[face.v3 - 1].x, vertices[face.v3 - 1].y, vertices[face.v3 - 1].z);
    }
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL OBJ Loader");

    glEnable(GL_DEPTH_TEST);

    LoadOBJ("Modele\cube.obj"); // Replace with the path to your OBJ file

    glutDisplayFunc(Display);
    glutMainLoop();

    return 0;
}