include_directories(${CMAKE_SOURCE_DIR}/Common/include/)
include_directories(${CMAKE_SOURCE_DIR}/Common/config/)
include_directories(${CMAKE_SOURCE_DIR}/Common/)

include_directories(${CMAKE_SOURCE_DIR}/Common/LibraryInterfaces/)

include(${CMAKE_SOURCE_DIR}/Common/LibraryInterfaces/libraryinterfaces.cmake)

target_sources(${NAME}
        PUBLIC
        ${CMAKE_SOURCE_DIR}/Common/src/ECS/Manager.cpp
        ${CMAKE_SOURCE_DIR}/Common/src/ECS/System.cpp
        ${CMAKE_SOURCE_DIR}/Common/src/ECS/Store.cpp

        ${CMAKE_SOURCE_DIR}/Common/src/ECS/Systems/Mouvement.cpp

        ${CMAKE_SOURCE_DIR}/Common/src/Communication/AsioSyncUdpNetwork.cpp
        ${CMAKE_SOURCE_DIR}/Common/src/Communication/UDPPacket.cpp

				${CMAKE_SOURCE_DIR}/Common/src/Mobs/Mob1/Mob1.cpp
				${CMAKE_SOURCE_DIR}/Common/src/Maps/Map1/Map1.cpp
)
