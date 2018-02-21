#pragma once

#include "factory/FactoryMacros.hpp"
#include "factory/Mobs/AMobs.hpp"

INIT_MOB(MonSuperMob, "BasicAttack", "SinusoideMove", "blue_texture");

static void addCustomRessources(LibLoader &loader)
{
  auto bob = BUILD_MOB(MonSuperMob);
  loader.mob.set("bob", bob);
}