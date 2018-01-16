cmake_minimum_required(VERSION 3.9)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Source and build directories cannot be the same.")
endif()

set(NAME R-Type)

include_directories(SYSTEM ../SFML/include)

include_directories(include)

add_executable(
        ${NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_compile_features(${NAME} PUBLIC cxx_std_17)

target_sources(${NAME}
        PUBLIC
        ${IMGUI_SOURCES}
)

include(../Common/common.cmake)

link_directories(SFML/lib)
target_link_libraries(${NAME} sfml-graphics sfml-window sfml-system sfml-audio AlfredBase)

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

if(MSVC)
  target_compile_options(${NAME} PUBLIC ${COMPILE_OPTIONS} /std:c++latest)
else()
  target_compile_options(${NAME} PUBLIC ${COMPILE_OPTIONS})
endif()

#Copy SFML DLL
file(GLOB copySource "${CMAKE_BINARY_DIR}/SFML/lib/*${CMAKE_SHARED_LIBRARY_SUFFIX}")
file(TO_NATIVE_PATH "${CMAKE_BINARY_DIR}\\Client" copyDest)

add_custom_command(TARGET ${NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E
        copy
        ${copySource}
        ${copyDest})

#Copy Boost DLL
if (WIN32)
  file(COPY ${Boost_LIBRARY_DIRS}/../bin/ DESTINATION ${copyDest})
endif()