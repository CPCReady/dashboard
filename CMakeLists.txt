cmake_minimum_required(VERSION 3.16)
project(Dashboard)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ftxui REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(YAML_CPP REQUIRED yaml-cpp)

add_executable(dashboard main.cpp)

target_include_directories(dashboard PRIVATE ${YAML_CPP_INCLUDE_DIRS})
target_link_libraries(dashboard PRIVATE ftxui::screen ftxui::dom ftxui::component ${YAML_CPP_LIBRARIES})