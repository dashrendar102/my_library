# CMakeList.txt : CMake project for library, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (
  library
  "library.cpp"
  "library.h"
  "types.cpp"
  "types.h"
  "db_context.cpp"
  "db_context.h"
  "commands.cpp"
  "commands.h")

target_link_libraries(library -lpqxx -lpq)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET library PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
