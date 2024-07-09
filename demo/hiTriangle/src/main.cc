#include "hi_triangle.h"

#include "model/mesh.h"
#include "camera/camera.h"

#include "imgui/imgui.h"
#include "spdlog/spdlog.h"

#include <memory>




int main(int argc, char** argv) {
    spdlog::set_level(spdlog::level::debug);

    auto app = ht::hi_triangle_app::New();
    auto window = ht::hi_triangle_window::New("Hi GL", 800, 600);
    auto ui = ht::hi_triagnle_ui::New(window);
    auto viewer = ht::hi_triangle_viewer::New();

    app->setWindow(window);
    app->initEventCallback();

    app->setUi(ui);
    app->setViewer(viewer);

    glm::mat4 projection = glm::perspective((float)glm::radians(90.0f), static_cast<float>(window->getWidth()) /  static_cast<float>(window->getHeight()), (float)0.1f, (float)1000.0f);
    glm::mat4 view(1.0f);
    auto camera = hi::Camera::New(projection, view);
    camera->lookAt(glm::vec3(0, 0, -1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    viewer->addCamera(camera);

    // draw triangle
    // std::vector<hi::Vec3f> vertices {
    //     hi::Vec3f(-0.5f, -0.5f, 0.0f), // bottom left
    //     hi::Vec3f( 0.5f, -0.5f, 0.0f), // bottom right
    //     hi::Vec3f( 0.0f,  0.5f, 0.0f), // top

    // };

    // draw quad
    std::vector<hi::Vec3f> vertices {
        hi::Vec3f( 0.5f,  0.5f, 0.0f), // 右上角
        hi::Vec3f( 0.5f, -0.5f, 0.0f), // 右下角
        hi::Vec3f(-0.5f, -0.5f, 0.0f), // 左下角
        hi::Vec3f(-0.5f, 0.5f,  0.0f)  // 左上角
    };

    std::vector<unsigned int> indices {
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    auto triangleMesh = hi::Mesh::New(vertices,indices);
    triangleMesh->setFaceCulling(hi::Mesh::FaceCulling::BACK); // BACK default

    auto scene = hi::Scene::New();
    auto object = hi::Object::New(GL_TRIANGLES);

    object->add(triangleMesh);
    object->setVisible(true);
    //object->setShowWire(true);
    scene->addObject(object);


    app->setScene(scene);


    spdlog::debug("main running!");
    app->run();
    spdlog::debug("main ending!");
    

    return 0;

}

