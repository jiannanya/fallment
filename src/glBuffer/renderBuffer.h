#pragma once
#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "buffer.h"

namespace hi{

class RenderBuffer : public Buffer {
    MAKE_PTR(RenderBuffer)
protected:
    unsigned int width, height;
    int internalFormat;
public:
    RenderBuffer(unsigned int _width, unsigned int _height, int _internalFormat = GL_DEPTH_COMPONENT);
    RenderBuffer() = default;
    virtual ~RenderBuffer();
protected:
    void initBuffer() override;
public:
    void bind() override;
    void unbind() override;
public:
    inline unsigned int getWidth() const { return width; }
    inline unsigned int getHeight() const { return height; }
    inline int getInternalFormat() const { return internalFormat; }
};

#endif

}