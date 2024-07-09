#include "window.h"
#include "spdlog/spdlog.h"


namespace hi{

    
int Window::CallbackManager::width = 0;
int Window::CallbackManager::height = 0;
std::function<void(GLFWwindow*, double, double)> Window::CallbackManager::scrollFun = nullptr;
std::function<void(GLFWwindow*, double, double)> Window::CallbackManager::mouseFun = nullptr;
std::function<void(GLFWwindow*, int, int)> Window::CallbackManager::resizeFun = nullptr;
std::function<void(GLFWwindow*, int, int, int)> Window::CallbackManager::mouseButtonFun = nullptr;
std::function<void(GLFWwindow*, int, int, int, int)> Window::CallbackManager::keyFun = nullptr;


Window::Window(const std::string& _title, unsigned int _width, unsigned int _height) 
    : title(_title) {
    CallbackManager::width = _width;
    CallbackManager::height = _height;
    initWindow();
}

void Window::initGlad() {
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		spdlog::error("Failed to initialize GLAD");
		return;
	}else{
        spdlog::info("Load glad functions OK");
    }
}

void Window::initWindow() {
    // Init window
    if (!glfwInit()) {
        spdlog::error("Couldn't initialize window !");
        return;
    }else{
        spdlog::info("Creating glfw window ...");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    window = glfwCreateWindow(CallbackManager::width, CallbackManager::height, title.c_str(), NULL, NULL);
    
    if (!window) terminate();
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, CallbackManager::frameBufferSizeCallback);
    glfwSetCursorPosCallback(window, CallbackManager::mouseCallback);
    glfwSetMouseButtonCallback(window, CallbackManager::mouseButtonCallback);
    glfwSetKeyCallback(window, CallbackManager::keyCallback);
    glfwSetScrollCallback(window, CallbackManager::scrollCallback);
    //glfwSwapInterval(1);
    
    // Init Glad
    initGlad();
    spdlog::info("Creating glfw window OK");
}

void Window::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::CallbackManager::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    CallbackManager::width = width;
    CallbackManager::height = height;
    if(resizeFun != nullptr) resizeFun(window, width, height);
}

void Window::CallbackManager::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if(mouseFun != nullptr) mouseFun(window, xpos, ypos);
}

void Window::CallbackManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if(mouseButtonFun != nullptr) mouseButtonFun(window, button, action, mods);
}

void Window::CallbackManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(keyFun != nullptr) keyFun(window, key, scancode, action, mods);
}

void Window::CallbackManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
    if( scrollFun != nullptr) scrollFun(window, xoffset, yoffset);
}

}