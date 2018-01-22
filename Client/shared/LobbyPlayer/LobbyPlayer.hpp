/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T18:35:48+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T02:08:08+01:00
 */


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
	explicit LobbyPlayer(ResourcesManager &resourceManager, GUI::Manager &, EventManager::Manager &);
	virtual ~LobbyPlayer() {};

	const	std::string &getName() const { return _name; }

	void	playerJoin(const std::string &);
	void	playerLeave(const std::string &);

	void	onEnter();
	void	onExit();

	void	onPause() {}
	void	onResume() {}

	void	update(const float time, ECS::Manager &ecs, EventManager::Manager &event);

private:
	std::string				_name;

	GUI::Manager			&_guiManager;
	EventManager::Manager	&_eventManager;
	ResourcesManager		&_resources;

	int _players;
};
