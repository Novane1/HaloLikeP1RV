#include <windows.h>
#include <glad/glad.h>
#include "Objet3D.h"
#include <iostream>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <sstream>
#include <fstream>

using namespace std;

// Constructeur
Objet3D::Objet3D()
{
    viewMatrix = glm::mat4(1.0f);
}

// Getters
vector<Vertex> Objet3D::getVertices()
{
    return vertices;
}
vector<Face> Objet3D::getFaces()
{
    return faces;
}
vector<glm::vec3> Objet3D::getNormals()
{
    return norms;
}
Texture Objet3D::getTexture()
{
    return texture;
}
vector<Tex> Objet3D::getTextureCoord()
{
    return textureCoord;
}
vector<vraiFace> Objet3D::getvraiFaces()
{
    return vraiFaces;
}
// Setters
void Objet3D::setVertices(vector<Vertex> v)
{
    vertices = v;
}
void Objet3D::setFaces(vector<Face> f)
{
    faces = f;
}
void Objet3D::setTextureCoord(vector<Tex> t)
{
    textureCoord = t;
}
void Objet3D::setTexture(Texture t)
{
    texture = t;
}

void Objet3D::setVraiFaces()
{
    vraiFace trueface;
    glm::vec3 tmp;
    glm::vec2 tmp2;


    for (const Face& face : faces) {
        
        tmp.x = vertices[face.v1 - 1].x; tmp.y = vertices[face.v1 - 1].y; tmp.z = vertices[face.v1 - 1].z;

        trueface.vertexA = tmp;

        tmp.x = vertices[face.v2 - 1].x; tmp.y = vertices[face.v2 - 1].y; tmp.z = vertices[face.v2 - 1].z;

        trueface.vertexB = tmp;

        tmp.x = vertices[face.v3 - 1].x; tmp.y = vertices[face.v2 - 1].y; tmp.z = vertices[face.v2 - 1].z;

        trueface.vertexC = tmp;

        // Coordonnées de texture, non utilisé pour l'instant
        /*tmp2.x = textureCoord[face.vt1 - 1].v1;
        tmp2.y = textureCoord[face.vt1 - 1].v2;

        trueface.texCoords = tmp2;*/

        tmp = norms[face.normal - 1];

        trueface.normal = tmp;

        vraiFaces.push_back(trueface);
    }

    return;
}

// Methodes
void Objet3D::affichage()
{
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 mvpMatrix = projectionMatrix * viewMatrix;
        //GLint mvpLocation = glGetUniformLocation(shaderProgram, "MVP");
        //glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
        glBindTexture(GL_TEXTURE_2D, texture.getID());
        glBegin(GL_TRIANGLES);
        for (const Face& face : faces) {// affichage de la scène

            // Gris

            //glColor3f(vertices[face.v1 - 1].r, vertices[face.v1 - 1].v, vertices[face.v1 - 1].b);
            glTexCoord2f(textureCoord[face.vt1 - 1].v1, textureCoord[face.vt1 - 1].v2);
            glVertex3f(vertices[face.v1 - 1].x, vertices[face.v1 - 1].y, vertices[face.v1 - 1].z);
            //glColor3f(vertices[face.v2 - 1].r, vertices[face.v2 - 1].v, vertices[face.v2 - 1].b);
            glTexCoord2f(textureCoord[face.vt2 - 1].v1, textureCoord[face.vt2 - 1].v2);
            glVertex3f(vertices[face.v2 - 1].x, vertices[face.v2 - 1].y, vertices[face.v2 - 1].z);
            //glColor3f(vertices[face.v3 - 1].r, vertices[face.v3 - 1].v, vertices[face.v3 - 1].b);
            glTexCoord2f(textureCoord[face.vt3 - 1].v1, textureCoord[face.vt3 - 1].v2);
            glVertex3f(vertices[face.v3 - 1].x, vertices[face.v3 - 1].y, vertices[face.v3 - 1].z);
        }

        glEnd();
    
}



void Objet3D::LoadTexture(const char* path)
{
        // Load the image using STB Image
        int width, height, channels;
        unsigned char* image = stbi_load(path, &width, &height, &channels, 0);

        if (!image) {
            cout << "Failed to load texture: " << path << endl;
            return;
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
        Texture tex;
        tex.setID(textureID);
        texture = tex;
    
}

void Objet3D::LoadOBJ(const char* filename)
{

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
            else if (token == "f") { // format du type f x/y/z x/y/z x/y/z, où seul les x et y nous interesse. 

                // il s'agit de tout les triplets de points formant des triangles
                Face face;
                char c = 'non';
                iss >> face.v1;
                //passer au point suivant
                while (c != '/') { iss.get(c); }
                iss >> face.vt1;

                while (c != '/') { iss.get(c); }
                //iss >> face.normal;                                                   TODO
                while (c != ' ') { iss.get(c); }

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
                glm::vec3 norm;
                iss >> norm.x >> norm.y >> norm.z;

                norms.push_back(norm);
            }
            // Coordonnées de texture
            else if (token == "vt") {
                Tex tex;
                iss >> tex.v1 >> tex.v2;
                tex.v2 = 1.0 - tex.v2;
                textureCoord.push_back(tex);
            }
        }
        file.close();
        
    
}



