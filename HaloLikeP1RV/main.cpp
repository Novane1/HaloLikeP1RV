//Librairies
#include <windows.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "UI.h"
#include <glut.h>
#include "Camera.h"
#include "Geometry.h"
#include "Shader.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "Objet3D.h"
#include "Player.h"

using namespace std;

// VARIABLES GLOBALES
int width, height, channels;
//Objets
Objet3D player;
UI listUI;
Objet3D gun;
//Variables main
vector<Vertex> vertices;
vector<Face> faces;
vector<Tex> texture;
bool red = true;
bool blue = true;
GLdouble SPEED = .03;
GLdouble strafeSpeed = 0.02;
GLdouble walkSpeed = 0.03;
GLdouble runSpeed = 0.06;
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
}
GLvoid clavier() { 

    if (keys[GLFW_KEY_LEFT_SHIFT]) { SPEED = runSpeed;  }
    else { SPEED = walkSpeed; }
   
    if (keys[GLFW_KEY_W]) { dZ = -SPEED;  }
    else{
        if (keys[GLFW_KEY_S]) { dZ = SPEED; }
        else { dZ = 0; }
    }
    

    if (keys[GLFW_KEY_A]) { dX = strafeSpeed;  }
    else {
        if (keys[GLFW_KEY_D]) { dX = -strafeSpeed;  }
        else { dX = 0; }
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


    // Load the texture and object
    player.LoadTexture("zelda.png");
    player.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/zelda.obj");
    gun.LoadTexture("gun.png");
    gun.LoadOBJ("C:/Users/Eleve/source/repos/Novane1/HaloLikeP1RV/HaloLikeP1RV/Modele/gun.obj");
    listUI.AddObject(gun);


    camera.setUI(listUI);

  
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
        
        clavier();
        player.affichage();
        camera.affichageUI();
        

        
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




/*
// Define the vertices of a square.
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

// Define the indices for drawing the square as two triangles.
GLuint indices[] = {
    0, 1, 2,
    2, 3, 0
};

const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    uniform mat4 model;
    void main() {
        gl_Position = model * vec4(aPos, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
)";

int main() {
    // Initialize GLFW.
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Square Movement Example", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers (using GLAD).
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Compile and link shaders.
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex array and buffer objects.
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Specify vertex attribute pointers.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Create and initialize the model matrix.
    glm::mat4 model = glm::mat4(1.0f);  // Identity matrix
    GLfloat translation = 0.0f;
    GLfloat speed = 0.005f;

    // Main rendering loop.
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Apply translation to the model matrix for right and left movement.
        model = glm::translate(model, glm::vec3(translation, 0.0f, 0.0f));

        // Use the shader program and set the model matrix as a uniform.
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

        // Bind the VAO and draw the square.
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glUseProgram(0);

        // Update the translation for continuous movement.
        if (translation >= 0.5f || translation <= -0.5f) {
            speed = -speed;
        }
        translation += speed;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup and terminate GLFW.
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();

    return 0;
}
*/