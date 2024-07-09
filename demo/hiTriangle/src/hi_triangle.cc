#include "hi_triangle.h"

namespace ht
{

void hi_triangle_app::resizeFun(GLFWwindow* w, int width, int height) {
    getWindow()->setWidth(width);
    getWindow()->setHeight(height);
    //renderer->setViewport(width, height);
    //frameCapturer->updateViewPort(width, height);
}


} // namespace ht
