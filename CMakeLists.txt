cmake_minimum_required(VERSION 2.6)

# CMAKE_BUILD_TYPE -- Цель сборки (Debug по умолчанию)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)")
endif()

project(CrossZero)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14")
set (CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories("./")
include_directories("${CMAKE_SOURCE_DIR}/src")

set(SRC_FILES
  "src/tools/random.cpp"
  "src/control.cpp"
  "src/button.cpp"
  "src/edit.cpp"
# "src/raster_rounded_rectangle.cpp"
  "src/rounded_rectangle.cpp"
  "src/screen.cpp"
  "src/settings_screen.cpp"
  "src/main_menu.cpp"
  "src/main.cpp"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
if (DEFINED SFML_INCLUDE_DIR AND SFML_LIBRARIES)
  message("You had set SFML paths manually. CMake will use them.")
  set(SFML_FOUND TRUE)
else()
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
  find_package(SFML 2 REQUIRED system graphics window network)
endif()
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

