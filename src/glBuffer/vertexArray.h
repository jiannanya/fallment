#pragma once
#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "buffer.h"

namespace hi{

class VertexArray : public Buffer {
    MAKE_PTR(VertexArray)
public:
    VertexArray();
    VertexArray(const VertexArray& vertexArray);
    VertexArray(VertexArray&& vertexArray) noexcept;
    VertexArray& operator=(const VertexArray& vertexArray);
    ~VertexArray();
protected:
    void initBuffer() override;
public:
    void bind() override;
    void unbind() override;
};

}
#endif