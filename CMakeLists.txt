cmake_minimum_required(VERSION 3.14)
project(NRE6103
  VERSION 0.1
  DESCRIPTION "Monte Carlo Simulation for Neutron Transport"
  LANGUAGES CXX
)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_STANDARD 20)

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()


enable_testing()

IF (WIN32)
  set(CMAKE_EXE_LINKER_FLAGS "-static")
ELSE()

ENDIF()

include_directories(src)
include_directories(include)
file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cc"
        )
add_executable(MyTarget ${all_SRCS})

#add_subdirectory(src)
add_subdirectory(tst)

#Google Test stuff
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

