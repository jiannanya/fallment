#pragma once
#ifndef COLORBUFFERTEXTURE_H
#define COLORBUFFERTEXTURE_H

#include "texture.h"

namespace hi{

class ColorBufferTexture : public Texture {
    MAKE_PTR(ColorBufferTexture)
public:
    ColorBufferTexture(int _width, int _height);
    ColorBufferTexture() = default;
    ~ColorBufferTexture() = default;
private:
    void generateTexture() override;
};

}

#endif