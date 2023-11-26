#pragma once
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
class World
{
public : 
	Camera camera;
	Crosshair crosshair;
	ShootBar shootBar;
protected:

};

