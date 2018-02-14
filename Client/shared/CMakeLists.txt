 set(CMAKE_POSITION_INDEPENDENT_CODE ON)

 include_directories(SYSTEM ../SFML/include)
 link_directories(${SFML_BINARY_DIR}/lib)

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

#MAPS
add_library(KirbyMap SHARED Maps/KirbyMap/KirbyMap.hpp Maps/KirbyMap/KirbyMap.cpp Maps/ILevels.hpp Maps/KirbyMap/levels/LevelOne.cpp Maps/KirbyMap/levels/LevelOne.hpp ${COMMON_SOURCES})

#MOBS
add_library(Metallos SHARED Mobs/Metallos/Metallos.cpp Mobs/Metallos/Metallos.hpp ${COMMON_SOURCES})
target_link_libraries(Metallos sfml-system sfml-graphics sfml-window sfml-audio)

#ATTACKS
add_library(BasicAttack SHARED Attack/BasicAttack/BasicAttack.cpp Attack/BasicAttack/BasicAttack.cpp ${COMMON_SOURCES})

#MOVE
add_library(StraightMove SHARED Move/StraightMove/StraightMove.cpp Move/StraightMove/StraightMove.hpp ${COMMON_SOURCES})
add_library(UpAndDownMove SHARED Move/UpAndDown/UpAndDownMove.cpp Move/UpAndDown/UpAndDownMove.hpp ${COMMON_SOURCES})
add_library(SinusoideMove SHARED Move/SinusoideMove/SinusoideMove.cpp Move/SinusoideMove/SinusoideMove.hpp ${COMMON_SOURCES})

set_target_properties(KirbyMap PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/map)
target_compile_options(KirbyMap PUBLIC ${COMPILE_OPTIONS})
set_target_properties(Metallos PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/mob)
target_compile_options(Metallos PUBLIC ${COMPILE_OPTIONS})
set_target_properties(BasicAttack PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/attack)
target_compile_options(BasicAttack PUBLIC ${COMPILE_OPTIONS})
set_target_properties(StraightMove PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/move)
target_compile_options(StraightMove PUBLIC ${COMPILE_OPTIONS})
set_target_properties(UpAndDownMove PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/move)
target_compile_options(UpAndDownMove PUBLIC ${COMPILE_OPTIONS})
set_target_properties(SinusoideMove PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/move)
target_compile_options(SinusoideMove PUBLIC ${COMPILE_OPTIONS})
