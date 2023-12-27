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
#include "al.h"
#include "alc.h"
#include "AudioManager.h"
#include "Crosshair.h"
#include "ShootBar.h"
#include "ReloadManager.h"
#include "World.h"
#include "PatternManager.h"
#include "MovementManager.h"
using namespace std;

// VARIABLES GLOBALES

#define _HEIGHT 4.0
int width, height, channels;
//Objets

Ennemi player(1.0f,50.0f); // main ennemi
Objet3D diamond; // useless rn
UI listUI; // List of our UI object
Objet3D smog; // Orb to get back our ammo
Objet3D gun; // gun
Objet3D heart; // hearth that simbolie health of our player
Objet3D knifeHandle; // Part of our knife
Objet3D knifeBlade;// Part of our knife
Objet3D glove;// Part of our knife
Objet3D spawnPoints; // spawn points for our "smog" (so ammo)
Objet3D monde; // world
Objet3D navMesh; // navmesh for player to travel in
Objet3D skybox; // skybox
Objet3D meteor; // meteor for the ennemi's attack
Objet3D death; //death screen


// FIN TEST
//Variables main
AudioManager* audioManager = new AudioManager(); // To put music
//All of our speed
GLdouble SPEED = .07;
GLdouble strafeSpeed = 0.05;
GLdouble walkSpeed = 0.05;
GLdouble runSpeed = 0.11;
//End of our speeds
GLdouble mouseSensitivityAngle = .002; // Sensitivity for mouse
const GLdouble minYAngle = -3.141592 / 2.0; // Minimum angle (e.g., -90 degrees)
const GLdouble maxYAngle = 3.141592 / 2.0;
float oldMouseX = -1; //Old mouse X coordonate
float oldMouseY = -1; //Old mouse Y coordonate
float xOffset = 0; // X Offset between actual mouse coordonate and previous one
float yOffset = 0; // Y Offset between actual mouse coordonate and previous one
float dX = 0; // X Axis offset for mooving
float dZ = 0; // Y Axis offset for mooving
Camera camera; //Définition de la caméra
//Window parameters
int windowW = 640;
int windowH = 480;
float focale = 65.0f;
float near1 = 0.1f;
float far1 = 100.0f;
//End of window parameters
std::vector<bool> keys(GLFW_KEY_LAST, false); // Vector to know the state of our keyboard's keys
std::vector<bool> mouseClick(2, false); // // Vector to know the state of our mous's keys
bool shouldExit = false; // Condition to exit main game
vector<Objet3D*> otherEnnemiCollider; // everything but the camera's collider
Crosshair crosshair; //Crosshair
ShootBar shootBar; // Amo counter bar



GLvoid mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        mouseClick[0] = true; // changing the state of our mouse key
        if (camera.getUI().isGun()) {
            shootBar.downAmo(); // We drop some ammo
        }
        
        if (camera.getUI().isGun()) {
            audioManager->playSong(1); // Shoot sound
        }
        // We need to apply damage
        //////////////////////////////////////////
        if (shootBar.getAmo() > 0)// Do we have enough ammo?
        {
            float temp;
            for (vector<Ennemi*>::iterator it = player.listEnnemi.begin(); it != player.listEnnemi.end(); it++) {
                temp = (*it)->isShot(camera.getPosition(), glm::normalize(camera.getTarget() - camera.getPosition()));
               
                
                    if ((camera.getUI().isKnife()&& temp > 0 && temp < 6.0f)|| (camera.getUI().isGun()&&temp!=0))
                    {
                        
                        (*it)->addHealth(-5);
                        (*it)->startDamageAnimation();
                        if ((*it)->getHealth() <= 0) {
                            (*it)->setActive(false);

                        }
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
        /// Audio
   // Initialize OpenAL


   
    const char* dsmusic = "dsmusic.wav";
    const char* laser = "laser.wav";
    audioManager->AddSong(dsmusic,0.3f);
    audioManager->AddSong(laser,1.0f);

    // Play the source
    


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
   /* GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Fullscreen Window", monitor, NULL);*/
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
    death.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/death.obj");
    death.LoadTexture("death.jpg");

    monde.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/map.obj");
    spawnPoints.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/spawnPoints.obj");

    navMesh.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/map.obj");
    navMesh.LoadTexture("Terrain.png");
    monde.LoadTexture("Terrain.png");
    heart.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/heart.obj");
    skybox.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/skybox.obj");

    
    player.LoadTexture("zelda.png");
    player.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/zeldo.obj");
    player.LoadCOllider("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/zeldoCollider.obj");
    otherEnnemiCollider.push_back(&player);
    knifeHandle.LoadTexture("knifeHandle.png");
    knifeHandle.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/knifeHandle.obj");

    knifeBlade.LoadTexture("knifeBlade.png");
    knifeBlade.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/knifeBlade.obj");

    glove.LoadTexture("glove.png");
    glove.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/glove.obj");
    camera.setCollider("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/cameraCollider.obj");

    meteor.LoadTexture("meteor.png");
    meteor.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/meteor.obj");
    meteor.LoadCOllider("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/meteorCollider.obj");
    otherEnnemiCollider.push_back(&meteor);

    smog.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/smog.obj");
   
    ///Load objet ECN
    /*death.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/death.obj");
    death.LoadTexture("death.jpg");

    monde.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/map.obj");
    spawnPoints.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/spawnPoints.obj");

    navMesh.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/map.obj");
    monde.LoadTexture("Terrain.png");

    skybox.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/skybox.obj");

    gun.LoadTexture("gun.png");
    gun.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/gun.obj");

 
    heart.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/heart.obj");



    player.LoadTexture("zelda.png");
    player.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/zeldo.obj");
    player.LoadCOllider("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/zeldoCollider.obj");
    otherEnnemiCollider.push_back(&player);

    knifeHandle.LoadTexture("knifeHandle.png");
    knifeHandle.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/knifeHandle.obj");

    knifeBlade.LoadTexture("knifeBlade.png");
    knifeBlade.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/knifeBlade.obj");

    glove.LoadTexture("glove.png");
    glove.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/glove.obj");
    camera.setCollider("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/cameraCollider.obj"); 

    meteor.LoadTexture("meteor.png");
    meteor.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/meteor.obj");
    meteor.LoadCOllider("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/meteorCollider.obj");
    otherEnnemiCollider.push_back(&meteor);

    smog.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/smog.obj");

    diamond.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/Diamond.obj");
    diamond.LoadTexture("Diamond.jpg");*/
    //// FIN LOAD

    

    listUI.AddObject(gun);
    listUI.AddObject(knifeHandle);
    listUI.AddObject(knifeBlade);
    listUI.AddObject(glove);
    listUI.AddObject(heart);
    listUI.AddObject(death);
    listUI.changeState(false, 0);
    listUI.changeState(false,5);
    camera.setUI(listUI);
   
    PatternManager pMeteor(&meteor);
    
    MovementManager movManager(&player);

    
  
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, 800.0f / 600.0f, 0.1f, 10000.0f);
    
    // Shader in CG
    const char* vertexShaderSourceBase = R"(
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

    

    const char* fragmentShaderSourceBase = R"(
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D texture1; // Texture unit

    void main() {


    vec4 texColor = texture(texture1, TexCoord); 
    

    FragColor = texColor;
    }
)";





    const char* vertexShaderSourceBaseP = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    uniform float closeRange;
    out float outCloseRange;
    out vec2 TexCoord;
    void main() {
        gl_Position =   projection *view *model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
        outCloseRange = closeRange;
    }
)";



    const char* fragmentShaderSourceBaseP = R"(
    #version 330 core
    in vec2 TexCoord;
    in float outCloseRange;
    out vec4 FragColor;
    

    uniform sampler2D texture1; // Texture unit

    void main() {

    vec4 texColor = texture(texture1, TexCoord); 
    
    texColor.a = outCloseRange;
    FragColor = texColor;
    }
)";


    const char* vertexShaderSourceAlpha = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    out vec2 TexCoord;
    void main() {
        gl_Position =   model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
    }
)";
    const char* fragmentShaderSourceAlpha = R"(
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D texture1; // Texture unit

    void main() {

    vec4 texColor = texture(texture1, TexCoord); 
    texColor.a = 0.7f;

    FragColor = texColor;
    }
)";










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
    const vec4 skytop =vec4(0.0f, 0.0f, 0.2f, 1.0f); 
    const vec4 skyhorizon = vec4(1.0f, 0.5f, 0.0f, 1.0f);
   
    void main() {
        vec3 pointOnSphere = normalize(pos);
        float a = min(pointOnSphere.y+0.8,1.0);

        FragColor =mix(skyhorizon, skytop, a);
       
    }
)";

    const char* vertexShaderSourceHealth = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    layout(location = 2) in vec3 normal;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    out vec2 TexCoord;
    out vec3 pos;
    out vec3 norm;
    void main() {
        gl_Position =   model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
        pos = vec3(model * vec4(aPos, 1.0));
        norm = normal;
    }
)";


    const char* fragmentShaderSourceHealth = R"(
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;
    in vec3 pos;
    in vec3 norm;
    uniform sampler2D texture1; // Texture unit

    void main() {
        vec3 redColor = vec3(1.0, 0.0, 0.0);

    
        vec3 norma = normalize(norm);
        vec3 lPos = vec3(5,5,0);
        vec3 lightDir = normalize(pos - vec3(0,5,0));
        float diff = max(max(dot(norma, lightDir),0),0.4);
        vec3 diffuse = diff * redColor;

        FragColor =vec4(diffuse, 1.0);
        
    }
)";


    const char* vertexShaderSourceSmog = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    layout(location = 2) in vec3 normal;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    out vec2 TexCoord;
    out vec3 pos;
    out vec3 norm;



    void main() {
        gl_Position =   projection * view * model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
        pos = vec3(model * vec4(aPos, 1.0));
        norm = normal;
    }
)";


    const char* fragmentShaderSourceSmog = R"(
    #version 330 core

    out vec4 FragColor;
    in vec3 pos;


float rand(vec2 co) {
        return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
    }
    void main() {
         vec3 pointOnSphere = normalize(pos);

        // Adjust the frequency and amplitude for the noise pattern
        float frequency = 5.0;
        float amplitude = 1.0;

        // Generate noise for the electricity pattern
        float noise = rand(pos.xy * frequency);

        // Create a sine function for periodic variation
        float sineFactor = sin(pos.y * 10.0);

        // Combine noise and sine function for variation
        float electricityPattern = noise + sineFactor;

        // Adjust the color based on the position along the electricity
        vec3 electricityColor = vec3(0.0, 1.0, 1.0); // Adjust color as needed
        electricityColor *= mix(0.2, 1.0, abs(pos.y));

        // Calculate the final color using the combined pattern and base color
        vec3 finalColor = electricityColor * electricityPattern * amplitude;

        // Add some brightness to enhance the effect
        finalColor += vec3(0.2);

        FragColor = vec4(finalColor, 1.0);
        
    }
)";


    const char* vertexShaderSourceGround = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    uniform vec3 meteorPos;
    uniform vec3 bossPos;
    uniform float longRadius;
    uniform float t;
    uniform float closeRadius;
    out float outCloseRadius;
    out vec2 TexCoord;
    out vec3 pos;
    out float outLongRadius;
    out float outT;
    out vec3 metPos;
    out vec3 bPos;
    void main() {
        gl_Position =   projection *view *model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
        pos = vec3(model * vec4(aPos, 1.0)); 
        outT = t;
        metPos = meteorPos;
        bPos = bossPos;
        outLongRadius = longRadius;
        outCloseRadius = closeRadius;
    }
)";


    const char* fragmentShaderSourceGround = R"(
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;
    in float outT;
    in vec3 metPos;
    in vec3 pos;
    in vec3 bPos;
    in float outLongRadius;
    in float outCloseRadius;
    uniform sampler2D texture1; // Texture unit

    void main() {
    float x = outT;
    float distanceToCenter = length(pos.xz - metPos.xz);
    float distanceToBoss = length(pos.xz - bPos.xz);
    vec4 texColor = texture(texture1, TexCoord); 
    vec4 darkEarthBrown = vec4(0.4, 0.2, 0.1,1.0); 
 vec4 orangeColor = vec4(0.7f, 0.35f, 0.0f,1.0f); // Red color
vec4 redColor = vec4(1.0f, 0.0f, 0.0f,1.0f); // Red color

    float blendFactor = 0.5; // You can change this value

    

     if (distanceToCenter <= x) {
        FragColor = mix(texColor, orangeColor, 0.7);

        } 
    else if (distanceToBoss<=outCloseRadius) {

            FragColor = mix(texColor, redColor, blendFactor);
        }
    else if (distanceToBoss>=outLongRadius && distanceToBoss<=(outLongRadius+1.0f) ) {

            FragColor = mix(texColor, redColor, blendFactor);
        }
    else{FragColor = mix(texColor, darkEarthBrown, blendFactor);}
    }
)";
   /* vec3 pointOnSphere = normalize(pos);
    float a = pointOnSphere.z;
    
    vec4 redColor = vec4(1.0, 0.0, 0.0, 1.0);
    vec4 redColorC = vec4(1.0, 0.2, 0.2, 1.0);
    FragColor = mix(redColorC, redColor, a);*/
    Shader redDamageShader(vertexShaderSource, fragmentShaderSource);
    Shader skyboxShader(vertexShaderSourceSkyBox, fragmentShaderSourceSkyBox);
    Shader healthShader(vertexShaderSourceHealth, fragmentShaderSourceHealth);
    Shader smogShader(vertexShaderSourceSmog, fragmentShaderSourceSmog);
    Shader groundShader(vertexShaderSourceGround, fragmentShaderSourceGround);
    Shader baseShader(vertexShaderSourceBase, fragmentShaderSourceBase);
    Shader alphaShader(vertexShaderSourceAlpha, fragmentShaderSourceAlpha);
    Shader playerShader(vertexShaderSourceBaseP, fragmentShaderSourceBaseP);
    // Initalisation du rayon de projection pour la coordonnée en y
    rayon downSnap(navMesh.getvraiFaces());
    glm::vec3 intersection(0.0f);

    // Lancement du OST original
    audioManager->playSong(0);

    ReloadManager reloadManager(smog, smogShader, spawnPoints.getvraiFaces(),&shootBar);


    while (!glfwWindowShouldClose(window)) {
        if (camera.getHealth() <= 0) 
        {
            glEnable(GL_BLEND);
            
            // Set the blending function
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glfwSetCursorPosCallback(window, nullptr);
            camera.changeState(false, 0);
            camera.changeState(false, 1);
            camera.changeState(false ,2);
            camera.changeState(false, 3);
            camera.changeState(false, 4);
            camera.changeState(true, 5);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_TEXTURE_2D);
            clavier();
            monde.affichageShader(groundShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0));
            skybox.affichageSkybox(skyboxShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0));
            camera.affichageUI(keys, mouseClick, healthShader,alphaShader);

            
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
            glfwSwapBuffers(window);
            glfwPollEvents();
            
        }
        else 
        {
            glEnable(GL_BLEND);

            // Set the blending function
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            camera.updateCamera();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Enable texturing

            glEnable(GL_TEXTURE_2D);

            clavier();



            ////monde.affichageShader(baseShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0));
            //if (!pMeteor.getIsActive()) {
            //    pMeteor.meteorAttack(glm::vec3(50),glm::vec3(-20));
            //}
            
            movManager.updatePos(camera, pMeteor);
            pMeteor.updateMeteor(baseShader, camera.getPosition(), camera.getTarget());
            
            monde.affichageGround(groundShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0), pMeteor.getT() * 10.0f , pMeteor.getActivePoint(),player.getPos(),movManager.getlongRadius(), movManager.getcloseRadius());
            float a = movManager.getCloseRange();

            if (a == 0) {
                a = 1.0f;
            }
            if (a >= 1) {
                a = 1.0f;
            }

            if ((player.getDamageFrame() / 10) % 2 == 0) 
            { 
               
                player.affichageShaderPlayer(playerShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0), player.getPos(),a);
            }
            else { player.affichageShaderPlayer(redDamageShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0), player.getPos(),a); }
           
           
            //meteor.affichage();
            camera.affichageUI(keys, mouseClick, healthShader,  alphaShader);
            
            skybox.affichageSkybox(skyboxShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0));
            if (camera.getUI().isGun()) {
                shootBar.affichage();
            }

            

            // Crosshair
            crosshair.affichageCrosshair();
            //reload
            reloadManager.actTime(camera.getPosition(), camera.getTarget());
            reloadManager.affichage(camera.getPosition(), camera.getTarget());
            //

            camera.go(dZ, dX, otherEnnemiCollider);
            /*camera.goFrontCamera(dZ, otherEnnemiCollider);
            camera.goSideCamera(dX, otherEnnemiCollider);*/


            // Intersection Joueur
            intersection = downSnap.ptIntersectionF(player.getPos());

            if (intersection != glm::vec3{ -100,-100,-100 })
            {
                
                 player.setPos(glm::vec3(player.getPos().x,intersection.y, player.getPos().z));
                 
                
            }
           

            // Intersection Ennemi
            intersection = downSnap.ptIntersectionF(camera.getPosition());

            if (intersection != glm::vec3{ -100,-100,-100 })
            {
                if (!camera.isJumping())
                {
                    camera.sethauteur(intersection, _HEIGHT);
                }
                
            }



            for (vector<Ennemi*>::iterator it = player.listEnnemi.begin(); it != player.listEnnemi.end(); it++) {
                (*it)->increaseDamageFrame();
            }


            camera.updateFrame();
            camera.updateJump(intersection.y);
            camera.updateCheckInvicibility();

            glDisable(GL_TEXTURE_2D);

            glfwSwapBuffers(window);
            glfwPollEvents();

        }
        
        // Exit on Echap
        if (shouldExit) {
            break;
        }
        glDisable(GL_BLEND);
        
    }



    
    // Clean up
    glfwTerminate();
    audioManager->destroy();
    return 0;
}