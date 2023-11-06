#include <windows.h>
#include "Texture.h"
#include <glad/glad.h>

GLuint Texture::getID()
{
    return ID;
}

Texture::Texture() {}

void Texture::setID(GLuint n)
{
    ID = n;
}
