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
    isActive = true;
}

Objet3D::~Objet3D()
{}

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
bool Objet3D::getActive()
{
    return isActive;
}
glm::vec3 Objet3D::getPos()
{
    return ourPos;
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

void Objet3D::setActive(bool act)
{
    isActive = act;
    collider.setActive(act);
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


        tmp.x = vertices[face.v3 - 1].x; tmp.y = vertices[face.v3 - 1].y; tmp.z = vertices[face.v3 - 1].z;
        trueface.vertexC = tmp;

 

        tmp = norms[face.normal - 1];
        trueface.normal = tmp;

        vraiFaces.push_back(trueface);
    }

    return;
}

void Objet3D::setColliderState(bool set)
{
    collider.setActive(set);
}

void Objet3D::setPos(glm::vec3 p)
{
    ourPos = p;
}

// Methodes
void Objet3D::affichage()
{
    if (isActive)
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
        
    
}

void Objet3D::affichageShader(Shader shader, glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp)
{
    if (isActive)
    {
        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

        float fov = glm::radians(90.0f);  // Field of view in radians
        float aspectRatio = 800.0f / 600.0f;  // Width divided by height
        float nearClip = 0.1f;
        float farClip = 10000.0f;

        // Create the projection matrix
        glm::mat4 projection = glm::perspective(fov, aspectRatio, nearClip, farClip);


        // Use the shader program and set the model matrix as a uniform.
        glUseProgram(shader.getShader());
        glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1i(glGetUniformLocation(shader.getShader(), "texture1"), 0);

        glBindTexture(GL_TEXTURE_2D, texture.getID());
        //Display
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, pointsTexture.size(), GL_UNSIGNED_INT, 0);
        //End of display
        glBindVertexArray(0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
}

void Objet3D::affichageShaderOffset(Shader shader, glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp, glm::vec3 offset)
{
    if (isActive)
    {
        
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 modelF = glm::mat4(1.0f);
        modelF = glm::translate(model, offset);
        glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

        float fov = glm::radians(90.0f);  // Field of view in radians
        float aspectRatio = 800.0f / 600.0f;  // Width divided by height
        float nearClip = 0.1f;
        float farClip = 10000.0f;

        // Create the projection matrix
        glm::mat4 projection = glm::perspective(fov, aspectRatio, nearClip, farClip);


        // Use the shader program and set the model matrix as a uniform.
        glUseProgram(shader.getShader());
        glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "model"), 1, GL_FALSE, glm::value_ptr(modelF));
        glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1i(glGetUniformLocation(shader.getShader(), "texture1"), 0);

        glBindTexture(GL_TEXTURE_2D, texture.getID());
        //Display
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, pointsTexture.size(), GL_UNSIGNED_INT, 0);
        //End of display
        glBindVertexArray(0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
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

void Objet3D::LoadTextureT(const char* path)
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

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
                c = 'non';
                while (c != '/') { iss.get(c); }
                //while (c != '/') { iss.get(c); }
                iss >> face.normal;
                while (c != ' ') {iss.get(c); }

                iss >> face.v2;
                // ...
                while (c != '/') { iss.get(c); }
                iss >> face.vt2;

                while (c != '/') { iss.get(c); }
                while (c != ' ' ) { iss.get(c); }

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

        this->setVraiFaces();

        file.close();
        float temp;
        for (const Face& face : faces) { // on met en place la liste de tout les points avec leur coordonnée de texture

            PointText p;

            p.position.x = vertices[face.v1 - 1].x;
            p.position.y = vertices[face.v1 - 1].y;
            p.position.z = vertices[face.v1 - 1].z;
            p.u = textureCoord[face.vt1 - 1].v1;
            p.v = textureCoord[face.vt1 - 1].v2;
            p.normal = norms[face.normal - 1];
            temp = p.normal.y;
            p.normal.y = p.normal.z;
            p.normal.z = temp;
            pointsTexture.push_back(p);
            p.position.x = vertices[face.v2 - 1].x;
            p.position.y = vertices[face.v2 - 1].y;
            p.position.z = vertices[face.v2 - 1].z;
            p.u = textureCoord[face.vt2 - 1].v1;
            p.v = textureCoord[face.vt2 - 1].v2;
            temp = p.normal.y;
            p.normal.y = p.normal.z;
            p.normal.z = temp;
            p.normal = norms[face.normal - 1];
            pointsTexture.push_back(p);
            p.position.x = vertices[face.v3 - 1].x;
            p.position.y = vertices[face.v3 - 1].y;
            p.position.z = vertices[face.v3 - 1].z;
            p.u = textureCoord[face.vt3 - 1].v1;
            p.v = textureCoord[face.vt3 - 1].v2;
            temp = p.normal.y;
            p.normal.y = p.normal.z;
            p.normal.z = temp;
            p.normal = norms[face.normal - 1];
            pointsTexture.push_back(p);


        }
        // Création du VAO , VBO et EBO, puis link avec le VAO pour pouvoir tout encapsuler dedans
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glGenBuffers(1, &EBO);
        // on set notre liste d'indices en 0, 1, 2, ... pointsTexture.size() car ils sont déjà dans l'ordre d'affichage
        for (int i = 0; i < pointsTexture.size(); i++) {
            indices.push_back(i);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, pointsTexture.size() * sizeof(PointText), pointsTexture.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PointText), (void*)offsetof(PointText, position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(PointText), (void*)offsetof(PointText, u));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(PointText), (void*)offsetof(PointText, normal));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
}

void Objet3D::LoadCOllider(const char* filename)
{
    collider.LoadCollider(filename);
}

void Objet3D::affichageSkybox(Shader shader, glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp)
{

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, cameraPosition);
    glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

    float fov = glm::radians(90.0f);  // Field of view in radians
    float aspectRatio = 800.0f / 600.0f;  // Width divided by height
    float nearClip = 0.1f;
    float farClip = 500.0f;

    // Create the projection matrix
    glm::mat4 projection = glm::perspective(fov, aspectRatio, nearClip, farClip);


    
    // Use the shader program and set the model matrix as a uniform.
    glUseProgram(shader.getShader());
    glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1i(glGetUniformLocation(shader.getShader(), "texture1"), 0);

    glBindTexture(GL_TEXTURE_2D, texture.getID());
    //Display
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, pointsTexture.size(), GL_UNSIGNED_INT, 0);
    //End of display
    glBindVertexArray(0);
    glUseProgram(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Objet3D::affichageHeartBar(Shader shader, glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp, int health,int frame)
{

    if (isActive)
    {

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 modelF = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

        float fov = glm::radians(90.0f);  // Field of view in radians
        float aspectRatio = 800.0f / 600.0f;  // Width divided by height
        float nearClip = 0.1f;
        float farClip = 10000.0f;

        // Create the projection matrix
        glm::mat4 projection = glm::perspective(fov, aspectRatio, nearClip, farClip);


        // Use the shader program and set the model matrix as a uniform.
        glUseProgram(shader.getShader());
        glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1i(glGetUniformLocation(shader.getShader(), "texture1"), 0);
        glBindTexture(GL_TEXTURE_2D, texture.getID());
        glBindVertexArray(VAO);
        for (int i = 0; i < health; i++) {
            
            modelF = glm::translate(model, glm::vec3(0.1f*i, sin(frame*0.01f+i)/40, 0.0f));
            
            glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "model"), 1, GL_FALSE, glm::value_ptr(modelF));

            glDrawElements(GL_TRIANGLES, pointsTexture.size(), GL_UNSIGNED_INT, 0);
        }
        

        
        //Display
        

       
        //End of display
        glBindVertexArray(0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Objet3D::drawCollider()
{
    collider.affichage(ourPos);
}

void Objet3D::affichageGround(Shader shader, glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp, float t, glm::vec3 meteorPos)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

    float fov = glm::radians(90.0f);  // Field of view in radians
    float aspectRatio = 800.0f / 600.0f;  // Width divided by height
    float nearClip = 0.1f;
    float farClip = 500.0f;

    // Create the projection matrix
    glm::mat4 projection = glm::perspective(fov, aspectRatio, nearClip, farClip);



    // Use the shader program and set the model matrix as a uniform.
    glUseProgram(shader.getShader());
    glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1i(glGetUniformLocation(shader.getShader(), "texture1"), 0);
    glUniform3fv(glGetUniformLocation(shader.getShader(), "meteorPos"), 1, glm::value_ptr(meteorPos));
    glUniform1f(glGetUniformLocation(shader.getShader(), "t") , t);

    glBindTexture(GL_TEXTURE_2D, texture.getID());
    //Display
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, pointsTexture.size(), GL_UNSIGNED_INT, 0);
    //End of display
    glBindVertexArray(0);
    glUseProgram(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Collider* Objet3D::getCollider()
{
    return &collider;
}


void Objet3D::initPos()
{
    glm::vec3 avr(0.0, 0.0, 0.0);
    float i = 0;
    for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
        avr.x += (*it).x;
        avr.y += (*it).y;
        avr.z += (*it).z;
        i += 1.0;
    }
    ourPos = avr / i;

}
