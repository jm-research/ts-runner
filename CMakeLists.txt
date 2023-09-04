cmake_minimum_required(VERSION 3.20)
project(
  tsrunner
  VERSION 0.0.1
  LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "Debug")
set(project_version "${${PROJECT_NAME}_VERSION}")

message(STATUS "Project '${PROJECT_NAME}', version: '${project_version}'")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # for debug of stl structure while using clang compile
  add_compile_options(-fstandalone-debug)
endif()

set(CMAKE_CXX_FLAGS "-Wno-unused-variable -Wno-switch -Wno-trigraphs -Wno-enum-constexpr-conversion")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math")
endif()

# CMake helpers:
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

include_directories(thirdparty/fmt/include/)
include_directories(thirdparty/magic_enum)
include_directories(thirdparty/tracy/public)

add_subdirectory(thirdparty/doctest)
add_subdirectory(thirdparty/tracy)
add_subdirectory(thirdparty/fmt)

include(CTest)
enable_testing()

include_directories(include)

set(TSRUNNER_SRCS)

set(STATIC_LIB_NAME ${PROJECT_NAME})

file(GLOB_RECURSE LIB_PATH
    ./lib/*/*.cpp
  )
list(APPEND TSRUNNER_SRCS ${LIB_PATH})

add_library(${STATIC_LIB_NAME} STATIC ${TSRUNNER_SRCS})
target_link_libraries(${STATIC_LIB_NAME} fmt)

add_subdirectory(unittests)

add_executable(tscpp driver/main.cpp)
target_link_libraries(tscpp tsrunner)