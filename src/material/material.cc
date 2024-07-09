#include "material.h"
#include "default.glsl.h"


namespace hi{

void Material::useDefaultMaterial(){
    // Default shader program
    Shader vertexShader = Shader::fromCode(defaultVertexShaderCode, Shader::ShaderType::Vertex);
    Shader fragmentShader = Shader::fromCode(defaultFragmentShaderCode, Shader::ShaderType::Fragment);
    shaderProgram = ShaderProgram::New(vertexShader, fragmentShader);
}

}