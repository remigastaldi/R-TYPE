/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2017-12-17T18:57:51+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-19T18:49:42+01:00
 */

#include  "Client.hpp"
#include "DynamicLibrary/LibLoader.hpp"

int main(int ac, char *av[])
{
  //Config logger
  Logger::get().setOutput(CONSOLE_LOG);

  if constexpr (DEBUG)
    std::cout << "DEBUG ON" << std::endl;

  LibLoader l;
  l.move.addFolder("");

  std::string ip("localhost");
  if (ac > 1)
  {
    ip = av[1];
  }

  sf::VideoMode videoMode(1920,1080);
  GameEngine::Client client(ip, videoMode);

  client.init();
  client.run();


//   ECS::Entity e = manager.createEntity();
//   manager.addComponent<ECS::Position>(e, ECS::Position(0, 10));
//   manager.updateEntityToSystems(e);
//
//   ECS::Entity e2 = manager.createEntity();
//   manager.addComponent<ECS::Position>(e2, ECS::Position(0, 20));
//   manager.updateEntityToSystems(e2);
//
//   manager.extractComponent<ECS::Position>(e);
//   manager.updateEntityToSystems(e);
//
//   for (int i = 0; i < 100; ++i) {
//     manager.updateSystems(0.5 + i);
//   }
//
// //  Resource manager example
//   ResourcesManager resourceManager;
//
//   resourceManager.load<Font>("font.otf");
//   resourceManager.load<Texture>("oui.png");
//   resourceManager.load<Texture>("os_arch.png");
//
//   std::shared_ptr<Font> texut = resourceManager.get<Font>("font.otf");
//   sf::Font &text = resourceManager.getContent<Font>("font.otf");
//
//   sf::Texture &texture1 = resourceManager.getContent<Texture>("oui.png");
//   sf::Texture &texture2 = resourceManager.getContent<Texture>("os_arch.png");

  //
  // sf::RenderWindow window(sf::VideoMode(800, 600), "win", sf::Style::None);

  //Manager example
  // GUI::Manager Manager(window);
  // Manager.addElement<GUI::Text>("Button", pos, "BONSOIR BONSOIR", text, 30);
  // Manager.update(10.f);
  //run the program as long as the window is open
  // sf::Vector2 pos(10.f, 10.f);
  // sf::Vector2 pos2(20.f, 10.f);
  // Manager.addElement<GUI::Button>("test",pos2 , texture1, texture2, "Bouton", text, test, 20);
  // while (window.isOpen())
  // {
  //     // check all the window's events that were triggered since the last iteration of the loop
  //     sf::Event event;
  //     while (window.pollEvent(event))
  //     {
  //         // "close requested" event: we close the window
  //         if (event.type == sf::Event::Closed)
  //             window.close();
  //     }
  //     window.clear();
  //     window.display();
  // }

  return (0);
}
