/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-19T18:05:32+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-20T01:23:10+01:00
 */


#pragma once

#include "LibraryInterfaces/IScene.hpp"
#include "ResourcesManager.hpp"
#include "Resources.hpp"
#include "GUIElements.hpp"
#include "GUIManager.hpp"
#include "EventManager.hpp"

class StartPage : IScene
{
public:
	explicit StartPage(GUI::Manager &, EventManager::Manager &);
	virtual ~StartPage() {};

	const	std::string &getName() const { return _name; }

	void	onEnter();
	void	onExit();

	void	onPause() {}
	void	onResume() {}

	void	update(const float time, ECS::Manager &ecs, EventManager::Manager &event);
	void	funcPlay(void);
	void	funcOptions(void);
	void	funcExit(void);

private:
	std::string			_name;

	GUI::Manager	&_guiManager;
	EventManager::Manager	&_eventManager;
	ResourcesManager	_resources;
};
