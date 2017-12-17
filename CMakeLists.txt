cmake_minimum_required(VERSION 3.9)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Source and build directories cannot be the same.")
endif()

project(R-TYPE)
set(R-TYPE_VERSION_MAJOR 0)
set(R-TYPE_VERSION_MINOR 1)
set(R-TYPE_VERSION_PATCH 0)

if(MSVC)
    add_definitions(-DMSVC)
elseif(APPLE)
    add_definitions(-DAPPLE)
endif()

if (${SERVER_ONLY})
  message(STATUS "### BUILD R-TYPE SERVER ###")
  set(SERVER true)
  set(NAME "server")
else()
  message(STATUS "### BUILD R-TYPE GAME ###")
  set(SERVER false)
  set(NAME "R-TYPE")
endif()

configure_file(${CMAKE_SOURCE_DIR}/config/r-type01.h.in ${CMAKE_SOURCE_DIR}/common/config/r-type01.h)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS
  "-O3 \
  -W \
  -Wall \
  -Wunsafe-loop-optimizations \
  -Woverloaded-virtual \
  -Wshadow \
  -Wsign-conversion \
  -Wsign-promo \
  -Wstrict-null-sentinel \
  -Wstrict-overflow=4 \
  -Wundef \
  -Weffc++ \
  -Wno-unused-variable \
  -Wfloat-equal \
  -Wcast-align \
  -Wmissing-declarations \
  -Wmissing-include-dirs \
  -Wswitch-enum \
  -Wlogical-op \
  -Wnoexcept \
  -Winvalid-pch \
  -Wredundant-decls \
  -Wformat=2 \
  -Wmissing-format-attribute \
  -Wformat-nonliteral \
  -flto \
  -Wodr"
)


if (${SERVER_ONLY})
  include_directories(common/config)
  include_directories(server/include)
  include_directories(common/components/include)
  include_directories(common/systems/include)
  file(GLOB source_files
        server/main.cpp
        server/src/*
        common/components/src/*
        common/systems/src/*
      )

else()
  include_directories(common/config)
  include_directories(server/include)
  include_directories(client/include)
  include_directories(common/components/include)
  include_directories(common/systems/include)
  file(GLOB source_files
        client/main.cpp
        server/src/*
        client/src/*
        common/components/src/*
        common/systems/src/*
      )
endif()

add_executable(
  ${NAME}
  ${source_files}
)
