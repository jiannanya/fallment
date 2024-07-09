#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H


#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "common/defines.h"
#include "shaderProgram.h"

namespace hi{

class Material {
    MAKE_PTR(Material)
private:
    glm::vec3 diffuse, specular;
    float shininess;
public:
    Material(const glm::vec3& _diffuse, const glm::vec3& _specular, float _shininess)
        : diffuse(_diffuse), specular(_specular), shininess(_shininess) { }
    Material() = default;
    ~Material() = default;
public:

    inline void setDiffuse(const glm::vec3& diffuse) { this->diffuse = diffuse; }
    inline glm::vec3& getDiffuse() { return diffuse; }

    inline void setSpecular(const glm::vec3& specular) { this->specular = specular; }
    inline glm::vec3& getSpecular() { return specular; }

    /**
     * @brief shininess: 2, 4, 8, 16, 32, 64, ..., 256
     * 
     * @param shininess 
     */
    inline void setShininess(const float shininess) { this->shininess = shininess; }
    inline float getShininess() const { return shininess; }

    inline void setShaderProgram(ShaderProgram::Ptr sp){shaderProgram = sp;}
    inline ShaderProgram::Ptr& getShaderProgram(){return shaderProgram;}
    void useDefaultMaterial();

private:

    ShaderProgram::Ptr shaderProgram;

};


}

#endif