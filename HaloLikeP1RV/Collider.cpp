#include "Collider.h"
#include <glad/glad.h>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
using namespace std;

void Collider::LoadCollider(const char* filename)
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
       
    }

    this->setVraiFaces();

    ray = rayon(vraiFaces);

    file.close();

    
}

bool Collider::checkCollision(Collider c,glm::vec3 offset,glm::vec3 posiColli) // Ne marche pas si le collider en entrée contient celle sur lequel on applique le test
{
    if (!isActive || !c.getActive()) {
        return false;
    }
    for (Vertex v : c.getVertices()) {
        glm::vec3 temp(v.x-offset.x, v.y-offset.y, v.z-offset.z);
        temp += posiColli;
        if (isInCollider(temp)) {
            return true;
        }
    }
    return false;
}

vector<Vertex> Collider::getVertices()
{
    return vertices;
}

vector<Face> Collider::getFaces()
{
    return faces;
}

bool Collider::isInCollider(glm::vec3 pos) // Convex enveloppe
{
    
    glm::vec3 dirX = glm::vec3(1, 0, 0);
    glm::vec3 dirY = glm::vec3(0, 1, 0);
    glm::vec3 dirZ = glm::vec3(0, 0, 1);
    return ray.ptIntersectionGlobalFBool(pos, dirX) && ray.ptIntersectionGlobalFBool(pos, dirY) && ray.ptIntersectionGlobalFBool(pos, dirZ);
}


void Collider::setVraiFaces()
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

void Collider::affichage(glm::vec3 colliPos)
{

    //glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
    glPushMatrix();
    glTranslatef(colliPos.x, colliPos.y, colliPos.z);
    glBegin(GL_TRIANGLES);
    for (const Face& face : faces) {// affichage de la scène

        // Gris

      
        glVertex3f(vertices[face.v1 - 1].x, vertices[face.v1 - 1].y, vertices[face.v1 - 1].z);
     
        glVertex3f(vertices[face.v2 - 1].x, vertices[face.v2 - 1].y, vertices[face.v2 - 1].z);

        glVertex3f(vertices[face.v3 - 1].x, vertices[face.v3 - 1].y, vertices[face.v3 - 1].z);
    }

    glEnd();
    glPopMatrix();
}

void Collider::setOffset(glm::vec3 pos)
{
    offset = pos;
}

glm::vec3 Collider::getOffset()
{
    return offset;
}

Collider::Collider()
{
    isActive = true;
}

void Collider::setActive(bool set)
{
    isActive = set;
}

bool Collider::getActive()
{
    return isActive;
}


