cmake_minimum_required(VERSION 3.29)
project(terminal-demo)

set(CMAKE_CXX_STANDARD 23)
add_executable(terminal-demo
        main.cpp)


cmake_minimum_required(VERSION 3.29)
project(graphic-demo)

set(CMAKE_CXX_STANDARD 23)
#set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_FIND_FRAMEWORK LAST)
#set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.2/lib/cmake/SFML")


find_package(SFML COMPONENTS system window graphics)
add_executable(graphic-demo
        graphic-demo.cpp)
target_link_libraries(graphic-demo sfml-graphics sfml-system sfml-window)


