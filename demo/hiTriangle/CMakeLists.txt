
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/vendor/assimp/include)
include_directories(${PROJECT_SOURCE_DIR}/vendor/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/vendor/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/vendor/glm)
include_directories(${PROJECT_SOURCE_DIR}/vendor/imgui)
include_directories(${PROJECT_SOURCE_DIR}/vendor/)
include_directories(${PROJECT_SOURCE_DIR}/vendor/spdlog/include)

if(APPLE)
        link_directories(${PROJECT_SOURCE_DIR}/vendor/libs/mac/assimp)
        link_directories(${PROJECT_SOURCE_DIR}/vendor/libs/mac/glfw)
endif()

if(WIN32)
        link_directories(${PROJECT_SOURCE_DIR}/vendor/libs/windows/assimp)
        link_directories(${PROJECT_SOURCE_DIR}/vendor/libs/windows/glfw3)
endif()

file(GLOB_RECURSE src_h ${PROJECT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE ht_h ${PROJECT_SOURCE_DIR}/demo/hiTriangle/src/*.h)

# Header Files
set(HEADERS
        ${src_h}
        ${ht_h}
)

file(GLOB_RECURSE src_cc ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE ht_cc ${PROJECT_SOURCE_DIR}/demo/hiTriangle/src/*.cc)
file(GLOB imgui_cpp ${PROJECT_SOURCE_DIR}/vendor/imgui/*.cpp)
file(GLOB imgui_backend_cpp ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp)
file(GLOB glad_c ${PROJECT_SOURCE_DIR}/vendor/glad/src/glad.c)
file(GLOB spdlog_cpp ${PROJECT_SOURCE_DIR}/vendor/spdlog/src/*.cpp)

# Source Files
set(SOURCES
        ${src_cc}
        ${ht_cc}
        ${imgui_cpp}
        ${imgui_backend_cpp}
        ${glad_c}
)

if(APPLE)
        set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
endif()

# Compile files
add_executable(hi_triangle ${SOURCES} ${HEADERS})

# Link libraries
if(APPLE)
        target_link_libraries(hi_triangle assimp dl glfw)
endif()

if(WIN32)
        target_link_libraries(hi_triangle assimp-vc143-mt glfw3)
endif()