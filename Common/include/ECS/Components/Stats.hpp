#pragma once

#include <ECS/Component.hpp>

namespace ECS
{
  namespace Components
  {
    class Stats : public ECS::Component
    {
      public:
        explicit Stats(int _health) :
          health(_health)
        {}

        int health;
    };
  }
}