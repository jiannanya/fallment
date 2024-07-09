#pragma once
#ifndef DEPTHTEXTURE_H
#define DEPTHTEXTURE_H

#include "texture.h"

namespace hi{

class DepthTexture : public Texture {
    MAKE_PTR(DepthTexture)
public:
    DepthTexture(int _width, int _height);
    DepthTexture() = default;
    ~DepthTexture() = default;
private:
    void generateTexture() override;
};

}

#endif