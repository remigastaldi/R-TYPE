#pragma once

#include <LibraryInterfaces/IMob.hpp>

namespace Factory
{
  struct MobConfig
  {
    std::string name;
    std::string attack_name;
    std::string movement_name;
    std::string texture_name;
  };
}

class Mob final
{
    static IMob *build();
};