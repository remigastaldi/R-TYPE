/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2017-12-17T18:57:51+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-16T19:46:11+01:00
 */


#include  "config.hpp"

#include  "ECS/Manager.hpp"
#include  "ECS/Systems/CommonSystems.hpp"

#include  <iostream>
#include "Logger/Logger.hpp"


int main(int ac, char *av[])
{
  (void)ac;
  (void)av;

  //Config logger
  Logger::get().setOutput(CONSOLE_LOG);

  LOG_INFO << "Ceci est un test" << std::endl;
  LOG_ERROR << "Ceci est une erreur" << std::endl;

//  return 0;
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
  manager->addComponent<ECS::Position>(e2, ECS::Position(0, 20));
  manager->subscribeEntityToSystems(e2);

  manager->extractComponent<ECS::Position>(e);
  manager->subscribeEntityToSystems(e);

  for (int i = 0; i < 100; ++i) {
    manager->updateSystems(0.5 + i);
  }

  return (0);
}
