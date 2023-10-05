//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include <glut.h>
//#include <gl\GL.h>
//using namespace std;
//
//struct Vertex {
//    float x, y, z;
//};
//
//struct Face {
//    int v1, v2, v3;
//};
//
//vector<Vertex> vertices;
//vector<Face> faces;
//
//void LoadOBJ(const char* filename, vector<Vertex> vertices, vector<Face> faces) {
//    std::ifstream file(filename);
//    std::string line;
//
//    if (!file.is_open()) {
//        std::cerr << "Failed to open file: " << filename << std::endl;
//        return;
//    }
//
//    while (std::getline(file, line)) {
//        std::istringstream iss(line);
//        std::string token;
//        
//        iss >> token;
//
//        if (token == "v") {
//            Vertex vertex;
//            iss >> vertex.x >> vertex.y >> vertex.z;
//            vertices.push_back(vertex);
//        }
//        else if (token == "f") {
//            Face face;
//            iss >> face.v1 >> face.v2 >> face.v3;
//            faces.push_back(face);
//        }
//        else if (token == "vn") {
//            // Handle vertex normals (if needed)
//            // You can parse and store them in a similar way as vertices
//        }
//        else if (token == "vt") {
//            // Handle texture coordinates (if needed)
//            // You can parse and store them in a similar way as vertices
//        }
//    }
//    file.close();
//}
//
//void Display() {
//
//    glMatrixMode(GL_MODELVIEW);
//
//
//
//
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//    // Render the loaded object
//    glBegin(GL_TRIANGLES);
//    for (const Face& face : faces) {
//        glColor3f(1.0f, 0.0f, 0.0f);
//        glVertex3f(vertices[face.v1 - 1].x, vertices[face.v1 - 1].y, vertices[face.v1 - 1].z);
//        glVertex3f(vertices[face.v2 - 1].x, vertices[face.v2 - 1].y, vertices[face.v2 - 1].z);
//        glVertex3f(vertices[face.v3 - 1].x, vertices[face.v3 - 1].y, vertices[face.v3 - 1].z);
//        
//    }
//    glEnd();
//    glFlush();
//    glutSwapBuffers();
//
//}
//
//void Reshape(int width, int height) {
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("OpenGL OBJ Loader");
//
//    glEnable(GL_DEPTH_TEST);
//
//    LoadOBJ("Modele/icosphere.obj", vertices, faces); // Replace with the path to your OBJ file
//
//    glutDisplayFunc(Display);
//    glutReshapeFunc(Reshape);
//    glutMainLoop();
//
//    return 0;
//}








//
//  students.cpp
//  ANREC_OGL_Cube3D
//
//  Created by Jean-Marie Normand on 21/09/2015.
//  Copyright © 2015 Centrale Innovation. All rights reserved.
//
#include "windows.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
// Fichiers d'en-têtes pour OpenGL et GLUT

#include <GL/gl.h>
#include <glut.h>
using namespace std;

struct Vertex {
    float x, y, z;
};

struct Face {
    int v1, v2, v3;
};
// Structure de données simpliste
// pour stocker un sommet 3D et
// ses informations de couleur

vector<Vertex> vertices;
vector<Face> faces;
const int imageWidth = 436;
const int imageHeight = 436;
unsigned char* image;


// Quelques variables globales (c'est pas bien)
GLfloat pointSize = 5.0f;
GLint typeForme = 0;
float parX = 0;
float parY = 0;
bool red = true;
bool blue = true;
float pas = 0.1f;

// Rotations autour de X et Y
GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLfloat oldX = 0.0f;
GLfloat oldY = 0.0f;
GLboolean boutonClick = false;

// Taille de la fenêtre
int windowW = 640;
int windowH = 480;
float focale = 65.0f;
float near1 = 0.1f;
float far1 = 100.0f;

// Déclarations des fonctions de rappel (callbacks)
GLvoid affichage();
GLvoid clavier(unsigned char touche, int x, int y);

GLvoid redimensionner(int w, int h);


// Definition de la fonction d'affichage
GLvoid affichage() {

    // Effacement du frame buffer



    glMatrixMode(GL_MODELVIEW);
    // glDrawBuffer(GL_COLOR_BUFFER);
    glClear(GL_COLOR_BUFFER_BIT); //| GL_DEPTH_BUFFER_BIT);

    //glDrawBuffer(GL_BACK_LEFT);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glBegin(GL_TRIANGLES);
    for (const Face& face : faces) {
       
        glVertex3f(vertices[face.v1 - 1].x, vertices[face.v1 - 1].y, vertices[face.v1 - 1].z);
        glVertex3f(vertices[face.v2 - 1].x, vertices[face.v2 - 1].y, vertices[face.v2 - 1].z);
        glVertex3f(vertices[face.v3 - 1].x, vertices[face.v3 - 1].y, vertices[face.v3 - 1].z);
        
    }
    /*glVertex3f(0.000000 ,-1.000000, 0.000000);
    glVertex3f(0.425323, - 0.850654 ,0.309011);
    glVertex3f(-0.162456 ,- 0.850654 ,0.499995);*/
    glEnd();

    // glDisable(GL_BLEND);
    glFlush();
    glutSwapBuffers();
}

// Definition de la fonction gerant les interruptions clavier
GLvoid clavier(unsigned char touche, int x, int y) {

    // Suivant les touches pressees, nous aurons un comportement different de l'application
    // ESCAPE ou 'q' : fermera l'application
    // 'p' : affichage du carre plein
    // 'f' : affichage du carre en fil de fer
    // 's' : affichage des sommets du carre

    switch (touche) {

        // Gestion du tampon de profondeur
    case 'd':
        // TODO : activer le test du tampon de profondeur
        glutPostRedisplay();
        break;
    case 'D':
        //TODO : desactiver le test du tampon de profondeur
        glutPostRedisplay();
        break;


    case 'q': // quitter
    case 27:
        exit(0);
        break;
    }

    // Demande a GLUT de reafficher la scene
    glutPostRedisplay();

}



// Callback de redimensionnement de la fenêtre
GLvoid redimensionner(int w, int h) {
    // Garde les valeurs
    windowW = w;
    windowH = h;
    // eviter une division par 0
    if (windowH == 0)
        windowH = 1;

    float ratio = (float)windowW / (float)windowH;
    std::cout << "Ratio : " << ratio << std::endl;

    // Projection
    glMatrixMode(GL_PROJECTION);

    // Resetting matrix
    glLoadIdentity();


    // Viewport
    // // TODO Essayez de modifier l'appel à glViewport
    // en changeant les parametre d'appel a la fonction mais
    // tout en obtenant le meme resultat
    glViewport(0, 0, windowW, windowH);

    // Mise en place de la perspective
    // TODO : peut-on changerle ratio ici pour un meilleur resultat ?
    gluPerspective(focale, 4 / 3.0, near1, far1);

    // Placement de la caméra
    gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

    // Retourne a la pile modelview
    glMatrixMode(GL_MODELVIEW);
}

void LoadOBJ(const char* filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        iss >> token;

        if (token == "v") {
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
          /*  cout << vertex.x << vertex.y << vertex.z << endl;*/
            vertices.push_back(vertex);
        }
        else if (token == "f") {
            Face face;
            char c ='non';
            iss >> face.v1;

            while ( c != '/') {
                iss.get(c);
            }
            iss.ignore();
            while (c != '/') {
                iss.get(c);
            }
            iss.ignore();
            while (c!= ' ') {
                iss.get(c);
            }
            iss.ignore();
           
            iss >> face.v2;

            while (c != '/') {
                iss.get(c);
            }
            iss.ignore();
            while (c != '/') {
                iss.get(c);
            }
            iss.ignore();
            while (c != ' ') {
                iss.get(c);
            }
            iss.ignore();

            iss >> face.v3;
   
            faces.push_back(face);
            /*cout << face.v1 << " " << face.v2 <<" " << face.v3 << endl;*/
   
        }
        else if (token == "vn") {
            // Handle vertex normals (if needed)
            // You can parse and store them in a similar way as vertices
        }
        else if (token == "vt") {
            // Handle texture coordinates (if needed)
            // You can parse and store them in a similar way as vertices
        }
    }
    file.close();
}
void PrintVerticesAndFaces() {
    // Print vertices
    std::cout << "Vertices:" << std::endl;
    for (size_t i = 0; i < vertices.size(); ++i) {
        std::cout << "Vertex " << i + 1 << ": " << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << std::endl;
    }

    // Print faces
    std::cout << "Faces:" << std::endl;
    for (size_t i = 0; i < faces.size(); ++i) {
        std::cout << "Face " << i + 1 << ": " << faces[i].v1 << " " << faces[i].v2 << " " << faces[i].v3 << std::endl;
    }
}
int FindMaxFaceComponent() {
    int maxComponent = 0;

    for (const Face& face : faces) {
        if (face.v1 > maxComponent) {
            maxComponent = face.v1;
        }
        if (face.v2 > maxComponent) {
            maxComponent = face.v2;
        }
        if (face.v3 > maxComponent) {
            maxComponent = face.v3;
        }
    }

    return maxComponent;
}

int main(int argc, char* argv[])
{
    
    LoadOBJ("Modele/icosphere.obj");
    PrintVerticesAndFaces();
    cout << endl <<FindMaxFaceComponent()<<endl;
    // Initialisation de GLUT
    glutInit(&argc, argv);
    // Choix du mode d'affichage (ici RVB)
    //glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // Position initiale de la fenetre GLUT
    glutInitWindowPosition(200, 200);
    // Taille initiale de la fenetre GLUT
    glutInitWindowSize(windowW, windowH);
    // Creation de la fenetre GLUT
    glutCreateWindow("carré");

    // Définition de la couleur d'effacement du framebuffer
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


    // Blend ?
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Définition des fonctions de callbacks
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);

    glutReshapeFunc(redimensionner);

    // Lancement de la boucle infinie GLUT
    glutMainLoop();

    delete[] image;

    return 0;
}










