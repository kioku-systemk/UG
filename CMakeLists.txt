# UG

cmake_minimum_required(VERSION 2.8)

PROJECT(UG)

add_subdirectory(third_party/zlib)
set(ZLIB_INCLUDE_DIR third_party/zlib/include)

set(LWS_WITH_SSL OFF CACHE BOOL description FORCE)
add_subdirectory(third_party/libwebsockets)

add_subdirectory(third_party/glfw)

# TODO build on CMake
#add_subdirectory(third_party/glew/build/cmake)

#------------------------------------------------------

find_package(OpenGL REQUIRED)
link_libraries(${OPENGL_LIBRARIES})

include_directories ("${CMAKE_SOURCE_DIR}/third_party/glfw/include")
link_libraries(glfw)

# TODO !!
#find_package(GLEW REQUIRED)
#if (GLEW_FOUND)
#   include_directories(${GLEW_INCLUDE_DIRS})
#   link_libraries(${GLEW_LIBRARIES})
#endif()

# TEMP
include_directories ("${CMAKE_SOURCE_DIR}/third_party/glew/include")
link_directories    ("${CMAKE_SOURCE_DIR}/third_party/glew/lib/Release/x64")
link_libraries(glew32)

set(SOURCE src/main.cpp)
add_executable(ug ${SOURCE})


