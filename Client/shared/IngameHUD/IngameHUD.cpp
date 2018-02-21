#include "IngameHUD.hpp"

IngameHUD::IngameHUD(ResourcesManager &resourceManager, GUI::Manager& guiManager, EventManager::Manager &eventManager)
	: _name("LobbyPlayer"),
		_score(0),
_guiManager(guiManager),
	_eventManager(eventManager),
	_resources(resourceManager)
{
	_eventManager.listen<int, std::string>("printAlert", [&] (std::string ev) -> int {
		printAlert(ev);
		return 0;
	});

	_eventManager.listen<int, std::string>("hideAlert", [&] (std::string ev) -> int {
		hideAlert(ev);
		return 0;
	});
}

void	IngameHUD::printAlert(std::string string)
{
	_guiManager.addElement<GUI::Text>(string, sf::Vector2f(0, 0), string, _resources.getContent<Font>("neuropol"), 30);
	std::shared_ptr<GUI::Text> text = _guiManager.getElement<GUI::Text>(string);

	text->setPosition(sf::Vector2f((_guiManager.getWindowSize().x / 2) - (text->getTextureRect().width / 2), 100));
}

void	IngameHUD::hideAlert(std::string string)
{
	_guiManager.release(string);
}

void	IngameHUD::onEnter()
{
	_resources.get<Font>("neuropol");
	_resources.get<Texture>("scoreSprite");
	_resources.get<Texture>("heart");

	_guiManager.addElement<GUI::Image>("scoreBox", sf::Vector2f(-50, 0), _resources.getContent<Texture>("scoreSprite"), sf::Vector2f(0.7, 0.5));
	_guiManager.addElement<GUI::Text>("scoreText", sf::Vector2f(0, 0), std::to_string(_score), _resources.getContent<Font>("neuropol"), 30);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Text>("scoreBox", "scoreText", 0, 0);
	_guiManager.addElement<GUI::Image>("heart1", sf::Vector2f(100, 130), _resources.getContent<Texture>("heart"), sf::Vector2f(1, 1));
	_guiManager.addElement<GUI::Image>("heart2", sf::Vector2f(50, 130), _resources.getContent<Texture>("heart"), sf::Vector2f(1, 1));
	_guiManager.addElement<GUI::Image>("heart3", sf::Vector2f(0, 130), _resources.getContent<Texture>("heart"), sf::Vector2f(1, 1));
}

void	IngameHUD::onExit()
{
	_guiManager.releaseAll();
}

void	IngameHUD::update(const float time, ECS::Manager &ecs, EventManager::Manager &event)
{
	(void)time;
	(void)ecs;
	(void)event;
}
