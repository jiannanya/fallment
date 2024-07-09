#pragma once
#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <iostream>
#include <vector>

#include "buffer.h"

namespace hi{

class IndexBuffer : public Buffer {
    MAKE_PTR(IndexBuffer)
private:
    size_t length;
public:
    IndexBuffer();
    IndexBuffer(const std::vector<unsigned int> indices);
    IndexBuffer(const IndexBuffer& indexBuffer);
    IndexBuffer(IndexBuffer&& indexBuffer) noexcept;
    IndexBuffer& operator=(const IndexBuffer& indexBuffer);
    ~IndexBuffer();
private:
    void initBuffer(std::vector<unsigned int> indices);
    void initBuffer() override;
public:
    void bind() override;
    void unbind() override;
    void updateIndices(const std::vector<unsigned int>& indices);
    std::vector<unsigned int> getIndices();
};

}

#endif