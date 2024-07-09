#pragma once
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "Buffer.h"


namespace hi{

class FrameBuffer : public Buffer {
    MAKE_PTR(FrameBuffer)
public:
    FrameBuffer();
    ~FrameBuffer();
protected:
    void initBuffer() override;
public:
    void toTexture(int attachment, int texturePrimitive, int textureID);
    void blitFrom(FrameBuffer::Ptr& frameBuffer, unsigned int width, unsigned int height);
    void setRenderBuffer(int attachment, int renderBufferID);
    void bind() override;
    void unbind() override;
    bool isComplete();
};

}

#endif