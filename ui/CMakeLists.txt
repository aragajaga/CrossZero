set(ui_SRCS
  button.cpp
  button.hpp
  colorscheme.hpp
  control.cpp
  control.hpp
)

add_library(ui ${ui_SRCS})
set_target_properties(ui PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(ui tools)

