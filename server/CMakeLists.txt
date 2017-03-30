add_subdirectory(detail)

set(server_SRCS
  ${server_detail_SRCS}
  common_data.hpp
  server.hpp
)

add_library(server ${server_SRCS})
set_target_properties(server PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(server server_detail)

