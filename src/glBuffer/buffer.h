#pragma once
#ifndef BUFFER_H
#define BUFFER_H

#include "glad/glad.h"
#include "common/defines.h"

namespace hi{

class Buffer {
protected:
    unsigned int id;
    virtual void initBuffer() = 0;
public:
    Buffer() : id(0) {}
    virtual ~Buffer() = default;
public:
    virtual void bind() = 0;
    virtual void unbind() = 0;
public:
    inline unsigned int getID() const { return id; }
};

}

#endif