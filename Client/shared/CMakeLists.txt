#MAPS
add_library(KirbyMap SHARED Maps/KirbyMap/KirbyMap.hpp Maps/KirbyMap/KirbyMap.cpp)

#MOBS
add_library(Metallos SHARED Mobs/Metallos/Metallos.cpp Mobs/Metallos/Metallos.hpp)

#ATTACKS
add_library(BasicAttack SHARED Attack/BasicAttack/BasicAttack.cpp Attack/BasicAttack/BasicAttack.cpp)

#MOVE
add_library(StraightMove SHARED Move/StraightMove/StraightMove.cpp Move/StraightMove/StraightMove.hpp)
