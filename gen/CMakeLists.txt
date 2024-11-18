cmake_minimum_required(VERSION 3.21)
project(Geant4Wrap)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

#---Find JlCxx package-------------------------------------------------------------
find_package(JlCxx)
get_target_property(JlCxx_location JlCxx::cxxwrap_julia LOCATION)
get_filename_component(JlCxx_location ${JlCxx_location} DIRECTORY)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_location}")
message(STATUS "Found JlCxx at ${JlCxx_location}")
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)
#---Find Geant4---------------------------------------------------------------------
find_package(Geant4 REQUIRED gdml)
include(${Geant4_USE_FILE})

#  Files are in gen folder
file(REAL_PATH ${CMAKE_SOURCE_DIR}/../gen SOURCE_DIR)
file(GLOB GEN_SOURCES CONFIGURE_DEPENDS  ${SOURCE_DIR}/cpp/Jl*.cxx)
add_library(Geant4Wrap SHARED ${SOURCE_DIR}/cpp/Geant4Wrap.cxx ${SOURCE_DIR}/cpp/jlGeant4.cxx ${GEN_SOURCES})

#target_compile_definitions(Geant4Wrap PUBLIC VERBOSE_IMPORT)
list(REMOVE_ITEM Geant4_LIBRARIES Geant4::G4ToolsSG)  # dependencies to system OpenGL
target_include_directories(Geant4Wrap PRIVATE ${SOURCE_DIR})
target_link_libraries(Geant4Wrap JlCxx::cxxwrap_julia JlCxx::cxxwrap_julia_stl ${Geant4_LIBRARIES})

install(TARGETS Geant4Wrap
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION lib)
