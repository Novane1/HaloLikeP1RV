#pragma once
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
#include "ShaderDeclaration.h"
#define _HEIGHT 4.0
int width, height, channels;
//Objets

Ennemi player(1.0f, 50.0f); // main ennemi
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
const char* dsmusic = "dsmusic.wav"; // Music name
const char* laser = "laser.wav"; // Music name

// CallBack Functions
GLvoid mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    // Shooting
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        mouseClick[0] = true; // changing the state of our mouse key
        if (camera.getUI().isGun()) {
            shootBar.downAmo(); // We drop some ammo
        }

        if (camera.getUI().isGun()) {
            audioManager->playSong(1); // Shoot sound
        }
        // We need to shoot
        //////////////////////////////////////////
        if (shootBar.getAmo() > 0)// Do we have enough ammo?
        {
            float temp;
            for (vector<Ennemi*>::iterator it = player.listEnnemi.begin(); it != player.listEnnemi.end(); it++) {
                temp = (*it)->isShot(camera.getPosition(), glm::normalize(camera.getTarget() - camera.getPosition())); // Do we hit an ennemy


                if ((camera.getUI().isKnife() && temp > 0 && temp < 6.0f) || (camera.getUI().isGun() && temp != 0))
                    // We check if we hit, and if knife is out, are we close enough
                {

                    (*it)->addHealth(-5); // Apply damage
                    (*it)->startDamageAnimation(); // Animation of damage begining
                    if ((*it)->getHealth() <= 0) {
                        (*it)->setActive(false); // If the ennemy does not have HP left, we set him inactive

                    }
                }


            }
        }


    }
    //Other update of our key's status
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        mouseClick[0] = false;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        mouseClick[1] = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        mouseClick[1] = false;
    }
    //End
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

//End of callback function

// Functions
GLfloat Norme(glm::vec3 vec1, glm::vec3 vec2) {
    GLfloat n;
    // TODO
    return 0.0;
}