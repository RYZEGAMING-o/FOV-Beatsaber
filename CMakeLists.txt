cmake_minimum_required(VERSION 3.21)
include(qpm_defines.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(${COMPILE_ID})

add_compile_definitions(VERSION="${MOD_VERSION}" MOD_ID="${MOD_ID}")
add_compile_options(-frtti -fexceptions -Wall -Wextra -Wno-unused-parameter)
add_compile_definitions(UNITY_2021 HAS_CODEGEN FMT_HEADER_ONLY)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_library(${COMPILE_ID} SHARED ${SRC_FILES})
target_include_directories(${COMPILE_ID} PRIVATE include)
target_link_libraries(${COMPILE_ID} PRIVATE -llog)

include(extern.cmake)
