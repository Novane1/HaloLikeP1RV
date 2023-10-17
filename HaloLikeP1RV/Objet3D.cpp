#include "Objet3D.h"
#include <glad/glad.h>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

vector<Vertex> Objet3D::getVertices()
{
    return vertices;
}

vector<Face> Objet3D::getFaces()
{
    return faces;
}

Texture Objet3D::getTexture()
{
    return texture;
}

vector<Tex> Objet3D::getTextureCoord()
{
    return textureCoord;
}

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

void Objet3D::affichage()
{

        glm::mat4 mvpMatrix = projectionMatrix * viewMatrix;
        GLint mvpLocation = glGetUniformLocation(shaderProgram, "MVP");
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
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

Objet3D::Objet3D()
{
    viewMatrix = glm::mat4(1.0f);
}



