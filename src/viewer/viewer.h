#pragma once
#ifndef VIEWER_H
#define VIEWER_H

#include "scene/scene.h"
#include "camera/camera.h"
#include "window/window.h"
#include "common/defines.h"

namespace hi{

class Viewer{
    MAKE_PTR(Viewer)
public:

    Viewer(){}
    ~Viewer(){}

    inline void addCamera( Camera::Ptr cam ){_camera = cam;}
    inline  Camera::Ptr& getCamera(){return _camera;}

    inline void setWindow(Window::Ptr w){appWindow = w;}
    Window::Ptr& getWindow(){return appWindow;}

    void setFaceCulling(const Mesh::Ptr& polytope);
    void enableBackFaceCulling();   // Counter-clockwise order
    void enableFrontFaceCulling();  // Counter-clockwise order
    void disableFaceCulling();

    void draw(Scene::Ptr&, Window::Ptr&);

private:

    Camera::Ptr _camera;

    glm::mat4 projection;
    glm::mat4 view;

    Window::Ptr appWindow;

};


}



#endif