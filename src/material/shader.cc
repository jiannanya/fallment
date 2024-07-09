#include "shader.h"

#include <fstream>

namespace hi{

Shader::Shader(const std::string& _code, const ShaderType& _shaderType) 
    : code(_code), shaderType(_shaderType) {
    compileShader();
}

Shader::Shader() : code(""), filePath(""), shaderID(0), shaderType(ShaderType::None) {}

Shader::Shader(const Shader& shader)
    : code(shader.code), filePath(shader.filePath), shaderID(shader.shaderID),
    shaderType(shader.shaderType) {
}

Shader::Shader(Shader&& shader) noexcept
    : code(std::move(shader.code)), filePath(std::move(shader.filePath)),
    shaderID(shader.shaderID), shaderType(std::move(shader.shaderType)) {
}

Shader& Shader::operator=(const Shader& shader) {
    code = shader.code;
    filePath = shader.filePath;
    shaderID = shader.shaderID;
    shaderType = shader.shaderType;
    return *this;
}

std::string Shader::readFile(const std::string& path) {
    std::ifstream file(path);
    std::string line = "", code = "";
    if(file.is_open()) {
        while ( getline(file, line) ) code += line + "\n";
        file.close();
    }
    return code;
}

void Shader::compileShader() {
    // Create shader
    std::string debugShader = "";
    switch (shaderType) {
    case ShaderType::Vertex:
        shaderID = glCreateShader(GL_VERTEX_SHADER);
        debugShader = "Vertex";
        break;
    case ShaderType::Fragment:
        shaderID = glCreateShader(GL_FRAGMENT_SHADER);
        debugShader = "Fragment";
        break;
    default:
        debugShader = "Not implemented yet";
        break;
    }
    const char* chrCode = code.c_str();
    glShaderSource(shaderID, 1, &chrCode, NULL);
    glCompileShader(shaderID);
    // Show error if any
    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << debugShader << " shader compilation error: " << infoLog << std::endl;
    }
}



}