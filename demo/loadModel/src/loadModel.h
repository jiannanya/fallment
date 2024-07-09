#pragma once
#ifndef LOADMODEL_H
#define LOADMODEL_H

#include "app/app.h"
#include "window/window.h"
#include "common/defines.h"

#include "spdlog/spdlog.h"

namespace lm{

class load_model_app: public hi::App{
    MAKE_PTR(load_model_app)

public:
    load_model_app():hi::App(){ 
        
        
    }




private:


};


class load_model_window: public hi::Window{
    MAKE_PTR(load_model_window)

public:
    load_model_window()=default;
    load_model_window(const std::string& _title, unsigned int _width, unsigned int _height)
        :hi::Window(_title, _width, _height)
        {
        }

};

class load_model_viewer: public hi::Viewer{
    MAKE_PTR(load_model_viewer)

public:
    load_model_viewer():hi::Viewer(){}

    void initEventCallback(){
        auto fn_resize = std::bind(&load_model_viewer::resizeFun,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
        auto fn_mouse = std::bind(&load_model_viewer::mouse_callback,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
        auto fn_scroll = std::bind(&load_model_viewer::scroll_callback,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
        auto fn_mouse_button 
            = std::bind(&load_model_viewer::mouse_button_callback,
                        this,
                        std::placeholders::_1,
                        std::placeholders::_2,
                        std::placeholders::_3,
                        std::placeholders::_4
                        );
        
        getWindow()->setResizeFun(fn_resize);
        getWindow()->setMouseFun(fn_mouse);
        getWindow()->setScrollFun(fn_scroll);
        getWindow()->setMouseButtonFun(fn_mouse_button);

    }

    void updateCmaeraViewProjection(){
        auto cam = getCamera();
        if(cam.get()){
                glm::mat4 projection = glm::perspective(glm::radians(fov),
                                                        static_cast<float>(getWindow()->getWidth())/ static_cast<float>(getWindow()->getHeight()), 
                                                        0.1f, 
                                                        1000.0f);
                cam->setProjectionMatrix(projection);

                // camera/view transformation
                glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
                cam->setViewMatrix(view);
        }
    }

    void processInput(){processInput(getWindow()->getGLFWwindow());}

private:

    //std::function<void(GLFWwindow*, int, int)> fn_resize;
    void resizeFun(GLFWwindow* w, int width, int height);
    void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        //spdlog::debug("mouse button event");
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
            left_mouse_press = true;
        }else{
            left_mouse_press = false;
        }
            
    }

    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        float cameraSpeed = static_cast<float>(2.5);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

private:
    bool firstMouse = true;
    float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch =  0.0f;
    float lastX =  800.0f / 2.0;
    float lastY =  600.0 / 2.0;
    float fov   =  45.0f;
    bool left_mouse_press = false;

    glm::vec3 cameraPos   = glm::vec3(100.0f, 100.0f, 200.0f);
    glm::vec3 cameraFront = glm::vec3(0,0,0)-cameraPos; //glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
};

class hi_triagnle_ui: public hi::Ui{
    MAKE_PTR(hi_triagnle_ui)
public:
    hi_triagnle_ui(hi::Window::Ptr w):hi::Ui(w){}
};


}

#endif
