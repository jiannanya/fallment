#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "glad/glad.h"

#include "common/defines.h"

namespace hi{

class Shader {
    MAKE_PTR(Shader)
public:
    enum class ShaderType {
        None, Vertex, Fragment
    };
private:
    std::string code, filePath;
    ShaderType shaderType;
    unsigned int shaderID;
private:
    static std::string readFile(const std::string& path);
    void compileShader();
public:
    Shader(const std::string& _code, const ShaderType& _shaderType);
    Shader();
    ~Shader() = default;
    Shader(const Shader& shader);
    Shader(Shader&& shader) noexcept;
    Shader& operator=(const Shader& shader);
public:
    inline static Shader fromFile(const std::string& filePath, const ShaderType& shaderType) {
        return Shader(readFile(filePath), shaderType);
    }

    inline static Shader fromCode(const std::string& code, const ShaderType& shaderType) {
        return Shader(code, shaderType);
    }

    inline void deleteShader() { glDeleteShader(shaderID); }
public:
    inline std::string& getCode() { return code; }
    inline unsigned int getShaderID() const { return shaderID; }
    inline ShaderType& getShaderType() { return shaderType; }
};



}