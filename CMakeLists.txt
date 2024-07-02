cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME constellation)
project(${PROJECT_NAME})

file(GLOB SOURCE src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})
# target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -pedantic -Wshadow -Wconversion -Wsign-conversion)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
