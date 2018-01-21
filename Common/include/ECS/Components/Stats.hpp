#pragma once

#include <ECS/Component.hpp>

namespace ECS
{
  namespace Components
  {
    struct Stats : public ECS::Component
    {
      int health;
    };
  }
}