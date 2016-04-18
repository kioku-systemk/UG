# UG

cmake_minimum_required(VERSION 2.8)

PROJECT(UG)

add_subdirectory(third_party/zlib)
set(ZLIB_INCLUDE_DIR third_party/zlib/include)

set(LWS_WITH_SSL OFF CACHE BOOL description FORCE)
add_subdirectory(third_party/libwebsockets)
