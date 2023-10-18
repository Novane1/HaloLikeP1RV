#ifndef SHADER_H
#define SHADER_H
//#include <glad/glad.h>

#include "glm/glm/glm.hpp"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

#include <string>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& matrix) const;
private:
    unsigned int ID;
    void checkCompileErrors(unsigned int shader, std::string type);

};

#endif

