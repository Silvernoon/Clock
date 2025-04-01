cmake_minimum_required(VERSION 3.10)
project(Clock CXX)

if(NOT CMAKE_TOOLCHAIN_FILE)
  message(FATAL_ERROR "Please set CMAKE_TOOLCHAIN_FILE with your VCPKG")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(OpenGL_GL_PREFERENCE
    "GLVND"
    CACHE STRING "Prefer GLVND libraries")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(${PROJECT_NAME} main.cpp window.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)
# 定义一个自定义目标用于运行程序
add_custom_target(
  test
  COMMAND $<TARGET_FILE:${PROJECT_NAME}> # 运行生成的可执行文件
  COMMENT "Running ${PROJECT_NAME}..."
  VERBATIM)

# 设置运行目标依赖于主目标
add_dependencies(test ${PROJECT_NAME})
