cmake_minimum_required(VERSION 3.9)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Source and build directories cannot be the same.")
endif()

set(NAME R-Type_server)

include_directories(include)

add_executable(
        ${NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Client.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Room.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/RoomManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Server.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_compile_features(${NAME} PRIVATE cxx_std_17)

target_sources(${NAME}
  PUBLIC
)

include(../Common/common.cmake)

target_link_libraries(${NAME} ${Boost_LIBRARIES} AlfredBase -ldl)

Set(COMPILE_OPTIONS "")
if (UNIX)
  list(APPEND COMPILE_OPTIONS
    $<$<CONFIG:Debug>: -g3>
    $<$<CONFIG:Release>: -O3>

    $<$<BOOL:True>:
      -fdiagnostics-color=always
      -Wall
      -Wextra
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
      -Wlogical-op
      -Wnoexcept
      -Winvalid-pch
      -Wredundant-decls
      -Wformat=2
      -Wmissing-format-attribute
      -Wformat-nonliteral
      -flto
      -Wno-odr >
  )
endif()

if(MSVC)
  target_compile_options(${NAME} PUBLIC ${COMPILE_OPTIONS}  /std:c++latest)
else()
  target_compile_options(${NAME} PUBLIC ${COMPILE_OPTIONS})
endif()

file(TO_NATIVE_PATH "${CMAKE_BINARY_DIR}\\Server" copyDest)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

#Copy Boost DLL
if (WIN32)
  file(COPY ${Boost_LIBRARY_DIRS}/../bin/ DESTINATION ${copyDest})
endif()
