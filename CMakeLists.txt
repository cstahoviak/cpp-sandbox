cmake_minimum_required(VERSION 3.10.2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(sandbox CXX)

include_directories("include")

set(LIB_SOURCES
  "src/smart_pointers/planner.cpp"
  "src/templates/planner.cpp"
  "src/network.cpp"
  "src/node.cpp"
)

set(LIB_HEADERS
  # "include/manager.h"
  "include/smart_pointers/planner.h"
  "include/templates/planner.h"
  "include/math.h"
  "include/network.h"
  "include/node.h"
)

# Create a library
add_library(sandboxlib ${LIB_SOURCES} ${LIB_HEADERS})

# Build all app executables
set(APP_SOURCES
  "app/polymorphism_and_smart_pointers.cpp"
  "app/polymorphism_and_templates.cpp"
)
foreach( testsourcefile ${APP_SOURCES} )
    # Cut off the file extension and directory path
    get_filename_component( testname ${testsourcefile} NAME_WE )
    add_executable( ${testname} ${testsourcefile} )
    # Linking
    target_link_libraries( ${testname} sandboxlib)
endforeach( testsourcefile ${APP_SOURCES} )

