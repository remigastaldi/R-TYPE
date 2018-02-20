#pragma once

#include <GameManagers.hpp>

void registerRessources(GameEngine::GameManagers &_managers)
{
  _managers.resources.load<Texture>("metallos_texture", "../../Client/media/img/ship/enemies/CX16-X2.png");
  _managers.resources.load<Texture>("player_ship_texture", "../../Client/media/img/ship/allies/playersSpaceships.png");
  _managers.resources.load<Texture>("player_missiles_texture", "../../Client/media/img/ship/allies/playersMissiles.png");
  _managers.resources.load<Texture>("parallax_01", "../../Client/media/img/Parallax/background_01_parallax_01.png");
  _managers.resources.load<Texture>("parallax_02", "../../Client/media/img/Parallax/background_01_parallax_02.png");
  _managers.resources.load<Texture>("parallax_03", "../../Client/media/img/Parallax/background_01_parallax_03.png");
  _managers.resources.load<Texture>("basick_attack_texture", "../../Client/media/img/ship/enemies/bullet_blaster_big_single.png");
  _managers.resources.load<Font>("neuropol", "../../Client/media/font/neuropol.ttf");
  _managers.resources.load<Texture>("scoreSprite", "../../Client/media/img/ingameHUD/scoreSprite.png");
  _managers.resources.load<Texture>("heart", "../../Client/media/img/ingameHUD/hearth.png");
  _managers.resources.load<Texture>("lobbiesBackground", "../../Client/media/img/lobbiesBackground.jpg");
  _managers.resources.load<Texture>("startButtons", "../../Client/media/img/startPage/startButtons.png");
  _managers.resources.load<Font>("Gravedigger", "../../Client/media/font/Gravedigger.otf");
  _managers.resources.load<Font>("neuropol", "../../Client/media/font/neuropol.ttf");
  _managers.resources.load<Texture>("lobbiesBackground", "../../Client/media/img/lobbiesBackground.jpg");
  _managers.resources.load<Texture>("window_whole", "../../Client/media/img/playerLobby/window_whole.png");
  _managers.resources.load<Texture>("window_bottom", "../../Client/media/img/playerLobby/window_bottom.png");
  _managers.resources.load<Texture>("playersSpaceships", "../../Client/media/img/ship/allies/playersSpaceships.png");
  _managers.resources.load<Texture>("exitButton", "../../Client/media/img/playerLobby/exitButton.png");
  _managers.resources.load<Texture>("readyButtonState", "../../Client/media/img/playerLobby/readyButtonState.png");
  _managers.resources.load<Texture>("readyButton", "../../Client/media/img/playerLobby/readyButton.png");
  _managers.resources.load<Font>("neuropol", "../../Client/media/font/neuropol.ttf");
}

#ifdef WIN32
extern "C" char const * __declspec(dllexport) __stdcall getName()
{
  return "BasicRessources";
}

extern "C" void __declspec(dllexport) __stdcall getSymbol(GameEngine::GameManagers &_managers)
{
  registerRessources(_managers);
}

#else

extern "C" char const *getName()
{
  return "BasicRessources";
}

extern "C" void getSymbol(GameEngine::GameManagers &_managers)
{
  registerRessources(_managers);
}

#endif