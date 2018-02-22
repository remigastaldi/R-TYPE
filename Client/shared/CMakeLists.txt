 set(CMAKE_POSITION_INDEPENDENT_CODE ON)

 include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/SFML/include)
 link_directories(${SFML_BINARY_DIR}/lib)

 Set(COMPILE_OPTIONS "")
 if (UNIX)
     list(APPEND COMPILE_OPTIONS
             $<$<CONFIG:Debug>: -g3>
             $<$<CONFIG:Release>: -O3>

             $<$<PLATFORM_ID:Darwin>: -stdlib=libc++ >

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
             -Wmissing-include-dirs
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
 endif ()

 set(UTILS_SOURCES
         ${CMAKE_SOURCE_DIR}/Common/src/ECS/Manager.cpp
         ${CMAKE_SOURCE_DIR}/Common/src/ECS/System.cpp
         ${CMAKE_SOURCE_DIR}/Common/src/ECS/Store.cpp
         ${CMAKE_SOURCE_DIR}/Common/src/ECS/Systems/Mouvement.cpp
         ${CMAKE_SOURCE_DIR}/Common/src/ECS/Systems/CleanupFrameCollisionComponents.cpp
         ${CMAKE_SOURCE_DIR}/Common/src/ECS/Systems/SpriteCollisionHandler.cpp
         ${CMAKE_SOURCE_DIR}/Common/src/ECS/Systems/Health.cpp)

 #MAPS
 add_library(KirbyMap SHARED
         Maps/KirbyMap/KirbyMap.hpp Maps/KirbyMap/KirbyMap.cpp
         Maps/ILevels.hpp
         Maps/KirbyMap/levels/LevelOne.cpp Maps/KirbyMap/levels/LevelOne.hpp
         Maps/KirbyMap/levels/LevelTwo.cpp Maps/KirbyMap/levels/LevelTwo.hpp
         Maps/KirbyMap/levels/LevelThree.cpp Maps/KirbyMap/levels/LevelThree.hpp
         ${CMAKE_SOURCE_DIR}/Client/include/GameManagers.hpp
         ${CMAKE_SOURCE_DIR}/Client/src/MapEngine.cpp
         ${CMAKE_SOURCE_DIR}/Client/src/Ship.cpp
         ${UTILS_SOURCES})
 target_link_libraries(KirbyMap sfml-system sfml-graphics sfml-window sfml-audio)

 #ATTACKS
 add_library(BasicAttack SHARED Attack/BasicAttack/BasicAttack.cpp ${UTILS_SOURCES})
 target_link_libraries(BasicAttack sfml-system sfml-graphics sfml-window sfml-audio)
 add_library(BombAttack SHARED Attack/BombAttack/BombAttack.cpp ${UTILS_SOURCES})
 target_link_libraries(BombAttack sfml-system sfml-graphics sfml-window sfml-audio)
 add_library(MiniBombAttack SHARED Attack/MiniBombAttack/MiniBombAttack.cpp ${UTILS_SOURCES})
 target_link_libraries(MiniBombAttack sfml-system sfml-graphics sfml-window sfml-audio)


 #MOBS
 add_library(Metallos SHARED Mobs/Metallos/Metallos.cpp Mobs/Metallos/Metallos.hpp ${UTILS_SOURCES})
 target_link_libraries(Metallos sfml-system sfml-graphics sfml-window sfml-audio)

 #MOVE
 add_library(StraightMove SHARED Move/StraightMove/StraightMove.cpp Move/StraightMove/StraightMove.hpp ${UTILS_SOURCES})
 add_library(UpAndDownMove SHARED Move/UpAndDown/UpAndDownMove.cpp Move/UpAndDown/UpAndDownMove.hpp ${UTILS_SOURCES})
 add_library(SinusoideMove SHARED Move/SinusoideMove/SinusoideMove.cpp Move/SinusoideMove/SinusoideMove.hpp ${UTILS_SOURCES})
 add_library(InverseSinusoideMove SHARED Move/InverseSinusoideMove/SinusoideMove.cpp Move/InverseSinusoideMove/SinusoideMove.hpp ${UTILS_SOURCES})

 #RESSOURCES
 add_library(BasicRessource SHARED Ressources/BasicRessources.hpp Ressources/BasicRessources.cpp ${UTILS_SOURCES})
 target_link_libraries(BasicRessource sfml-system sfml-graphics sfml-window sfml-audio)

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
 set_target_properties(BasicRessource PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/ressources)
 target_compile_options(BasicRessource PUBLIC ${COMPILE_OPTIONS})
 set_target_properties(BombAttack PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/attack)
 target_compile_options(BasicAttack PUBLIC ${COMPILE_OPTIONS})
 set_target_properties(MiniBombAttack PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/attack)
 target_compile_options(MiniBombAttack PUBLIC ${COMPILE_OPTIONS})
 set_target_properties(InverseSinusoideMove PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ressources/move)
 target_compile_options(InverseSinusoideMove PUBLIC ${COMPILE_OPTIONS})