# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(mlf_beam_sim)

# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
option(WITH_GEANT4_UIVIS "Build with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

# Find ROOT as well
find_package(ROOT REQUIRED)

# Setup Geant4 + ROOT include directories and compile definitions
# Setup include directory for this project
include(${Geant4_USE_FILE} ${ROOT_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include ${ROOT_INCLUDE_DIR})
add_definitions(${ROOT_DEFINITIONS})

execute_process (COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process (COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process (COMMAND root-config --version OUTPUT_VARIABLE ROOT_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
message(STATUS "[ROOT]: root-config --version: ${ROOT_VERSION}")
message(STATUS "[ROOT]: root-config --cflags: ${ROOT_CXX_FLAGS}")
message(STATUS "[ROOT]: root-config --libs: ${ROOT_LD_FLAGS}")

#set(CMAKE_CXX_FLAGS ${ROOT_CXX_FLAGS} " -std=c++11")
set(CMAKE_CXX_FLAGS ${ROOT_CXX_FLAGS})
message(${CMAKE_CXX_FLAGS})

# Locate sources and headers for this project
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Add the executable, and link it to the Geant4 libraries
add_executable(mlf_beam_sim mlf_beam_sim.cc ${sources} ${headers})
set_target_properties(mlf_beam_sim PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/..")
target_link_libraries(mlf_beam_sim ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
add_executable(decay_parents decay_parents.cc ${sources} ${headers})
set_target_properties(decay_parents PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/..")
target_link_libraries(decay_parents ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
