#include "mesh.h"

#include "spdlog/spdlog.h"

namespace hi{

Mesh::Mesh(size_t length) 
    : vertexLength(length), modelMatrix(1.f), indicesLength(0), selected(false), 
    faceCulling(FaceCulling::BACK), emissionStrength(1.0) {
    initMesh(length);
}

Mesh::Mesh(std::vector<Vec3f>& vertices, bool _tangentAndBitangents)
    : vertexLength(vertices.size()), modelMatrix(1.f), indicesLength(0), selected(false), 
    faceCulling(FaceCulling::BACK), emissionStrength(1.0), tangentAndBitangents(_tangentAndBitangents) {
    initMesh(vertices);
}

Mesh::Mesh(std::vector<Vec3f>& vertices, std::vector<unsigned int>& indices, bool _tangentAndBitangents) 
    : vertexLength(vertices.size()), modelMatrix(1.f), indicesLength(indices.size()), selected(false), 
    faceCulling(FaceCulling::BACK), emissionStrength(1.0), tangentAndBitangents(_tangentAndBitangents) {
    initMesh(vertices, indices);
}

void Mesh::setTangentsAndBitangents(Vec3f& vertex0, Vec3f& vertex1, Vec3f& vertex2) {

    glm::vec3 pos1(vertex0.x,  vertex0.y, vertex0.z);
    glm::vec3 pos2(vertex1.x,  vertex1.y, vertex1.z);
    glm::vec3 pos3(vertex2.x,  vertex2.y, vertex2.z);

    glm::vec2 uv1(vertex0.tx, vertex0.ty);
    glm::vec2 uv2(vertex1.tx, vertex1.ty);
    glm::vec2 uv3(vertex2.tx, vertex2.ty);

    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    vertex0.tanx = vertex1.tanx = vertex2.tanx = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    vertex0.tany = vertex1.tany = vertex2.tany = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    vertex0.tanz = vertex1.tanz = vertex2.tanz = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

    vertex0.bitanx = vertex1.bitanx = vertex2.bitanx = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    vertex0.bitany = vertex1.bitany = vertex2.bitany = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    vertex0.bitanz = vertex1.bitanz = vertex2.bitanz = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
}

void Mesh::calculateTangentsAndBitangents(std::vector<Vec3f>& vertices) {

    if(!tangentAndBitangents) return;

    for(int i = 0; i < vertices.size(); i += 3) {

        Vec3f& vertex0 = vertices[i];
        Vec3f& vertex1 = vertices[i + 1];
        Vec3f& vertex2 = vertices[i + 2];

        setTangentsAndBitangents(vertex0, vertex1, vertex2);
    }
}

void Mesh::calculateTangentsAndBitangents(std::vector<Vec3f>& vertices, std::vector<unsigned int>& indices) {

    if(!tangentAndBitangents) return;

    for(int i = 0; i < indices.size(); i += 3) {
        
        Vec3f& vertex0 = vertices[indices[i]];
        Vec3f& vertex1 = vertices[indices[i + 1]];
        Vec3f& vertex2 = vertices[indices[i + 2]];

        setTangentsAndBitangents(vertex0, vertex1, vertex2);
    }   
}

void Mesh::initMesh(size_t length) {
    vertexArray = VertexArray::New();
    vertexBuffer = VertexBuffer::New(length);
    material = Material(MATERIAL_DIFFUSE, MATERIAL_SPECULAR, MATERIAL_SHININESS);
    material.useDefaultMaterial();
    unbind();
}

void Mesh::initMesh(std::vector<Vec3f>& vertices) {
    calculateTangentsAndBitangents(vertices);
    vertexArray = VertexArray::New();
    vertexBuffer = VertexBuffer::New(vertices);
    material = Material(MATERIAL_DIFFUSE, MATERIAL_SPECULAR, MATERIAL_SHININESS);
    material.useDefaultMaterial();
    unbind();
}

void Mesh::initMesh(std::vector<Vec3f>& vertices, std::vector<unsigned int>& indices) {
    calculateTangentsAndBitangents(vertices, indices);
    vertexArray = VertexArray::New();
    vertexBuffer = VertexBuffer::New(vertices, indices);
    material = Material(MATERIAL_DIFFUSE, MATERIAL_SPECULAR, MATERIAL_SHININESS);
    material.useDefaultMaterial();
    unbind();
}

void Mesh::bind() {
    if(vertexArray != nullptr && vertexBuffer != nullptr)
        //spdlog::debug("bind mesh vao {}", vertexArray->getID());
        vertexArray->bind();
}

void Mesh::unbind() {
    if(vertexArray != nullptr && vertexBuffer != nullptr)
        //spdlog::debug("unbind mesh vao {}", vertexArray->getID());
        vertexArray->unbind();
}

void Mesh::updateVertices(std::vector<Vec3f>& vertices) {
    if(vertexBuffer != nullptr) {
        vertexBuffer->updateVertices(vertices);
        vertexLength = vertices.size();
    }
}

void Mesh::updateVertex(int pos, Vec3f newVertex) {
    if(vertexBuffer != nullptr)
        vertexBuffer->updateVertex(pos, newVertex);
}

void Mesh::updateIndices(std::vector<unsigned int>& indices) {
    if(vertexBuffer != nullptr && vertexBuffer->getIndexBuffer() != nullptr) {
        vertexBuffer->getIndexBuffer()->updateIndices(indices);
        indicesLength = indices.size();
    }
}

void Mesh::removeTexture(const Texture::Ptr& texture) {
    unsigned int index = 0;
    for(auto& t : textures) {
        if(t.get() == texture.get()) {
            removeTexture(index);
            break;
        }
        index ++;
    }
}

void Mesh::draw(unsigned int primitive, bool showWire) {
    //spdlog::debug("draw mesh");
    bind();
    if(!showWire){
        //spdlog::debug("GL_FILL");
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }   
    else {
        //spdlog::debug("GL_LLINE");
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }    

    if(!vertexBuffer->HasIndexBuffer()){
        //spdlog::debug("glDrawArrays");
        glDrawArrays(primitive, 0, vertexLength);

    }
    else{
        //spdlog::debug("glDrawElements");
        glDrawElements(primitive, indicesLength, GL_UNSIGNED_INT, 0);
    }
    unbind();
}

}