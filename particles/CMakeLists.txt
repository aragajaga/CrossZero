set(particles_SRCS
  particle.hpp
  particle.tcc
  particle_container.hpp
  particle_traits.hpp
)

add_library(particles ${particles_SRCS})
set_target_properties(particles PROPERTIES LINKER_LANGUAGE CXX)

