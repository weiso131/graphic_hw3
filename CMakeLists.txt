cmake_minimum_required(VERSION 3.10)
project(opengl_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 找 OpenGL
find_package(OpenGL REQUIRED)

# 你不再用 find_package(glfw3) 了，所以這行要刪掉
# find_package(glfw3 REQUIRED)

# 加入 include 路徑
include_directories(
    glad/include
    glm
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/libs/glfw/include
)

# 加入 lib 路徑
link_directories(${PROJECT_SOURCE_DIR}/libs/glfw/lib)

# 加入你的 .cpp 檔案
file(GLOB SRC_FILES
    src/*.cpp
)

add_executable(opengl_test
    main.cpp
    glad/src/glad.c
    ${SRC_FILES}
)

# Link libraries
target_link_libraries(opengl_test
    glfw3          # 注意：這裡是 `glfw3`，要跟 lib 的名字一致
    OpenGL::GL
)
