/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T19:04:26+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-15T03:35:15+01:00
 */


#include  "ECS/Systems/Mouvement.hpp"

#include <iostream>

namespace ECS
{
  Mouvement::Mouvement(std::shared_ptr<ECS::Manager> manager)
    : System(MOUVEMENT_PRIORITY, { }, manager)
    {}

  void Mouvement::updateEntity(float delta, Entity e)
  {
    std::shared_ptr<ECS::Position> body = getManager()->getComponent<ECS::Position>(e);

    if (body->y == 10)
      body->x++;
    if (body->y == 20)
      body->x += 2;
    (void) delta;
    std::cout << body->y << ":" << body->x << std::endl;
  }
}
