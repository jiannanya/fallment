#include "loadModel.h"

#include "model/mesh.h"
#include "camera/camera.h"
#include "camera/cameraController/orbitController.h"

#include "imgui/imgui.h"
#include "spdlog/spdlog.h"

#include <memory>
#include <chrono>

int main(int argc, char** argv) {
    spdlog::set_level(spdlog::level::debug);

    auto app = lm::load_model_app::New();
    auto window = lm::load_model_window::New("Hi GL", 800, 600);
    auto ui = lm::hi_triagnle_ui::New(window);
    auto viewer = lm::load_model_viewer::New();

    app->setWindow(window);
    ;
    app->setUi(ui);
    app->setViewer(viewer);

    glm::mat4 projection =
        glm::perspective((float)glm::radians(90.0f),
                         (float)(window->getWidth() / window->getHeight()),
                         (float)0.1f, (float)1000.0f);
    glm::mat4 view(1.0f);
    auto camera = hi::Camera::New(projection, view);
    // camera->lookAt(glm::vec3(5, 5, -100), glm::vec3(0, 0, 0), glm::vec3(0, 1,
    // 0));

    viewer->addCamera(camera);
    viewer->setWindow(window);
    viewer->initEventCallback();

    auto scene = hi::Scene::New();
    auto model = hi::Model::New("F:/cc/data/stl/英雄联盟LOL 焰尾妖狐阿狸.stl",
                                GL_TRIANGLES);
    // model->setShowWire(true);
    auto ab = model->getAabb();
    auto center = model->getAabb()->center();
    spdlog::debug("center: {},{},{}", center.x, center.y, center.z);
    spdlog::debug("xlen: {}", ab->xMax() - ab->xMin());
    spdlog::debug("ylen: {}", ab->yMax() - ab->yMin());
    spdlog::debug("zlen: {}", ab->zMax() - ab->zMin());

    model->translate(glm::vec3(-center.x, -center.y, -center.z));

    // model->scale(glm::vec3(1,1.2,1));

    model->setVisible(true);
    scene->addObject(model);

    // for(int i=1;i<=2;i++){
    //     auto model2 =
    //     hi::Model::New("/Users/anycubic/AC/data/金刚狼.stl",GL_TRIANGLES);
    //     auto ab2 = model2->getAabb();
    //     auto center2 = model2->getAabb()->center();
    //     model2->translate(glm::vec3(-center2.x,-center2.y,-center2.z));
    //     model2->translate(glm::vec3(10,10,10*i));
    //     model2->setVisible(true);
    //     scene->addObject(model2);
    // }
    //     auto model2 =
    //     hi::Model::New("/Users/anycubic/AC/data/dress2.stl",GL_TRIANGLES);
    //     auto ab2 = model2->getAabb();
    //     auto center2 = model2->getAabb()->center();
    //     spdlog::debug("center2: {},{},{}", center2.x,center2.y,center2.z);
    //     model2->translate(glm::vec3(-center2.x,-center2.y,-center2.z));
    //     model2->setVisible(true);
    //     scene->addObject(model2);

    app->setScene(scene);

    spdlog::debug("main running!");
    // app->run();

    unsigned int frame = 0;
    double total_delta = 0;

    while (!window->windowShouldClose()) {
        using namespace std::chrono;
        frame++;
        // auto start = std::chrono::system_clock::now();
        // auto t1=
        // duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
        viewer->processInput();
        viewer->updateCmaeraViewProjection();
        app->frame();
        // auto t2=
        // duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
        // auto end = std::chrono::system_clock::now();
        // auto delta =
        // static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end
        // - start).count());
        //  auto delta = t2-t1;
        //  total_delta += delta;
        //  if(frame%10 == 0){
        //      spdlog::debug("fps: {}     elapse: {} ms    frame {}",
        //      1000.0*10/total_delta, total_delta/10.0, frame); total_delta =
        //      0;
        //  }

        // auto start = std::chrono::system_clock::now();
        // sleep(1);
        // auto end = std::chrono::system_clock::now();
        // delta =
        // static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end
        // - start).count()); spdlog::debug("test: {}    test-elapse: {} ms",
        // 1000.0/delta,delta);

        // spdlog::debug("start: {}   end: {}", start.time_since_epoch());
        // total_delta += delta;
        // if(frame == 100){
        //  spdlog::debug("fps: {}", 1000.0*100.0/total_delta);
        //  total_delta = 0;
        //  frame = 0;
        //}
    }
    spdlog::debug("main ending!");

    return 0;
}
