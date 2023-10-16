#include "Texture.h"

GLuint Texture::getID()
{
    return ID;
}

Texture::Texture()
{
    ;
}

void Texture::setID(GLuint n)
{
    ID = n;
}
