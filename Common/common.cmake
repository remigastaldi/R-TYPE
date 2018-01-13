include_directories(../Common/include/)
include_directories(../Common/config/)

target_sources(${NAME}
        PUBLIC
        ${CMAKE_SOURCE_DIR}/Common/src/ECS/Manager.cpp
        ${CMAKE_SOURCE_DIR}/Common/src/ECS/System/System.cpp
)
