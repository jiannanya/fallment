#include "indexBuffer.h"

#include <string>
#include <numeric>


#include "spdlog/spdlog.h"

namespace hi{


IndexBuffer::IndexBuffer() : Buffer() { }

IndexBuffer::IndexBuffer(const std::vector<unsigned int> indices)
    : Buffer(), length(indices.size()) {
    initBuffer(indices);
}

IndexBuffer::IndexBuffer(const IndexBuffer& indexBuffer) 
    : length(indexBuffer.length) {
    id = indexBuffer.id;
}

IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept 
    : length(indexBuffer.length) {
    id = indexBuffer.id;
}

IndexBuffer& IndexBuffer::operator=(const IndexBuffer& indexBuffer) {
    id = indexBuffer.id;
    length = indexBuffer.length;
    return *this;
}

IndexBuffer::~IndexBuffer() {
    unbind();
    glDeleteBuffers(1, &id);
}

void IndexBuffer::initBuffer(std::vector<unsigned int> indices) {
    spdlog::info("init index buffer start");
    // unsigned int* ind = new unsigned int[indices.size()];
    // long c = 0;
    // for(auto  i : indices) {
    //     ind[c] = i;
    //     c++;
    // }

    glGenBuffers(1, &id);
    spdlog::info("init index buffer 2");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    auto o = std::numeric_limits<long>::max();
     spdlog::info("init index buffer 3: size {} {} {}",indices.size() * sizeof(indices),o, indices.size() * sizeof(indices) > o);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
    spdlog::info("init index buffer end");
    //delete[] ind;
}

void IndexBuffer::initBuffer() { }

void IndexBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::updateIndices(const std::vector<unsigned int>& indices) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    unsigned int* ptr = (unsigned int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(ptr, &indices[0], indices.size());
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

std::vector<unsigned int> IndexBuffer::getIndices() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    unsigned int* ptr = (unsigned int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);

    std::vector<unsigned int> indices;
    for(int i = 0; i < length; i ++) indices.push_back(ptr[i]);
    
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return indices;
}

}