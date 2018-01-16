cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)

message($ENV{BOOST_ROOT})

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Source and build directories cannot be the same.")
endif()

project(R-TYPE)
set(R-TYPE_VERSION 001)

#Includes
include_directories(.)

#Alfred
include_directories(libs/Alfred/src/)
add_subdirectory(libs/Alfred)

if(MSVC)
    add_definitions(-DMSVC)
elseif(APPLE)
    add_definitions(-DAPPLE)
endif()

if (${DEBUG})
  message(STATUS "### DEBUG ON ###")
  set(DEBUG true)
else()
  set(DEBUG false)
endif()

configure_file(${CMAKE_SOURCE_DIR}/config/r-type001.h.in ${CMAKE_SOURCE_DIR}/Common/config/r-type001.h)

#BOOST
set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
FIND_PACKAGE(Boost COMPONENTS regex system filesystem serialization thread REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

#Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if (${SERVER_ONLY})
  message(STATUS "### BUILD R-TYPE SERVER ONLY ###")
  add_subdirectory(Server)
elseif (${CLIENT_ONLY})
  message(STATUS "### BUILD R-TYPE CLIENT ONLY ###")
  add_subdirectory(SFML)
  add_subdirectory(Client)
else()
  message(STATUS "### BUILD R-TYPE CLIENT AND SERVER ###")
  set(IMGUI_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui")
  include_directories(libs/imgui-sfml libs/imgui)
  include(libs/imgui.cmake)
  add_subdirectory(SFML)
  add_subdirectory(Server)
  add_subdirectory(Client)
endif()
