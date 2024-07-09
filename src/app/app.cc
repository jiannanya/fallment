#include "app.h"

#include <memory>

#include "spdlog/spdlog.h"

namespace hi{

void App::setWindow(Window::Ptr w){
    appWindow = w;
}

Window::Ptr App::getWindow(){
    return appWindow;
}

void App::setViewer(Viewer::Ptr v){
    appViewer = v;
}

Viewer::Ptr App::getViewer(){
    return appViewer;
}

void App::setScene(Scene::Ptr s){
    appScene = s;
}

Scene::Ptr App::getScene(){
    return appScene;
}

void App::setUi(Ui::Ptr u){
    appUi = u;
}

Ui::Ptr App::getUi(){
    return appUi;
}

void App::init(){
    spdlog::debug("app start init!");

    
}

void App::run(){
    spdlog::debug("enter app run function!");
    if(appViewer.get() && appScene.get() && appWindow.get()){

        spdlog::debug("app start running!");

        while(!appWindow->windowShouldClose()){
            appViewer->draw(appScene,appWindow);
            appWindow->update();

        }

        spdlog::debug("app ending");
    }
}

void App::frame(){
        //spdlog::debug("enter app frame function!");
    if(appViewer.get() && appScene.get() && appWindow.get()){

        //spdlog::debug("one framing!");

        if(!appWindow->windowShouldClose()){      
            //spdlog::debug("inner!");
            appViewer->draw(appScene,appWindow);
            appWindow->update();

        }

        //spdlog::debug("app framending");
    }
}

}