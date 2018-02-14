cmake_minimum_required(VERSION 3.9)

#Sfml need shared libs generated because yolo
#set(BUILD_SHARED_LIBS true)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Source and build directories cannot be the same.")
endif()

project(R-TYPE)
set(R-TYPE_VERSION 001)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
  message("### DEBUG MOD ###")
  set(DEBUG true)
else()
  set(DEBUG false)
endif(CMAKE_BUILD_TYPE MATCHES Debug)

if(MSVC)
  add_definitions(-DMSVC)
elseif(APPLE)
  add_definitions(-DAPPLE)
endif()

#Alfred
include_directories(libs/Alfred/src/)
add_subdirectory(libs/Alfred)

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

set(BUILD_SHARED_LIBS true)
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
  add_subdirectory(SFML)
  add_subdirectory(Server)
  add_subdirectory(Client)
endif()
