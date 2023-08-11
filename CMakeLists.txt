cmake_minimum_required(VERSION 3.27.0)
project(r3nder VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

# 1. Look for a SDL2 package, 2. Look for the SDL2maincomponent and 3. DO NOT fail when SDL2main is not available
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

file(GLOB_RECURSE ENGINE engine/src/*.cpp)
file(GLOB_RECURSE CUSTOM_SRCS custom/src/*.cpp)

add_executable(r3nder ${ENGINE} ${CUSTOM_SRCS} main.cpp)

target_include_directories(r3nder PRIVATE custom/include engine/include)

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(r3nder PRIVATE SDL2::SDL2main)
endif()

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
target_link_libraries(r3nder PRIVATE SDL2::SDL2)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
