#include "viewer.h"

#include "spdlog/spdlog.h"

namespace hi{

void Viewer::enableBackFaceCulling() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW); 
}

void Viewer::enableFrontFaceCulling() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW); 
}

void Viewer::disableFaceCulling() {
    glDisable(GL_CULL_FACE);
}

void Viewer::setFaceCulling(const Mesh::Ptr& polytope) {
    switch(polytope->getFaceCulling()) {
        case Mesh::FaceCulling::FRONT:
            enableFrontFaceCulling();
        break;
        case Mesh::FaceCulling::BACK:
            enableBackFaceCulling();
        break;
        case Mesh::FaceCulling::NONE:
            disableFaceCulling();
        break;
    }
}

void Viewer::draw(Scene::Ptr& scene, Window::Ptr& window){
    glDepthMask(GL_TRUE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0);
    glClearColor(0.0,0.0,0.0,1.0);

    glEnable(GL_MULTISAMPLE);


    auto& camera = _camera;
    if(camera.get()){
        projection = camera->getProjectionMatrix();
        view = camera->getViewMatrix();
    }

    
    int objc = 1;
    for(auto& object: scene->getObjects()){

        if(!object->isVisible()) return;

        glViewport(0, 0, window->getWidth(), window->getHeight());

        //spdlog::debug("w: {}, h: {}", window->getWidth(),window->getHeight());
        //spdlog::debug("draw objecj");
        //primitiveSettings(group);
        
        //spdlog::debug("draw object start {} ", objc);
        for(auto& mesh : object->getMeshs()) {
            
            // Compute model matrix from polytope and group
            glm::mat4 model = object->getModelMatrix() * mesh->getModelMatrix();
            //glm::mat4 model = glm::mat4(1.0);
            glm::mat4 mv = view * model;

            // Use shader programs
            auto shaderProgram = mesh->getMaterial().getShaderProgram();
            shaderProgram->useProgram();
            // Uniforms
            shaderProgram->uniformMat4("hi_ProjectionMatrix", projection);
            shaderProgram->uniformMat4("hi_ModelViewMatrix", mv);
                

            // Set face culling
            setFaceCulling(mesh);

            
            // Draw mesh
            mesh->draw(object->getPrimitive(), object->isShowWire());

        }
        //spdlog::debug("draw object end {}", objc++);
    }
}

}