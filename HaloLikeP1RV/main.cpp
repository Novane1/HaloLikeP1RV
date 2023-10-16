//Librairies
#include "windows.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <GL/gl.h>
//#include <glut.h>
#include "Camera.h"
//#include "Vector3.h"
#include "Geometry.h"
#include <GLFW/glfw3.h>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "Objet3D.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


using namespace std;

// VARIABLES GLOBALES
int width, height, channels;
Objet3D player;

vector<Vertex> vertices;
vector<Face> faces;
vector<Tex> texture;

bool red = true;
bool blue = true;
GLdouble SPEED = .03;
GLdouble strafeSpeed = 0.01;
GLdouble walkSpeed = 0.03;
GLdouble runSpeed = 0.1;
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
Camera camera; //Définition de la caméra


// Taille de la fenêtre
int windowW = 640;
int windowH = 480;
float focale = 65.0f;
float near1 = 0.1f;
float far1 = 100.0f;


GLvoid clavier(GLFWwindow* window, int key, int scancode, int action, int mods) { // récupère un input clavier dans touche, (x,y) donne les coord. de la souris
    if ((scancode == glfwGetKeyScancode(GLFW_KEY_LEFT_SHIFT)) && !(action == GLFW_RELEASE))
    {
        SPEED = runSpeed;
    }
    if ((scancode == glfwGetKeyScancode(GLFW_KEY_LEFT_SHIFT)) && (action == GLFW_RELEASE))
    {
        SPEED = walkSpeed;
    }
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
        dX = strafeSpeed;
    }
    if ((scancode == glfwGetKeyScancode(GLFW_KEY_A)) && (action == GLFW_RELEASE)) {
        dX = 0;
    }

    if ((scancode == glfwGetKeyScancode(GLFW_KEY_D)) && !(action == GLFW_RELEASE)) {
        dX = -strafeSpeed;
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


void LoadOBJ(const char* filename, Objet3D& obj) { // Load un objet .obj avec des faces triangulaires
    std::ifstream file(filename);
    std::string line;
    vector<Vertex> vertices;
    vector<Face> faces;
    vector<Tex> texture;
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
        else if (token == "f") { // format du type f x/y/z x/y/z x/y/z, où seul les x et y nous interesse. 
            
            // il s'agit de tout les triplets de points formant des triangles
            Face face;
            char c ='non';
            iss >> face.v1;
            //passer au point suivant, en évitant le vecteur  normal
            while ( c != '/') { iss.get(c); } 
            iss >> face.vt1;
            
            while (c != '/') { iss.get(c); } 
            while (c!= ' ') { iss.get(c); }

            iss >> face.v2;
            // ...
            while (c != '/') { iss.get(c); }
            iss >> face.vt2;
            
            while (c != '/') { iss.get(c); }
            while (c != ' ') { iss.get(c); }
            
            iss >> face.v3;
            while (c != '/') { iss.get(c); }
            iss >> face.vt3;
            
            faces.push_back(face);
        } 
        else if (token == "vn") {
            //pas utile pour l'instant
        }
        // Coordonnées de texture
        else if (token == "vt") { 
            Tex tex;
            iss >> tex.v1 >> tex.v2;
             tex.v2 = 1.0 - tex.v2;
            texture.push_back(tex);
        }
    }
    file.close();
    obj.setVertices(vertices);
    obj.setFaces(faces);
    obj.setTextureCoord(texture);
}

////          MAIN()



////////////////////////////////////////////////////

 /// Function to load a texture from a file
void LoadTexture(const char* path, Objet3D &obj) {
    // Load the image using STB Image
    int width, height, channels;
    unsigned char* image = stbi_load(path, &width, &height, &channels, 0);

    if (!image) {
        std::cout << "Failed to load texture: " << path << std::endl;
        return ;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters for basic rendering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Load the image data into the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    // Free the image data
    stbi_image_free(image);
    Texture texture;
    texture.setID(textureID);
    obj.setTexture(texture);
}

int main() {
    // Initialize GLFW
    
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Texture Example", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, clavier);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, souris_au_centre);
    // Load the texture
    LoadTexture("zelda.png",player);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/helmet.obj");
    LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/zelda.obj",player);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, 800.0f / 600.0f, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        camera.updateCamera();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Enable texturing
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, player.getTexture().getID());

        /*glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
        glEnd();*/

        player.affichage();

        camera.goFrontCamera(dZ);
        camera.goSideCamera(dX);
        glDisable(GL_TEXTURE_2D);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glfwTerminate();

    return 0;
}