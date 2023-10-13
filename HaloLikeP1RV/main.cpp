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
#include "stb_image.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"


using namespace std;


//variables utiles
vector<Vertex> vertices;
vector<Face> faces;
unsigned char* image;
bool red = true;
bool blue = true;
GLdouble SPEED = .05;
GLdouble mouseSensitivityAngle = .002;
GLdouble actualAngleX = 3.141592/2;
GLdouble actualAngleY = 0;
const GLdouble minYAngle = -3.141592 / 2.0; // Minimum angle (e.g., -90 degrees)
const GLdouble maxYAngle = 3.141592 / 2.0;
float oldMouseX = -1;
float oldMouseY = -1;
float xOffset = 0;
float yOffset = 0;
float dX = 0; // décalage selon l'axe X en déplacement
float dZ = 0;// décalage selon l'axe Z en déplacement
glm::mat4 view; // matrice de vue
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

        //glColor3f(vertices[face.v1 - 1].r, vertices[face.v1 - 1].v, vertices[face.v1 - 1].b);
        glVertex3f(vertices[face.v1 - 1].x, vertices[face.v1 - 1].y, vertices[face.v1 - 1].z);
        //glColor3f(vertices[face.v2 - 1].r, vertices[face.v2 - 1].v, vertices[face.v2 - 1].b);
        glVertex3f(vertices[face.v2 - 1].x, vertices[face.v2 - 1].y, vertices[face.v2 - 1].z);
        //glColor3f(vertices[face.v3 - 1].r, vertices[face.v3 - 1].v, vertices[face.v3 - 1].b);
        glVertex3f(vertices[face.v3 - 1].x, vertices[face.v3 - 1].y, vertices[face.v3 - 1].z);        
    }

    camera.goFrontCamera(dZ);
    camera.goSideCamera(dX);

    glEnd();
}

GLvoid clavier(GLFWwindow* window, int key, int scancode, int action, int mods) { // récupère un input clavier dans touche, (x,y) donne les coord. de la souris

    if((scancode== glfwGetKeyScancode(GLFW_KEY_W))&&!(action==GLFW_RELEASE)){ // avance  
        dZ = -SPEED;
    }
    if ((scancode == glfwGetKeyScancode(GLFW_KEY_W)) && (action == GLFW_RELEASE)) { // avance
        dZ = 0;
    }

    if ((scancode == glfwGetKeyScancode(GLFW_KEY_S)) && !(action == GLFW_RELEASE)) { // recule
        dZ = SPEED;
    }
    if ((scancode == glfwGetKeyScancode(GLFW_KEY_S)) && (action == GLFW_RELEASE)) { // recule
        dZ = 0;
    }

    if ((scancode == glfwGetKeyScancode(GLFW_KEY_A)) && !(action == GLFW_RELEASE)) {
        dX = SPEED;
    }
    if ((scancode == glfwGetKeyScancode(GLFW_KEY_A)) && (action == GLFW_RELEASE)) {
        dX = 0;
    }

    if ((scancode == glfwGetKeyScancode(GLFW_KEY_D)) && !(action == GLFW_RELEASE)) {
        dX = -SPEED;
    }
    if ((scancode == glfwGetKeyScancode(GLFW_KEY_D)) && (action == GLFW_RELEASE)) {
        dX = 0;
    }

}
GLvoid souris_au_centre(GLFWwindow* window, double xpos, double ypos)
{
    xOffset = xpos - oldMouseX;
    yOffset = oldMouseY - ypos;
    oldMouseX = xpos;
    oldMouseY = ypos;
    camera.updateRotation(xOffset, yOffset, mouseSensitivityAngle,actualAngleX,actualAngleY);
}

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
            iss >> vertex.x >> vertex.y >> vertex.z; //>> vertex.r >> vertex.v >> vertex.b;
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

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    } 

    LoadOBJ("C:/Users/Eleve/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/sword.obj");
   


    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Cube Example", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, clavier);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, souris_au_centre);

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

   
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 800, 600);

    // Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    // Main loop
    while (!glfwWindowShouldClose(window)) {

        
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        camera.updateCamera();


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        affichage(); // affiche ma scène



        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}