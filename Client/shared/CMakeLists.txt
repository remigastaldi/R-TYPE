set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#MAPS
add_library(KirbyMap SHARED Maps/KirbyMap/KirbyMap.hpp Maps/KirbyMap/KirbyMap.cpp Maps/ILevels.hpp Maps/KirbyMap/levels/LevelOne.cpp Maps/KirbyMap/levels/LevelOne.hpp ${COMMON_SOURCES})

#MOBS
add_library(Metallos SHARED Mobs/Metallos/Metallos.cpp Mobs/Metallos/Metallos.hpp ${COMMON_SOURCES})

#ATTACKS
add_library(BasicAttack SHARED Attack/BasicAttack/BasicAttack.cpp Attack/BasicAttack/BasicAttack.cpp ${COMMON_SOURCES})

#MOVE
add_library(StraightMove SHARED Move/StraightMove/StraightMove.cpp Move/StraightMove/StraightMove.hpp ${COMMON_SOURCES})
add_library(UpAndDownMove SHARED Move/UpAndDown/UpAndDownMove.cpp Move/UpAndDown/UpAndDownMove.hpp ${COMMON_SOURCES})

set_target_properties(KirbyMap PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/map)
set_target_properties(Metallos PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/mob)
set_target_properties(BasicAttack PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/attack)
set_target_properties(StraightMove PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/move)
set_target_properties(UpAndDownMove PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/move)