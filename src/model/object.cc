#include "object.h"

namespace hi{

Object::Object(unsigned int _primitive, bool _showWire) 
    : primitive(_primitive), showWire(_showWire), modelMatrix(1.f), visible(true), 
    pointSize(POINT_SIZE), lineWidth(LINE_WIDTH), outliningWidth(OUTLINING_WIDTH) {
}

Object::Object() 
    : primitive(GL_TRIANGLES), showWire(false), modelMatrix(1.f), visible(true), 
    pointSize(POINT_SIZE), lineWidth(LINE_WIDTH), outliningWidth(OUTLINING_WIDTH) {
}

void Object::removeMesh(Mesh::Ptr& mesh) {
    unsigned int index = 0;
    for(auto& p : meshes) {
        if(p.get() == mesh.get()) {
            removeMesh(index);
            break;
        }
        index ++;
    }
}

bool Object::isSelected() {
    bool selected = true;
    for(auto& p : meshes) {
        if(!p->isSelected()) selected = false;
    }
    return selected;
}

void Object::setSelected(bool selected) {
    for(auto& p : meshes) p->setSelected(selected);
}

}