if(DEFINED BUILD_HI_TRIANGLE)
    unset(BUILD_HI_TRIANGLE CACHE)
endif()

if(DEFINED BUILD_LOAD_MODEL)
    unset(BUILD_LOAD_MODEL CACHE)
endif()

option(BUILD_HI_TRIANGLE "build hiTriangle" ON)
option(BUILD_LOAD_MODEL "build loadModel" ON)

if(BUILD_HI_TRIANGLE)
    message("option BUILD_HI_TRIANGLE: ON")
    add_subdirectory(hiTriangle)
endif()

if(NOT BUILD_HI_TRIANGLE)
    message("option BUILD_HI_TRIANGLE: OFF")
endif()

if(BUILD_LOAD_MODEL)
    message("option BUILD_LOAD_MODEL: ON")

    add_subdirectory(loadModel)
endif()

if(NOT BUILD_LOAD_MODEL)
    message("option BUILD_LOAD_MODEL: OFF")
endif()
