cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 23)
project(terminal-demo)
add_executable(terminal-demo
        main.cpp)


project(graphic-demo)
# https://github.com/SFML/cmake-sfml-project/blob/master/CMakeLists.txt
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)
add_executable(graphic-demo
        graphic-demo.cpp)
target_link_libraries(graphic-demo PRIVATE sfml-graphics sfml-system sfml-window)
#find_package(SFML COMPONENTS system window graphics)
