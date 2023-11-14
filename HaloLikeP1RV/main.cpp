//Librairies
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "UI.h"
#include <glut.h>
#include "Camera.h"
#include "Geometry.h"
#include "Shader.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "Objet3D.h"
#include "Player.h"
#include "rayon.h"
#include "Shader.h"
#include "Ennemi.h"
#include <GLFW/glfw3.h>

using namespace std;

// VARIABLES GLOBALES

#define _HEIGHT 4.0

int width, height, channels;
//Objets
Ennemi player(1.0f,20.0f);
Player testPlayer;
Objet3D playerObj;
UI listUI;
Objet3D gun;
Objet3D second;
Objet3D knifeHandle;
Objet3D knifeBlade;
Objet3D glove;
// TEST NAVMESH
Objet3D monde;
Objet3D navMesh;
Objet3D skybox;
//Debug
glm::vec3 previousCam(0, 0, 0);
// FIN TEST
//Variables main
vector<Vertex> vertices;
vector<Face> faces;
vector<Tex> texture;
bool red = true;
bool blue = true;
GLdouble SPEED = .03;
GLdouble strafeSpeed = 0.02;
GLdouble walkSpeed = 0.03;
GLdouble runSpeed = 0.05;
GLdouble mouseSensitivityAngle = .002;
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
std::vector<bool> keys(GLFW_KEY_LAST, false);
std::vector<bool> mouseClick(2, false);
bool shouldExit = false;
vector<Collider*> otherCollider; // everything but the camera's collider

GLvoid mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        mouseClick[0] = true;
        // Il faut faire des dégats sur ennemi
        //////////////////////////////////////////
        for (vector<Ennemi*>::iterator it = player.listEnnemi.begin(); it != player.listEnnemi.end(); it++) {
            if ((*it)->isShot(camera.getPosition(), glm::normalize(camera.getTarget() - camera.getPosition()))) {
                cout << (*it)->addHealth(-5) << endl;
                if ((*it)->getHealth() <= 0) { 
                    // Le buter 
                }
            }
        }
        
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        mouseClick[0] = false;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        mouseClick[1] = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        mouseClick[1] = false;
    }
}
GLvoid keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key >= 0 && key < GLFW_KEY_LAST) {
        if (action == GLFW_PRESS) {
            // Set the flag for the pressed key to true.
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE) {
            // Set the flag for the released key to false.
            keys[key] = false;
        }
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        // Set a flag or perform some action to exit the application
        shouldExit = true;
    }
}
GLvoid clavier() { 

    if (keys[GLFW_KEY_LEFT_SHIFT]) { SPEED = runSpeed; }
    else { SPEED = walkSpeed; }
    
    if (keys[GLFW_KEY_W]) { dZ = -SPEED; }
    else {
        if (keys[GLFW_KEY_S]) { dZ = SPEED; }
        else { dZ = 0; }
    }


    if (keys[GLFW_KEY_A]) { dX = strafeSpeed; }
    else {
        
        if (keys[GLFW_KEY_D]) { dX = -strafeSpeed; }
        else { dX = 0; }
    }
    if (keys[GLFW_KEY_C]) { camera.changeState(false, 0); camera.changeState(true, 1); camera.changeState(true, 2); camera.changeState(true, 3); }
    if (keys[GLFW_KEY_Z]) { camera.changeState(true, 0); camera.changeState(false, 1); camera.changeState(false, 2); camera.changeState(false, 3); }

    if (keys[GLFW_KEY_SPACE]) {
        camera.setJump();
    }

}
GLvoid souris_au_centre(GLFWwindow* window, double xpos, double ypos)
{
    xOffset = xpos - oldMouseX;
    yOffset = oldMouseY - ypos;
    oldMouseX = xpos;
    oldMouseY = ypos;
    camera.updateRotation(xOffset, yOffset, mouseSensitivityAngle);
}


GLfloat Norme(glm::vec3 vec1, glm::vec3 vec2) {
    GLfloat n; 
    // TODO
    return 0.0;
}


int main() {
    // Initialize GLFW
    
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    //// Create a GLFW window
    //GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    //// Get the video mode of the monitor
    //const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    //// Create a fullscreen window
    //GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Fullscreen Game", monitor, NULL);
    GLFWwindow* window = glfwCreateWindow(800, 600, "My GLFW Window", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Shader shader(vertexShaderSource, fragmentShaderSource);
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        // Handle error
        glfwTerminate();
        return -1;
    }
   
    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, souris_au_centre);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    // LOAD OBJETS DE JACOB
    /*monde.LoadOBJ("C:/Users/jaco2/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/map.obj");
    navMesh.LoadOBJ("C:/Users/jaco2/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/navMesh.obj");
    
    player.LoadTexture("zelda.png");
    player.LoadOBJ("C:/Users/jaco2/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/zelda.obj");

    knifeHandle.LoadTexture("knifeHandle.png");
    knifeHandle.LoadOBJ("C:/Users/jaco2/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/knifeHandle.obj");

    knifeBlade.LoadTexture("knifeBlade.png");
    knifeBlade.LoadOBJ("C:/Users/jaco2/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/knifeBlade.obj");

    glove.LoadTexture("glove.png");
    glove.LoadOBJ("C:/Users/jaco2/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/glove.obj");*/
    // FIN LOAD

    //// LOAD OBJETS DE NATHAN
    monde.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/map.obj");

    navMesh.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/map.obj");
    monde.LoadTexture("Terrain.png");

    skybox.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/skybox.obj");

    
    player.LoadTexture("zelda.png");
    player.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/zeldo.obj");
    player.LoadCOllider("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/zeldoCollider.obj");
    otherCollider.push_back(player.getCollider());
    knifeHandle.LoadTexture("knifeHandle.png");
    knifeHandle.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/knifeHandle.obj");

    knifeBlade.LoadTexture("knifeBlade.png");
    knifeBlade.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/knifeBlade.obj");

    glove.LoadTexture("glove.png");
    glove.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/glove.obj");
    camera.setCollider("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/cameraCollider.obj");
    ///Load objet ECN
   /* monde.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/map.obj");

    navMesh.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/map.obj");
    monde.LoadTexture("Terrain.png");

    skybox.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/skybox.obj");

    gun.LoadTexture("gun.png");
    gun.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/gun.obj");


    player.LoadTexture("zelda.png");
    player.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/zelda.obj");

    knifeHandle.LoadTexture("knifeHandle.png");
    knifeHandle.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/knifeHandle.obj");

    knifeBlade.LoadTexture("knifeBlade.png");
    knifeBlade.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/knifeBlade.obj");

    glove.LoadTexture("glove.png");
    glove.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/glove.obj");*/
    //// FIN LOAD


    listUI.AddObject(gun);
    listUI.AddObject(knifeHandle);
    listUI.AddObject(knifeBlade);
    listUI.AddObject(glove);
    //
    camera.setUI(listUI);
    camera.changeState(0, false);
    camera.setPlayer(testPlayer);
  
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    
    // Shader in CG
    const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    out vec2 TexCoord;
    void main() {
        gl_Position =   projection *view *model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
    }
)";


    const char* fragmentShaderSource = R"(
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D texture1; // Texture unit

    void main() {

    vec4 texColor = texture(texture1, TexCoord); 
    vec4 redColor = vec4(1.0, 0.0, 0.0, 1.0); // Red color

    float blendFactor = 0.5; // You can change this value

    FragColor = mix(texColor, redColor, blendFactor);
    }
)";

    const char* vertexShaderSourceSkyBox = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    out vec2 TexCoord;
    out vec3 pos;
    void main() {
        gl_Position =   projection *view *model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
    pos = aPos;
    }
)";


    const char* fragmentShaderSourceSkyBox = R"(
    #version 330 core

    out vec4 FragColor;
    in vec3 pos;
    const vec4 skytop = vec4(0.0f, 0.0f, 1.0f, 1.0f);
    const vec4 skyhorizon = vec4(0.3294f, 0.92157f, 1.0f, 1.0f);
   
    void main() {
        vec3 pointOnSphere = normalize(pos);
        float a = pointOnSphere.y;

        FragColor =mix(skyhorizon, skytop, a);
       
    }
)";

    /*const vec4 skytop = vec4(0.0f, 0.0f, 1.0f, 1.0f);
    const vec4 skyhorizon = vec4(0.3294f, 0.92157f, 1.0f, 1.0f);
    vec4 pointOnSphere = normalize(pos);
    float a = pointOnSphere.y;
    FragColor = mix(skyhorizon, skytop, a);*/
    Shader redDamageShader(vertexShaderSource, fragmentShaderSource);
    Shader skyboxShader(vertexShaderSourceSkyBox, fragmentShaderSourceSkyBox);
    
    rayon downSnap(navMesh.getvraiFaces()); // Initalisation du rayon de projection pour la coordonnée en y
    glm::vec3 intersection(0.0f);

    while (!glfwWindowShouldClose(window)) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        camera.updateCamera();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Enable texturing

        glEnable(GL_TEXTURE_2D);

        clavier();

        monde.affichage(); // TEST NAVMESH
        player.affichageShader(redDamageShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0));

        camera.affichageUI(keys, mouseClick);

        skybox.affichageSkybox(skyboxShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0));
        



        glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glDisable(GL_DEPTH_TEST);
        glTranslatef(0, 0, -100); // Placement du point de visée
        GLUquadricObj* quadric = gluNewQuadric();
        gluPartialDisk(quadric, 0.0, 1.0, 100, 1, 0.0, 360.0);
        glEnable(GL_DEPTH_TEST);
        glPopMatrix();
        
        

        camera.goFrontCamera(dZ,otherCollider);
        camera.goSideCamera(dX,otherCollider);

        intersection = downSnap.ptIntersectionF(camera.getPosition());

        if (intersection != glm::vec3{ -100,-100,-100 })
        {

            if (!camera.isJumping())
            {
                camera.sethauteur(intersection, _HEIGHT);
            }

        }

           
       
        
       
            
        camera.updateJump(intersection.y);
        
        glDisable(GL_TEXTURE_2D);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Exit on Echap
        if (shouldExit) {
            break;
        }
    }

    // Clean up
    glfwTerminate();

    return 0;
}