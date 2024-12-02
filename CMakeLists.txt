cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 23)
project(terminal-demo)
add_executable(terminal-demo
        main.cpp)


project(graphic-demo)
find_package(SFML COMPONENTS system window graphics)
add_executable(graphic-demo
        graphic-demo.cpp)
target_link_libraries(graphic-demo sfml-graphics sfml-system sfml-window)

