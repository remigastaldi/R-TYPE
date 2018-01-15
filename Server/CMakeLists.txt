cmake_minimum_required(VERSION 3.9)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Source and build directories cannot be the same.")
endif()

set(NAME R-Type_server)

include_directories(include)

add_executable(
        ${NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_compile_features(${NAME} PRIVATE cxx_std_17)

target_sources(${NAME}
  PUBLIC
)

include(../Common/common.cmake)

target_link_libraries(${NAME} AlfredBase)

if (UNIX)
  list(APPEND COMPILE_OPTIONS
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
    list(APPEND COMPILE_OPTIONS -g3)
  else()
    #impossible due to libs warnings
    # list(APPEND COMPILE_OPTIONS -Werror)
  endif()
endif()
target_compile_options(${NAME} PUBLIC ${COMPILE_OPTIONS})
