#pragma once
#ifndef MULTISAMPLETEXTURE_H
#define MULTISAMPLETEXTURE_H

#include "texture.h"

namespace hi{

class MultiSampleTexture : public Texture {
    MAKE_PTR(MultiSampleTexture)
protected:
    unsigned int samples;
public:
    MultiSampleTexture(unsigned int width, unsigned int height, unsigned int _samples = 4);
    MultiSampleTexture() = default;
    ~MultiSampleTexture() = default;
protected:
    void generateTexture() override;
public:
    void bind() override;
    void unbind() override;
public:
    inline unsigned int getSamples() const { return samples; }
};

}

#endif