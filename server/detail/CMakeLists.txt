set(server_detail_SRCS
  message_decoder.hpp
  server_interfaces.hpp
  server_protocol.hpp
  socket_container.hpp
)

add_library(server_detail ${server_detail_SRCS})
set_target_properties(server_detail PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(server_detail particles)

