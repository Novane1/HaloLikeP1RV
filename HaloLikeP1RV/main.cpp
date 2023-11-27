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
using namespace std;

// VARIABLES GLOBALES

#define _HEIGHT 4.0
// Function to check for OpenAL errors

int width, height, channels;
//Objets
Ennemi player(1.0f,50.0f);
Player testPlayer;
Objet3D playerObj;
Objet3D diamond;
UI listUI;
Objet3D smog;
Objet3D gun;
Objet3D heart;
Objet3D healthBar;
Objet3D second;
Objet3D knifeHandle;
Objet3D knifeBlade;
Objet3D glove;
Objet3D spawnPoints;
// TEST NAVMESH
Objet3D monde;
Objet3D navMesh;
Objet3D skybox;
Objet3D meteor;
//Debug
glm::vec3 previousCam(0, 0, 0);
// FIN TEST
//Variables main
AudioManager* audioManager = new AudioManager();
vector<Vertex> vertices;
vector<Face> faces;
vector<Tex> texture;
bool red = true;
bool blue = true;
GLdouble SPEED = .07;
GLdouble strafeSpeed = 0.05;
GLdouble walkSpeed = 0.05;
GLdouble runSpeed = 0.11;
GLdouble mouseSensitivityAngle = .002;
const GLdouble minYAngle = -3.141592 / 2.0; // Minimum angle (e.g., -90 degrees)
const GLdouble maxYAngle = 3.141592 / 2.0;
float oldMouseX = -1;
float oldMouseY = -1;
float xOffset = 0;
float yOffset = 0;
float dX = 0; // d�calage selon l'axe X en d�placement
float dZ = 0;// d�calage selon l'axe Z en d�placement
glm::mat4 view; // matrice de vue
Camera camera; //D�finition de la cam�ra
// Taille de la fen�tre
int windowW = 640;
int windowH = 480;
float focale = 65.0f;
float near1 = 0.1f;
float far1 = 100.0f;
std::vector<bool> keys(GLFW_KEY_LAST, false);
std::vector<bool> mouseClick(2, false);
bool shouldExit = false;
vector<Objet3D*> otherEnnemiCollider; // everything but the camera's collider
Crosshair crosshair;
ShootBar shootBar;

GLvoid mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        mouseClick[0] = true;
        shootBar.downAmo();
        if (camera.getUI().isGun()) {
            audioManager->playSong(1);
        }
        // Il faut faire des d�gats sur ennemi
        //////////////////////////////////////////
        if (shootBar.getAmo() > 0)// A-t-on es balles?
        {
            float temp;
            for (vector<Ennemi*>::iterator it = player.listEnnemi.begin(); it != player.listEnnemi.end(); it++) {
                temp = (*it)->isShot(camera.getPosition(), glm::normalize(camera.getTarget() - camera.getPosition()));
                bool a = camera.getUI().isKnife(); bool b = camera.getUI().isGun();
                
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
  /*  monde.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/map.obj");
    spawnPoints.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/spawnPoints.obj");

    navMesh.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/map.obj");
    navMesh.LoadTexture("Terrain.png");
    monde.LoadTexture("Terrain.png");
    heart.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/heart.obj");
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

    meteor.LoadTexture("meteor.png");
    meteor.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/meteor.obj");

    smog.LoadOBJ("C:/Users/Utilisateur/source/repos/HaloLikeP1RV/HaloLikeP1RV/Modele/smog.obj");*/


    ///Load objet ECN
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

    smog.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/smog.obj");

    diamond.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/Diamond.obj");
    diamond.LoadTexture("Diamond.jpg");
    //// FIN LOAD

    player.initPos();

    listUI.AddObject(gun);
    listUI.AddObject(knifeHandle);
    listUI.AddObject(knifeBlade);
    listUI.AddObject(glove);
    listUI.AddObject(heart);
    //
    camera.setUI(listUI);
    camera.changeState(0, false);
    camera.setPlayer(testPlayer);
  
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
    out vec2 TexCoord;
    void main() {
        gl_Position =   projection *view *model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
    }
)";


    const char* fragmentShaderSourceGround = R"(
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D texture1; // Texture unit

    void main() {

    vec4 texColor = texture(texture1, TexCoord); 
    vec4 darkEarthBrown = vec4(0.4, 0.2, 0.1,1.0); // Red color

    float blendFactor = 0.5; // You can change this value

    FragColor = mix(texColor, darkEarthBrown, blendFactor);
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
    // Initalisation du rayon de projection pour la coordonn�e en y
    rayon downSnap(navMesh.getvraiFaces());
    glm::vec3 intersection(0.0f);

    // Lancement du OST original
    audioManager->playSong(0);

    ReloadManager reloadManager(smog, smogShader, spawnPoints.getvraiFaces(),&shootBar);


    while (!glfwWindowShouldClose(window)) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        camera.updateCamera();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Enable texturing

        glEnable(GL_TEXTURE_2D);

        clavier();


        // AFFICHAGE DES OBJETS
        monde.affichageShader(groundShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0));
        
        if ((player.getDamageFrame() / 10) % 2 == 0) { player.affichageShaderOffset(baseShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0), -player.getPos()); }
        else { player.affichageShaderOffset(redDamageShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0),-player.getPos()); }

        //meteor.affichage();
        camera.affichageUI(keys, mouseClick,healthShader);

        skybox.affichageSkybox(skyboxShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0));
        if (camera.getUI().isGun()) {
            shootBar.affichage();
        }
        
        diamond.affichage();

        // Crosshair
        crosshair.affichageCrosshair();
        //reload
        reloadManager.actTime(camera.getPosition(),camera.getTarget());
        reloadManager.affichage(camera.getPosition(), camera.getTarget());
        //
        camera.goFrontCamera(dZ,otherEnnemiCollider);
        camera.goSideCamera(dX,otherEnnemiCollider);

        
        // Intersection Joueur
        intersection = downSnap.ptIntersectionF(player.getPos());
       
        if (intersection != glm::vec3{ -100,-100,-100 })
        {
            if (!camera.isJumping())
            {
                player.setHeight(intersection.y);
            }
        }

        // Intersection Ennemi
        intersection = downSnap.ptIntersectionF(camera.getPosition());
        if (intersection != glm::vec3{ -100,-100,-100 })
        {
            camera.sethauteur(intersection, _HEIGHT);
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

        // Exit on Echap
        if (shouldExit) {
            break;
        }
    }

    // Clean up
    glfwTerminate();
    audioManager->destroy();
    return 0;
}