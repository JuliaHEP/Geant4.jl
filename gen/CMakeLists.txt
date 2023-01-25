project(Geant4Wrap)
cmake_minimum_required(VERSION 3.21)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

#---Find JlCxx package
find_package(JlCxx)
get_target_property(JlCxx_location JlCxx::cxxwrap_julia LOCATION)
get_filename_component(JlCxx_location ${JlCxx_location} DIRECTORY)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_location}")

message(STATUS "Found JlCxx at ${JlCxx_location}")

message("CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
#---Find Geant4
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

add_library(Geant4Wrap SHARED cpp/Geant4Wrap.cxx cpp/jlGeant4.cxx)

target_include_directories(Geant4Wrap PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(Geant4Wrap JlCxx::cxxwrap_julia JlCxx::cxxwrap_julia_stl Geant4::G4run)

install(TARGETS Geant4Wrap
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION lib)
