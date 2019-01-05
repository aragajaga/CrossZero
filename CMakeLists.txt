cmake_minimum_required(VERSION 2.6)
project(CrossZero)

# Enable find_package policy
if (POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW) # CMake 3.12
endif ()

# Strict code to C++14
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14")

# List all source files to be compilated
set(SRC_FILES
	"button.cpp"
	"control.cpp"
	"eventhandler.cpp"
	"main.cpp"
	"mainmenu.cpp"
	"RoundedRectangleShape.cpp"
	"ScreenManager.cpp"
)

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
