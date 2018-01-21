cmake_minimum_required(VERSION 3.9)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Source and build directories cannot be the same.")
endif()

set(NAME R-Type)

include_directories(SYSTEM ../SFML/include)

include_directories(include)
include_directories(shared)

link_directories(SFML/lib)

add_executable(
        ${NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_compile_features(${NAME} PUBLIC cxx_std_17)

target_sources(${NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Client.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/GUIElements.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Ship.cpp

        # ECS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Systems/Render.cpp

        # Temporary
        ${CMAKE_CURRENT_SOURCE_DIR}/shared/StartPage/StartPage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shared/LobbyPlayer.cpp
)

include(../Common/common.cmake)

target_link_libraries(${NAME} -lboost_system sfml-system sfml-graphics sfml-window sfml-audio AlfredBase -lstdc++fs stdc++fs)

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
file(TO_NATIVE_PATH "${CMAKE_BINARY_DIR}/Client" copyDest)

#MAPS
add_subdirectory(shared)