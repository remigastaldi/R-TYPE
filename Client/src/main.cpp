/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2017-12-17T18:57:51+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-14T02:01:56+01:00
 */


#include  "config.hpp"

#include  "ECS/Manager.hpp"
#include  "ECS/Systems/CommonSystems.hpp"

#include  <iostream>

int     main(int ac, char *av[])
{
  (void)ac;
  (void)av;

  if constexpr (DEBUG)
    std::cout << "DEBUG ON" << std::endl;

  ECS::Manager manager;
  std::observer_ptr<ECS::Manager> managerPointer(&manager);

  manager.createStoreFor(ECS::Position::Type);

  manager.addSystem<ECS::Mouvement>(managerPointer);
  manager.initSystems();

  ECS::Entity e = manager.createEntity();
  manager.addComponent(e, new ECS::Position(0, 10));
  manager.subscribeEntityToSystems(e);


  ECS::Entity e2 = manager.createEntity();
  manager.addComponent(e2, new ECS::Position(0, 20));
  manager.subscribeEntityToSystems(e2);

  for (int i = 0; i < 100; ++i)
  {
    manager.updateSystems(0.5 + i);
  }

  return (0);
}
