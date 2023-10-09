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
#include "Geometry.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;


//variables utiles
vector<Vertex> vertices;
vector<Face> faces;
unsigned char* image;
bool red = true;
bool blue = true;
GLdouble SPEED = 1;
GLdouble mouseSensitivityAngle = .005;
GLdouble actualAngleX = 3.141592/2;
GLdouble actualAngleY = 0;
float oldMouseX = -1;
float oldMouseY = -1;

//Définition de la cméra
Camera camera;



// Taille de la fenêtre
int windowW = 640;
int windowH = 480;
float focale = 65.0f;
float near1 = 0.1f;
float far1 = 100.0f;
//
//// Déclarations des fonctions de rappel (callbacks)
//GLvoid affichage();
//GLvoid clavier(unsigned char touche, int x, int y);
//
//GLvoid redimensionner(int w, int h);
//
//
//
//// Definition de la fonction d'affichage
GLvoid affichage() {
    
    
    glBegin(GL_TRIANGLES);
    for (const Face& face : faces) {// affichage de la scène
       
        glVertex3f(vertices[face.v1 - 1].x, vertices[face.v1 - 1].y, vertices[face.v1 - 1].z);
        glVertex3f(vertices[face.v2 - 1].x, vertices[face.v2 - 1].y, vertices[face.v2 - 1].z);
        glVertex3f(vertices[face.v3 - 1].x, vertices[face.v3 - 1].y, vertices[face.v3 - 1].z);
        
    }

    glEnd();

    
    


}
//
//
//GLvoid clavier(unsigned char touche, int x, int y) { // récupère un input clavier dans touche, (x,y) donne les coord. de la souris
//
//   
//    switch (touche) {
//
//    case 's' :
//        camera.goFrontCamera(SPEED);
//        break;
//
//    case 'z':
//        camera.goFrontCamera(-SPEED);
//        break;
//
//    case 'a':
//        camera.goSideCamera(-SPEED);
//        break;
//
//    case 'd':
//        camera.goSideCamera(SPEED);
//        break;
// 
//        
//    
//
//    //case 'q': // quitter
//    //case 27:
//    //    exit(0);
//    //    break;
//    }
//    glutPostRedisplay();
//    
//    
//
//}
//void souris(int button, int state, int x, int y){
//  //  if (button == GLUT_RIGHT_BUTTON)
//  //  {
//  //      camera.updateRotation(x, y, oldMouseX, oldMouseY, mouseSensitivityAngle);
//  //  }
//  ///*  ;*/
//  //  
//  //  oldMouseX = x;
//  //  oldMouseY = y;
//}
//void mouseMovement(int x, int y) {
//    /*if ((oldMouseX < 0) && (oldMouseY < 0))
//    {
//        oldMouseX = x;
//        oldMouseY = y;
//    }*/
//    camera.updateRotation(x, y, oldMouseX, oldMouseY, mouseSensitivityAngle,actualAngleX,actualAngleY);
//    oldMouseX = x;
//    oldMouseY = y;
//
//    camera.updateCamera();
//    glutPostRedisplay();
//}
//
//
//
//// Callback de redimensionnement de la fenêtre
//GLvoid redimensionner(int w, int h) {
//    // Garde les valeurs
//    windowW = w;
//    windowH = h;
//    // eviter une division par 0
//    if (windowH == 0)
//        windowH = 1;
//
//    float ratio = (float)windowW / (float)windowH;
//    std::cout << "Ratio : " << ratio << std::endl;
//
//    // Projection
//    glMatrixMode(GL_PROJECTION);
//
//    // Resetting matrix
//    glLoadIdentity();
//
//
//
//    glViewport(0, 0, windowW, windowH);
//
//    // Mise en place de la perspective
//
//    gluPerspective(focale, float(windowW) / float(windowH), near1, far1);
//
//    // Placement de la caméra
//    camera.updateCamera();
//
//    // Retourne a la pile modelview
//    glMatrixMode(GL_MODELVIEW);
//}
//
void LoadOBJ(const char* filename) { // Load un objet .obj avec des faces triangulaires
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
            //passer au point suivant, en éviant le vecteur de texture et normal
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
            // ...
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
            //pas utile pour l'instant
        }
        else if (token == "vt") {
            // idem
        }
    }
    file.close();
}


//int main(int argc, char* argv[])
//{
//   
//    LoadOBJ("Modele/icosphere.obj");
//
//    // Initialisation de GLUT
//    glutInit(&argc, argv);
//    // Choix du mode d'affichage (ici RVB)
//    //glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    // Position initiale de la fenetre GLUT
//    glutInitWindowPosition(200, 200);
//    // Taille initiale de la fenetre GLUT
//    glutInitWindowSize(windowW, windowH);
//    // Creation de la fenetre GLUT
//    glutCreateWindow("carré");
//
//    // Définition de la couleur d'effacement du framebuffer
//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//
//
//    // Blend
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    // Définition des fonctions de callbacks
//    glutDisplayFunc(affichage);
//    glutKeyboardFunc(clavier);
//    glutPassiveMotionFunc(mouseMovement);
//    glutReshapeFunc(redimensionner);
//    glutMouseFunc(souris);
//    // Lancement de la boucle infinie GLUT
//    glutMainLoop();
//
//
//
//    return 0;
//}



int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    } 
    LoadOBJ("Modele/icosphere.obj");

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Cube Example", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

   
    glEnable(GL_DEPTH_TEST);
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);


        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -5.0f);
    
        affichage();



        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}