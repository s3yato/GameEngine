add_library(TinyEngine STATIC
    src/Application.cpp
    src/Window.cpp
    src/GLFWContext.cpp
    src/Time.cpp
    src/math/Transform.cpp
    src/math/Matrix4.cpp
    src/render/Render.cpp
    src/render/Mesh.cpp
    src/render/Material.cpp
    src/graphics/Shader.cpp
    src/input/Input.cpp
    src/render/Camera2D.cpp
    src/graphics/StbImage.cpp
    src/graphics/Texture.cpp
    src/graphics/SpriteBatch.cpp
)

target_compile_definitions(TinyEngine
    PUBLIC GLFW_INCLUDE_NONE
    PRIVATE ATLAS_SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders"
)

target_include_directories(TinyEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_SOURCE_DIR}/libraries/stb_image
)

target_link_libraries(TinyEngine
    PUBLIC
        glfw
        glad
        OpenGL::GL
)