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
	explicit IngameHUD(ResourcesManager &resourceManager, GUI::Manager &, EventManager::Manager &);
	virtual ~IngameHUD() {};

	const	std::string &getName() const { return _name; }

	void	printAlert(const std::string&);
	void	hideAlert(const std::string&);

	void	onEnter();
	void	onExit();

	void	onPause() {}
	void	onResume() {}

	void	setScore(int score) { _score = score; }

	void	update(const float time, ECS::Manager &ecs, EventManager::Manager &event);

private:
	std::string				_name;

	int						_score;

	GUI::Manager			&_guiManager;
	EventManager::Manager	&_eventManager;
	ResourcesManager		&_resources;
};
