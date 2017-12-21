cmake_minimum_required(VERSION 3.9)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Source and build directories cannot be the same.")
endif()

set(BINARY_NAME server)

include_directories(include)
include_directories(../Common/include/)
include_directories(../Common/config/)

file(GLOB source_files
      src/*
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
  -std=c++17 \
  -O3 \
  -W \
  -Wall \
  -Wuninitialized \
  -Winit-self \
  -Wunsafe-loop-optimizations \
  -Woverloaded-virtual \
  -Wshadow \
  -Wsign-conversion \
  -Wsign-promo \
  -Wstrict-null-sentinel \
  -Wstrict-overflow=4 \
  -Wundef \
  -Weffc++ \
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
  -Wold-style-cast \
  -flto \
  -Wodr"
)
if (DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -g3")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

add_executable(
  ${BINARY_NAME}
  ${source_files}
)
