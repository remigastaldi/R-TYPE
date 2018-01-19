#pragma once

#include "LibraryInterfaces\IScene.hpp"
#include "ResourcesManager.hpp"
#include "Resources.hpp"
#include "GUIElements.hpp"
#include "GUIManager.hpp"

class StartPage : IScene
{
public:
	StartPage(GUI::Manager&);
	~StartPage() {}

	const	std::string &getName() const { return _name; }

	void	onEnter();
	void	onExit();

	void	onPause() {}
	void	onResume() {}

	void	update(const float time, ECS::Manager &ecs, Alfred::EventManager::Manager &event);
	void	StartPage::funcPlay(void);
	void	StartPage::funcOptions(void);
	void	StartPage::funcExit(void);

private:
	std::string			_name;

	GUI::Manager&		_manager;
	ResourcesManager	_resources;
};