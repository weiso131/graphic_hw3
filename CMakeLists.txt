cmake_minimum_required(VERSION 3.10)
project(opengl_test)

# 開啟 C++17（或其他版本）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 找到 OpenGL
find_package(OpenGL REQUIRED)

# 找 GLFW：假設用的是 vcpkg 或系統安裝的
find_package(glfw3 REQUIRED)

# 加入 include 路徑：GLAD、GLM、你自己的 include
include_directories(
    glad/include
    glm
    ${PROJECT_SOURCE_DIR}/include
)

# 加入檔案
file(GLOB SRC_FILES
    src/*.cpp
)

add_executable(opengl_test
    main.cpp
    glad/src/glad.c
    ${SRC_FILES}
)

# 連接函式庫
target_link_libraries(opengl_test
    glfw
    OpenGL::GL
)
