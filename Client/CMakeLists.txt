cmake_minimum_required(VERSION 3.9)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Source and build directories cannot be the same.")
endif()

set(NAME R-Type)

include_directories(include)
include_directories(SYSTEM ../SFML/include)
include_directories(../Common/include/)
include_directories(../Common/config/)

if (UNIX)
  add_compile_options(
   -std=c++17
   -O3
   -W
   -Wall
   -Wuninitialized
   -Winit-self
   -Wunsafe-loop-optimizations
   -Woverloaded-virtual
   -Wshadow
   -Wsign-conversion
   -Wsign-promo
   -Wstrict-null-sentinel
   -Wstrict-overflow=4
   -Wundef
   -Weffc++
   -Wfloat-equal
   -Wcast-align
   -Wmissing-declarations
   -Wmissing-include-dirs
   -Wswitch-enum
   -Wlogical-op
   -Wnoexcept
   -Winvalid-pch
   -Wredundant-decls
   -Wformat=2
   -Wmissing-format-attribute
   -Wformat-nonliteral
   -Wold-style-cast
   -flto
   -Wodr
  )
  if (DEBUG)
   add_compile_options(-g -g3)
  else()
   add_compile_options(-Werror)
  endif()
endif()

add_executable(
        ${NAME}
        ${CMAKE_SOURCE_DIR}/Client/src/main.cpp
        ${IMGUI_SOURCES}
)

target_sources(${NAME}
        PUBLIC
        )

link_directories(SFML/lib)
target_link_libraries(${NAME} sfml-graphics sfml-window sfml-system sfml-audio AlfredBase)
