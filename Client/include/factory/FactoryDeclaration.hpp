#pragma once

#include "factory/FactoryMacros.hpp"
#include "factory/Mobs/AMobs.hpp"

INIT_MOB(Bomber, "BombAttack", "UpAndDownMove", "blue_texture");

static void addCustomRessources(LibLoader &loader)
{
  auto bomber = BUILD_MOB(Bomber);
  loader.mob.set("Bomber", bomber);
}