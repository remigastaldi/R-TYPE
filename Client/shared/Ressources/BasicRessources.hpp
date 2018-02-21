#pragma once

#include <GameManagers.hpp>

void registerRessources(GameEngine::GameManagers &_managers)
{
  //Texture
  _managers.resources.load<Texture>("metallos_texture", "../../Client/media/img/ship/enemies/CX16-X2.png");
  _managers.resources.load<Texture>("blue_texture", "../../Client/media/img/ship/enemies/WO84-wu-X3.png");
  _managers.resources.load<Texture>("player_ship_texture", "../../Client/media/img/ship/allies/playersSpaceships.png");

  //Missiles
  _managers.resources.load<Texture>("player_missiles_texture", "../../Client/media/img/ship/allies/playersMissiles.png");
  _managers.resources.load<Texture>("player_missiles_texture_red", "../../Client/media/img/ship/enemies/rocket_bx_single.png");
  _managers.resources.load<Texture>("basick_attack_texture", "../../Client/media/img/ship/enemies/bullet_blaster_big_single.png");
  _managers.resources.load<Texture>("bomb_texture", "../../Client/media/img/ship/enemies/cluster_bomb_single.png");
  _managers.resources.load<Texture>("mini_bomb_texture", "../../Client/media/img/ship/enemies/cluster_bomb_single_cluster.png");

  //Animations
  _managers.resources.load<Texture>("bomb_explosion", "../../Client/media/img/ship/explosion.png");

  _managers.resources.load<Texture>("parallax_01", "../../Client/media/img/Parallax/background_01_parallax_01.png");
  _managers.resources.load<Texture>("parallax_02", "../../Client/media/img/Parallax/background_01_parallax_02.png");
  _managers.resources.load<Texture>("parallax_03", "../../Client/media/img/Parallax/background_01_parallax_03.png");
  _managers.resources.load<Texture>("scoreSprite", "../../Client/media/img/ingameHUD/scoreSprite.png");
  _managers.resources.load<Texture>("heart", "../../Client/media/img/ingameHUD/heart.png");
  _managers.resources.load<Texture>("border", "../../Client/media/img/ingameHUD/border.png");
  _managers.resources.load<Texture>("border2", "../../Client/media/img/ingameHUD/border2.png");
  _managers.resources.load<Texture>("lobbiesBackground", "../../Client/media/img/lobbiesBackground.jpg");
  _managers.resources.load<Texture>("startButtons", "../../Client/media/img/StartScene/startButtons.png");
  _managers.resources.load<Texture>("lobbiesBackground", "../../Client/media/img/lobbiesBackground.jpg");
  _managers.resources.load<Texture>("window_whole", "../../Client/media/img/playerLobby/window_whole.png");
  _managers.resources.load<Texture>("window_bottom", "../../Client/media/img/playerLobby/window_bottom.png");
  _managers.resources.load<Texture>("playersSpaceships", "../../Client/media/img/ship/allies/playersSpaceships.png");
  _managers.resources.load<Texture>("exitButton", "../../Client/media/img/playerLobby/exitButton.png");
  _managers.resources.load<Texture>("readyButtonState", "../../Client/media/img/playerLobby/readyButtonState.png");
  _managers.resources.load<Texture>("readyButton", "../../Client/media/img/playerLobby/readyButton.png");
  
  //Font
  _managers.resources.load<Font>("Gravedigger", "../../Client/media/font/Gravedigger.otf");
  _managers.resources.load<Font>("neuropol", "../../Client/media/font/neuropol.ttf");
}

#ifdef WIN32
extern "C" char const  __declspec(dllexport) *getName()
{
  return "BasicRessources";
}

extern "C" void __declspec(dllexport) getSymbol(GameEngine::GameManagers &_managers)
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