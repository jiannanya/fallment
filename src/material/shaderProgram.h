#pragma once
#ifndef SHADERPROGRAM

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "glad/glad.h"

#include "common/defines.h"
#include "shader.h"

namespace hi{

class ShaderProgram {
    MAKE_PTR(ShaderProgram)
private:
    unsigned int shaderProgramID;
    Shader vertexShader, fragmentShader;
public:
    ShaderProgram(const Shader& _vertexShader, const Shader& _fragmentShader);
    ShaderProgram();
    ShaderProgram(const ShaderProgram& shaderProgram);
    ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
    ~ShaderProgram();
    ShaderProgram& operator=(const ShaderProgram& shaderProgram);
private:
    void link();
public:
    void uniformInt(const std::string& uniform, int value);
    void uniformFloat(const std::string& uniform, float value);
    void uniformVec3(const std::string& uniform, const glm::vec3& vec);
    void uniformMat4(const std::string& uniform, const glm::mat4& mat);
    void uniformTextureArray(const std::string& uniform, std::vector<int>& textures);
public:
    inline void useProgram() { glUseProgram(shaderProgramID); }
    inline unsigned int getShaderProgramID() const { return shaderProgramID; }
    
    inline Shader& getVertexShader() { return vertexShader; }
    inline Shader& getFragmentShader() { return fragmentShader; }
};
    
}

#endif