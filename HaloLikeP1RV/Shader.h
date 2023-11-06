#ifndef SHADER_H
#define SHADER_H
#include <windows.h>
#include <glad/glad.h>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

#include <string>

class Shader {
protected:
    GLuint shaderProgram;
public:
    //Getter
    GLuint getShader();
    //Constructeur
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource);

};

#endif