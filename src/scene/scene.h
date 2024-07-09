#pragma once
#ifndef SCENE_H

#include "model/model.h"
#include "model/object.h"
#include "lights/lights.h"
#include "common/defines.h"

#include <vector>
#include <memory>

namespace hi{

class Scene{
    MAKE_PTR(Scene)
public:
    Scene(){
        objectVec = std::vector<Object::Ptr>();
        lightVec = std::vector<Light::Ptr>();

    }
    ~Scene(){}

    void addObject(Object::Ptr m){objectVec.emplace_back(m);}
    void addLight(Light::Ptr l){lightVec.emplace_back(l);}

    std::vector<Object::Ptr>& getObjects(){return objectVec;}
    std::vector<Light::Ptr>& getLights(){return lightVec;}


private:
    std::vector<Object::Ptr> objectVec;
    std::vector<Light::Ptr> lightVec;
    
    
};

}


#endif