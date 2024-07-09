#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include <memory>

#include "mesh.h"

#include "common/defines.h"

#define POINT_SIZE 1.0
#define LINE_WIDTH 1.0
#define OUTLINING_WIDTH 3.0

namespace hi{

class Object {
    MAKE_PTR(Object)
private:
    std::vector<Mesh::Ptr> meshes;
    unsigned int primitive;
    float pointSize, lineWidth, outliningWidth;
    bool showWire, visible;
    glm::mat4 modelMatrix;
public:
    Object(unsigned int _primitive, bool _showWire = false);
    Object();
    ~Object() = default;
public:
    void removeMesh(Mesh::Ptr& mesh);
    bool isSelected();
    void setSelected(bool selected);
public:
    inline void translate(const glm::vec3& v) { modelMatrix = glm::translate(modelMatrix, v); }
    inline void rotate(float degrees, const glm::vec3& axis) { modelMatrix = glm::rotate(modelMatrix, glm::radians(degrees), axis); }
    inline void scale(const glm::vec3& s) { modelMatrix = glm::scale(modelMatrix, s); }

    inline void add(const Mesh::Ptr& mesh) { meshes.push_back(mesh); }
    inline std::vector<Mesh::Ptr>& getMeshs() { return meshes; }

    inline void removeMesh(int index) { meshes.erase(meshes.begin() + index); }

    inline void setVisible(bool visible) { this->visible = visible; }
    inline bool isVisible() const { return visible; }

    inline void setShowWire(bool showWire) { this->showWire = showWire; }
    inline bool isShowWire() const { return showWire; }

    inline void setPrimitive(unsigned int primitive) { this->primitive = primitive; }
    inline unsigned int getPrimitive() const { return primitive; }

    inline void setModelMatrix(const glm::mat4& modelMatrix) { this->modelMatrix = modelMatrix; }
    inline glm::mat4& getModelMatrix() { return modelMatrix; }

    inline float getPointSize() const { return pointSize; }
    inline float getLineWidth() const { return lineWidth; }
    inline float getOutliningWidth() const { return outliningWidth; }

    inline void setPointSize(float pointSize) { this->pointSize = pointSize; }
    inline void setLineWidth(float lineWidth) { this->lineWidth = lineWidth; }
    inline void setOutliningWidth(float outliningWidth) { this->outliningWidth = outliningWidth; }
};

}

#endif