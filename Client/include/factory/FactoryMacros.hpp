#pragma once

#include "factory/FactoryHeaders.hpp"
#include <LibraryInterfaces/IMob.hpp>
#include "factory/Mobs/AMobs.hpp"

#define INIT_MOB(NAME, ATTACK_NAME, MOVE_NAME, TEXTURE_NAME) \
static IMob * NAME##_getSymbol(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Components::Position pos)       \
{                                                                                                                       \
  return new AMobs(gameManagers, mapEngine, pos, ATTACK_NAME, MOVE_NAME, TEXTURE_NAME);                                 \
}                                                                                                                       \
/*  Get Build */                                                                                                        \
static getMobSymbol NAME##_build()                                                                                        \
{                                                                                                                       \
getMobSymbol out;                                                                                                       \
out = NAME##_getSymbol;                                                                                                   \
return out;                                                                                                             \
}                                                                                                                       \

#define BUILD_MOB(NAME) NAME##_build()