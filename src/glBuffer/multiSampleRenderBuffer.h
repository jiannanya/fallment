#pragma once
#ifndef MULTISAMPLERENDERBUFFER_H
#define MULTISAMPLERENDERBUFFER_H

#include "renderBuffer.h"

namespace hi{

class MultiSampleRenderBuffer : public RenderBuffer {
    MAKE_PTR(MultiSampleRenderBuffer)
protected:
    unsigned int samples;
public:
    MultiSampleRenderBuffer(unsigned int width, unsigned int height, unsigned int _samples = 4);
    MultiSampleRenderBuffer() = default;
    virtual ~MultiSampleRenderBuffer() = default;
protected:
    void initBuffer() override;
public:
    inline unsigned int getSamples() const { return samples; }
};

#endif

}