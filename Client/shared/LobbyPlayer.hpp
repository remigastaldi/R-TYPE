#pragma once

#include "LibraryInterfaces/IScene.hpp"
#include "ResourcesManager.hpp"
#include "Resources.hpp"
#include "GUIElements.hpp"
#include "GUIManager.hpp"
#include "EventManager.hpp"

class LobbyPlayer : IScene
{
public:
	explicit LobbyPlayer(GUI::Manager &, EventManager::Manager &);
	virtual ~LobbyPlayer() {};

	const	std::string &getName() const { return _name; }

	void	onEnter();
	void	onExit();

	void	onPause() {}
	void	onResume() {}

	void	update(const float time, ECS::Manager &ecs, EventManager::Manager &event);

private:
	std::string				_name;

	GUI::Manager			&_guiManager;
	EventManager::Manager	&_eventManager;
	ResourcesManager		_resources;
};
