cmake_minimum_required(VERSION 3.29)
project(eulers-method)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        muparser
        GIT_REPOSITORY https://github.com/beltoforion/muparser.git
        GIT_TAV        v2.3.5
)

set(ENABLE_OPENMP OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(muparser)

add_executable(eulers-method main.cpp
)
target_link_libraries(eulers-method PRIVATE muparser)



