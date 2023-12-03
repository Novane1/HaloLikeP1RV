#pragma once
#ifndef Objet3D_h
#define Objet3D_h
#include <vector>
#include "Texture.h"
#include "Shader.h"
#include "Collider.h"

using namespace std;
class Objet3D
{
protected :

	vector<Vertex> vertices;
	vector<glm::vec3> norms;
	vector<Face> faces;
	vector<Tex> textureCoord;
	Texture texture;
	glm::mat4 viewMatrix;
	Collider collider;
	bool isActive;
	glm::vec3 ourPos;
	
	// SHADERS
	// Pour l'affichage en OpenGL moderne
	GLuint VAO;
	GLuint VBO, EBO;
	vector<GLuint> indices; // indice pour rendre le pointTexture. Elle vaudra 0,1,2,...,pointTexture.size()-1
	vector<PointText> pointsTexture;  // liste des points à rendre dans l'ordre
	// la différence avec vertices est que là, les points sont dans l'ordre de l'afichage et in n'y a donc pas besoin d'indices 
	// même si on utilise quand même indices, qui est juste une liste croissante incrémenté de 1 en 1


	// Nouvelle structure de données pour face, permettant de tout stocker dans un vector
	vector<vraiFace> vraiFaces;




public :

	// Constructeurs
	Objet3D();
	void initPos();
	// Destructeurs
	virtual ~Objet3D();

	// Getters
	vector<Vertex> getVertices();
	vector<Face> getFaces();  
	vector<glm::vec3> getNormals();
	Texture getTexture();
	vector<Tex> getTextureCoord();
	vector<vraiFace> getvraiFaces();
	bool getActive();
	glm::vec3 getPos();
	// Setters
	void setVertices(vector<Vertex> v);
	void setFaces(vector<Face> f);
	void setTextureCoord(vector<Tex> t);
	void setTexture(Texture t);
	void setActive(bool act);
	void setVraiFaces(); // A appeler une seule fois par objet, après loadOBJ pour transferer la structure de données
	void setColliderState(bool set);
	void setPos(glm::vec3 p);
	// Methodes 
	void affichage();
	void LoadTexture(const char* path);
	void LoadTextureT(const char* path);
	void LoadOBJ(const char* filename);
	void LoadCOllider(const char* filename);
	void affichageShader(Shader shader, glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp);
	void affichageShaderOffset(Shader shader, glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp,glm::vec3 offset);
	void affichageSkybox(Shader shader, glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp);
	void affichageHeartBar(Shader shader, glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp,int health,int frame);
	void drawCollider();
	void affichageGround(Shader shader, glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp, float t, glm::vec3 meteorPos, glm::vec3 bossPos);
	Collider* getCollider();
};

#endif