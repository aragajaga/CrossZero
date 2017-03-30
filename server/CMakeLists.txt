add_subdirectory(detail)

set(server_SRCS
  ${server_detail_SRCS}
  server_connection_mng.hpp
  server_listener.hpp
  common_data.hpp
  server.hpp
)

add_library(server ${server_SRCS})
set_target_properties(server PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(server server_detail -lpthread)

