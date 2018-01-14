/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T19:04:26+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-14T00:10:13+01:00
 */


#include  "ECS/Systems/Mouvement.hpp"

#include <iostream>

namespace ECS
{
  Mouvement::Mouvement(std::observer_ptr<ECS::Manager> &manager)
    : System(MOUVEMENT_PRIORITY, { }, manager)
    {}

  void Mouvement::updateEntity(float delta, Entity e)
  {
    ECS::Position *body = getManager()->getComponent<ECS::Position>(e);

    if (body->y == 10)
      body->x++;
    if (body->y == 20)
      body->x += 2;

    std::cout << body->x << ":" << body->x << std::endl;
  }
}
