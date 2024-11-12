cmake_minimum_required(VERSION 3.10.2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(sandbox CXX)

include_directories("include")

set(LIB_SOURCES
  "src/planner.cpp"
  "src/network.cpp"
)

set(LIB_HEADERS
  # "include/manager.h"
  "include/planner.h"
  "include/network.h"
)

# Create a library
add_library(sandboxlib ${LIB_SOURCES} ${LIB_HEADERS})

# Build all app executables
set(APP_SOURCES
  "app/virtual_funcs_and_polymorphism.cpp"
)
foreach( testsourcefile ${APP_SOURCES} )
    # Cut off the file extension and directory path
    get_filename_component( testname ${testsourcefile} NAME_WE )
    add_executable( ${testname} ${testsourcefile} )
    # Linking
    target_link_libraries( ${testname} sandboxlib)
endforeach( testsourcefile ${APP_SOURCES} )

