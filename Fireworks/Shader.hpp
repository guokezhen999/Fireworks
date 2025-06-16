//
//  Shader.hpp
//  Fireworks
//
//  Created by 郭珂桢 on 2025/2/18.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Shader
{
public:
    GLuint id;
    
    Shader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
    Shader &use();
    
    void loadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile);
    
    void setVector3f(const GLchar * name, const glm::vec3 &vec, GLboolean useShader = false);
    void setMatrix4f(const GLchar * name, const glm::mat4 &mat, GLboolean useShader = false);
    void setInt(const GLchar * name, const int value, GLboolean useShader = false);
    
private:
    void compile(const GLchar * vertexSource, const GLchar * fragmentSource, const GLchar * geometrySource = nullptr);
    
    void checkCompileErrors(GLuint object, std::string type);
};

#endif /* Shader_hpp */
