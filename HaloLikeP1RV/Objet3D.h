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

	// Destructeurs
	virtual ~Objet3D();

	// Getters
	vector<Vertex> getVertices();
	vector<Face> getFaces();  
	vector<glm::vec3> getNormals();
	Texture getTexture();
	vector<Tex> getTextureCoord();
	vector<vraiFace> getvraiFaces();

	// Setters
	void setVertices(vector<Vertex> v);
	void setFaces(vector<Face> f);
	void setTextureCoord(vector<Tex> t);
	void setTexture(Texture t);

	void setVraiFaces(); // A appeler une seule fois par objet, après loadOBJ pour transferer la structure de données

	// Methodes 
	void affichage();
	void LoadTexture(const char* path);
	void LoadOBJ(const char* filename);
	void LoadCOllider(const char* filename);
	void affichageShader(Shader shader, glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp);
	void affichageSkybox(Shader shader, glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp);
	void drawCollider();
	Collider* getCollider();
};

#endif