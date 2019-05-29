cmake_minimum_required(VERSION 2.6)
project(CrossZero)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14")
set (CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories("./")
include_directories("${CMAKE_SOURCE_DIR}/src")

# List all source files to be compilated
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

# Name output binary executable file
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Strict code to C++
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system graphics window network)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()
