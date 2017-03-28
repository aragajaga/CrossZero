cmake_minimum_required(VERSION 3.6)

project(CrossZero)

set(SFML_ROOT "C:/SFML")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "C:/SFML/cmake/Modules")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14")

find_package(SFML 2 REQUIRED system graphics window network)

include_directories(${SFML_INCLUDE_DIR})

file(GLOB_RECURSE SRC_FILES
  "*.hpp"
  "*.cpp"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
