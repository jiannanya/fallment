#pragma once
#ifndef UI_H
#define UI_H

#include "window/window.h"

#include <memory>

#include "imgui/imgui.h"
#include "common/defines.h"

namespace hi{

class Ui{
    MAKE_PTR(Ui)
public:
    Ui(std::shared_ptr<Window> w){uiWindow = w;}
    virtual void initImgui();
    virtual void updateImgui();
    virtual void drawImgui();

private:
    std::shared_ptr<Window> uiWindow;
};

}

#endif