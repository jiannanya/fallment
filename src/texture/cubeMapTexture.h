#pragma once
#ifndef CUBEMAPTEXTURE_H
#define CUBEMAPTEXTURE_H



#include <iostream>
#include <vector>

#include "texture.h"

namespace hi{

class CubeMapTexture : public Texture {
    MAKE_PTR(CubeMapTexture)
private:
    std::vector<std::string> faces;
public:
    CubeMapTexture(const std::vector<std::string>& _faces);
    CubeMapTexture() = default;
    ~CubeMapTexture() = default;
private:
    void generateTexture() override;
public:
    void bind() override;
    void unbind() override;
public:
    inline std::vector<std::string>& getFaces() { return faces; }
};

}

#endif