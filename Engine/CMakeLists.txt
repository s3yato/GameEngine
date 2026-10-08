find_package(OpenGL REQUIRED)

add_library(TinyEngine STATIC
    src/Application.cpp
    src/Window.cpp
    src/GLFWContext.cpp
    src/Time.cpp
    src/Math/Transform.cpp
    src/render/Render.cpp
    src/graphics/Shader.cpp
)

target_include_directories(TinyEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(TinyEngine
    PUBLIC
        glfw
        OpenGL::GL
)