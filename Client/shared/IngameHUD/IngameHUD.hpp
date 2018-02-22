/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T15:02:12+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-21T03:46:40+01:00
 */


#pragma once

#include "LibraryInterfaces/IScene.hpp"
#include "ResourcesManager.hpp"
#include "Resources.hpp"
#include "GUIElements.hpp"
#include "GUIManager.hpp"
#include "EventManager.hpp"

#include <string>

class IngameHUD : public IScene
{
public:
	explicit IngameHUD(ResourcesManager &resourceManager, GUI::Manager& guiManager, EventManager::Manager &eventManager);
	virtual ~IngameHUD() {};

	const	std::string &getName() const { return _name; }

	void	printAlert(std::string);
	void	hideAlert(std::string);

	void	onEnter();
	void	onExit();

	void	onPause() {}
	void	onResume() {}

	void	setScore(int score) { _score = score; }

	void	update();

	void  changePlayerHealth(const std::string &playerName, int health);

private:
	std::string				_name;
	std::vector<std::tuple<std::shared_ptr<GUI::Image>, int, int>>	_border;
	int						_score;

	GUI::Manager			&_guiManager;
	EventManager::Manager	&_eventManager;
	ResourcesManager		&_resources;

	std::unordered_map<std::string, int> _playersHealth;
	std::unordered_map<std::string, EventManager::EventListener>  _listeners;
};
