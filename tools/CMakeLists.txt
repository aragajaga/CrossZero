set(tools_SRCS
  math.hpp
  random.hpp
  timer.hpp
)

add_library(tools ${tools_SRCS})
set_target_properties(tools PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(tools server)

