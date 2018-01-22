#pragma once

#include <ECS/Component.hpp>

namespace ECS
{
  namespace Components
  {
    class Stats : public ECS::Component
    {
      public:
        explicit Stats(int health) :
          health(health)
        {}

        int health;
    };
  }
}