cmake_minimum_required(VERSION 3.16)
project(constellation)

file(GLOB SOURCE src/*.cpp)
add_executable(constellation ${SOURCE})
target_link_libraries(constellation PRIVATE sfml-system sfml-window sfml-graphics)
target_compile_features(constellation PRIVATE cxx_std_20)
