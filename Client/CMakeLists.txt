cmake_minimum_required(VERSION 3.9)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Source and build directories cannot be the same.")
endif()

set(NAME R-Type)

include_directories(SYSTEM ../SFML/include)

include_directories(include)
include_directories(shared)

link_directories(${SFML_BINARY_DIR}/lib)

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
        ${CMAKE_CURRENT_SOURCE_DIR}/src/NetworkManager.cpp

        # ECS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Systems/Animation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Systems/Render.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Systems/Collision.cpp

        # Temporary
        ${CMAKE_CURRENT_SOURCE_DIR}/shared/StartPage/StartPage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shared/LobbyPlayer/LobbyPlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shared/IngameHUD/IngameHUD.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shared/Parallax/Parallax.cpp
)

include(../Common/common.cmake)

link_directories(${SFML_BINARY_DIR}/lib)

if (UNIX)
  target_link_libraries(${NAME} ${Boost_LIBRARIES} sfml-system sfml-graphics sfml-window sfml-audio AlfredBase -lstdc++fs stdc++fs -ldl)
elseif(MSVC)
  target_compile_definitions(${NAME} PRIVATE WINDOWS_LEAN_AND_MEAN=1})
  target_compile_definitions(${NAME} PRIVATE WINDOWS_LEAN_AND_MEAN)
  target_link_libraries(${NAME} ${Boost_LIBRARIES} AlfredBase ${SFML_BINARY_DIR}/lib/sfml-audio-d.lib ${SFML_BINARY_DIR}/lib/sfml-graphics-d.lib ${SFML_BINARY_DIR}/lib/sfml-system-d.lib ${SFML_BINARY_DIR}/lib/sfml-window-d.lib)
endif()


if (UNIX)
  list(APPEND COMPILE_OPTIONS
    $<$<CONFIG:Debug>: -g3>
    $<$<CONFIG:Release>: -O3>

    $<$<PLATFORM_ID:Darwin>: -stdlib=libc++ >

    $<$<BOOL:True>:
      -fdiagnostics-color=always
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
      -Wswitch
      -Wlogical-op
      -Wnoexcept
      -Winvalid-pch
      -Wredundant-decls
      -Wformat=2
      -Wmissing-format-attribute
      -Wformat-nonliteral
      -flto
      -Wodr >
  )
endif()

if(MSVC)
  target_compile_options(${NAME} PUBLIC ${COMPILE_OPTIONS} /std:c++latest)
else()
  target_compile_options(${NAME} PUBLIC ${COMPILE_OPTIONS})
endif()

#Copy SFML DLL
file(GLOB copySource "${CMAKE_BINARY_DIR}/SFML/lib/*${CMAKE_SHARED_LIBRARY_SUFFIX}")
file(TO_NATIVE_PATH "${CMAKE_BINARY_DIR}/Client" copyDest)

if(MSVC)
add_custom_command(
        TARGET ${NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${copySource} ${copyDest})
endif()

#MAPS
add_subdirectory(shared)

#Copy Boost DLL
if (WIN32)
  file(COPY ${CMAKE_SOURCE_DIR}/SFML/extlibs/libs-msvc/x64/ DESTINATION ${copyDest})
  file(COPY ${Boost_LIBRARY_DIRS}/../bin/ DESTINATION ${copyDest})
  file(COPY ${CMAKE_BINARY_DIR}/SFML/lib/ DESTINATION ${copyDest})
  #YOLo
  file(GLOB_RECURSE SFML_EXTBLIBS_WIN
          ${CMAKE_SOURCE_DIR}/SFML/extlibs/bin/x64/*.dll
          )
  file(COPY ${SFML_EXTBLIBS_WIN} DESTINATION ${copyDest})
endif()
