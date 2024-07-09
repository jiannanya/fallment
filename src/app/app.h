#pragma once
#ifndef APP_H
#define APP_H

#include "window/window.h"
#include "viewer/viewer.h"
#include "scene/scene.h"
#include "ui/ui.h"
#include "common/defines.h"

#include <memory>

namespace hi{

class App{
    MAKE_PTR(App)
public:
    App(){}
    ~App(){}

    void setWindow(Window::Ptr);
    Window::Ptr getWindow();

    void setViewer(Viewer::Ptr);
    Viewer::Ptr getViewer();

    void setScene(Scene::Ptr);
    Scene::Ptr getScene();
    
    void setUi(Ui::Ptr);
    Ui::Ptr getUi();

    void init();
    void run();
    void frame();

private:

    Window::Ptr appWindow;
    Viewer::Ptr appViewer;
    Scene::Ptr  appScene;
    Ui::Ptr  appUi;

    



};

}





#endif