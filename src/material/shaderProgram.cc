#include "shaderProgram.h"

namespace hi{

ShaderProgram::ShaderProgram(const Shader& _vertexShader, const Shader& _fragmentShader) 
    : vertexShader(_vertexShader), fragmentShader(_fragmentShader), shaderProgramID(0) {
    link();
}

ShaderProgram::ShaderProgram() : shaderProgramID(0) {}

ShaderProgram::ShaderProgram(const ShaderProgram& shaderProgram) 
    : vertexShader(shaderProgram.vertexShader), fragmentShader(shaderProgram.fragmentShader),
    shaderProgramID(shaderProgram.shaderProgramID) {
}

ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept 
: vertexShader(std::move(shaderProgram.vertexShader)), fragmentShader(std::move(shaderProgram.fragmentShader)),
    shaderProgramID(shaderProgram.shaderProgramID) {
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(shaderProgramID);
}

ShaderProgram& ShaderProgram::operator=(const ShaderProgram& shaderProgram) {
    vertexShader = shaderProgram.vertexShader;
    fragmentShader = shaderProgram.fragmentShader;
    shaderProgramID = shaderProgram.shaderProgramID;
    return *this;
}

void ShaderProgram::link() {
    // Link program
    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShader.getShaderID());
    glAttachShader(shaderProgramID, fragmentShader.getShaderID());
    glLinkProgram(shaderProgramID);
    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
        std::cout << "Couldn't link shaders\n" << infoLog << std::endl;
    }
    // Delete shaders
    vertexShader.deleteShader();
    fragmentShader.deleteShader();
}

void ShaderProgram::uniformInt(const std::string& uniform, int value) {
    int location = glGetUniformLocation(shaderProgramID, uniform.c_str());
    glUniform1i(location, value); 
}

void ShaderProgram::uniformFloat(const std::string& uniform, float value) {
    int location = glGetUniformLocation(shaderProgramID, uniform.c_str());
    glUniform1f(location, value); 
}

void ShaderProgram::uniformVec3(const std::string& uniform, const glm::vec3& vec) {
    int location = glGetUniformLocation(shaderProgramID, uniform.c_str());
    glUniform3fv(location, 1, &vec[0]); 
}

void ShaderProgram::uniformMat4(const std::string& uniform, const glm::mat4& mat) {
    int location = glGetUniformLocation(shaderProgramID, uniform.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::uniformTextureArray(const std::string& uniform, std::vector<int>& textures) {
    int location = glGetUniformLocation(shaderProgramID, uniform.c_str());
    glUniform1iv(location, textures.size(), &textures[0]);
}

}