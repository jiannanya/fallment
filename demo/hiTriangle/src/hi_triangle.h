#pragma once
#ifndef HI_TRIANGLE_H
#define HI_TRIANGLE_H

#include "app/app.h"
#include "common/defines.h"
#include "window/window.h"

namespace ht {

class hi_triangle_app : public hi::App {
    MAKE_PTR(hi_triangle_app)

  public:
    hi_triangle_app() : hi::App() {
        fn_resize =
            std::bind(&hi_triangle_app::resizeFun, this, std::placeholders::_1,
                      std::placeholders::_2, std::placeholders::_3);
    }

    void initEventCallback() { getWindow()->setResizeFun(fn_resize); }

  private:
    std::function<void(GLFWwindow*, int, int)> fn_resize;
    void resizeFun(GLFWwindow* w, int width, int height);

  private:
};

class hi_triangle_window : public hi::Window {
    MAKE_PTR(hi_triangle_window)

  public:
    hi_triangle_window() = default;
    hi_triangle_window(const std::string& _title, unsigned int _width,
                       unsigned int _height)
        : hi::Window(_title, _width, _height) {}
};

class hi_triangle_viewer : public hi::Viewer {
    MAKE_PTR(hi_triangle_viewer)

  public:
    hi_triangle_viewer() : hi::Viewer() {}
};

class hi_triagnle_ui : public hi::Ui {
    MAKE_PTR(hi_triagnle_ui)
  public:
    hi_triagnle_ui(hi::Window::Ptr w) : hi::Ui(w) {}
};

} // namespace ht

#endif
