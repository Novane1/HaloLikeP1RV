//Librairies
#include "windows.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <GL/gl.h>
#include <glut.h>
#include "Camera.h"
#include "Vector3.h"

using namespace std;

//structures utiles

struct Vertex {
    float x, y, z;
};

struct Face {
    int v1, v2, v3;
};

//variables utiles
vector<Vertex> vertices;
vector<Face> faces;
unsigned char* image;
GLfloat pointSize = 5.0f;
GLint typeForme = 0;
bool red = true;
bool blue = true;
GLdouble SPEED = .1;

//Définition de la cméra
Camera camera;



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

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT); 

    glBegin(GL_TRIANGLES);
    for (const Face& face : faces) {
       
        glVertex3f(vertices[face.v1 - 1].x, vertices[face.v1 - 1].y, vertices[face.v1 - 1].z);
        glVertex3f(vertices[face.v2 - 1].x, vertices[face.v2 - 1].y, vertices[face.v2 - 1].z);
        glVertex3f(vertices[face.v3 - 1].x, vertices[face.v3 - 1].y, vertices[face.v3 - 1].z);
        
    }
    glEnd();
    glFlush();
    glutSwapBuffers();

    
}


GLvoid clavier(unsigned char touche, int x, int y) {


    switch (touche) {

    case 's' :
        camera.goFrontCamera(SPEED);
        break;

    case 'z':
        camera.goFrontCamera(-SPEED);
        break;

    case 'q': // quitter
    case 27:
        exit(0);
        break;
    }
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



    glViewport(0, 0, windowW, windowH);

    // Mise en place de la perspective

    gluPerspective(focale, float(windowW) / float(windowH), near1, far1);

    // Placement de la caméra
    camera.updateCamera();

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

        if (token == "v") { // on ajoute un format du type v x y z
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        }
        else if (token == "f") { // format du type f x/y/z x/y/z x/y/z, où seul les x nous interesse. 
            // il s'agit de tout les triplets de points formant des triangles

            Face face;
            char c ='non';
            iss >> face.v1;

            while ( c != '/') {
                iss.get(c);
            }
            
            while (c != '/') {
                iss.get(c);
            }
            
            while (c!= ' ') {
                iss.get(c);
                
            }

            
           
            iss >> face.v2;

            while (c != '/') {
                iss.get(c);
            }
            
            while (c != '/') {
                iss.get(c);
            }
            
            while (c != ' ') {
                iss.get(c);
            }
            

            iss >> face.v3;
   
            faces.push_back(face);

   
        }
        else if (token == "vn") {
            //pas utile pour nous
        }
        else if (token == "vt") {
            // idem
        }
    }
    file.close();
}


int main(int argc, char* argv[])
{
   
    LoadOBJ("Modele/icosphere.obj");
  
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


    // Blend
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Définition des fonctions de callbacks
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);

    glutReshapeFunc(redimensionner);

    // Lancement de la boucle infinie GLUT
    glutMainLoop();



    return 0;
}










