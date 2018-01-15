/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2017-12-17T18:57:51+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-15T03:32:57+01:00
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

  std::shared_ptr<ECS::Manager> manager(new ECS::Manager());

  manager->createStoreFor(ECS::Position::Type);

  manager->addSystem<ECS::Mouvement>(manager);
  manager->initSystems();

  ECS::Entity e = manager->createEntity();
  manager->addComponent<ECS::Position>(e, ECS::Position(0, 10));
  manager->subscribeEntityToSystems(e);


  ECS::Entity e2 = manager->createEntity();
  // std::shared_ptr<ECS::Position> test2(new ECS::Position(0, 20));
  manager->addComponent<ECS::Position>(e2, ECS::Position(0, 20));
  manager->subscribeEntityToSystems(e2);
  //TODO correct extractor
  // std::shared_ptr  test = manager->extractComponent<ECS::Position>(e);
  // std::cout << test->y << std::endl;
  // manager->subscribeEntityToSystems(e2);

  for (int i = 0; i < 100; ++i)
  {
    // std::shared_ptr<ECS::Store>  store = manager->getStore(ECS::Position::Type);
    // std::cout << store->has(e2) << std::endl;
    manager->updateSystems(0.5 + i);
  }

  return (0);
}
