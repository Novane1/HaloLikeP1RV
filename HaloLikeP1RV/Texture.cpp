#include <windows.h>
#include "Texture.h"
#include <gl/GL.h>

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
