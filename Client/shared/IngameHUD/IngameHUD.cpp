#include "IngameHUD.hpp"

IngameHUD::IngameHUD(ResourcesManager &resourceManager, GUI::Manager& guiManager, EventManager::Manager &eventManager)
	: _name("LobbyPlayer"),
	_guiManager(guiManager),
	_eventManager(eventManager),
	_resources(resourceManager)
{

}

void	IngameHUD::onEnter()
{
}

void	IngameHUD::onExit()
{

}

void	IngameHUD::update(const float time, ECS::Manager &ecs, EventManager::Manager &event)
{
	(void)time;
	(void)ecs;
	(void)event;
}
