#include "IngameHUD.hpp"

IngameHUD::IngameHUD(ResourcesManager &resourceManager, GUI::Manager& guiManager, EventManager::Manager &eventManager)
	: _name("LobbyPlayer"),
		_score(0),
_guiManager(guiManager),
	_eventManager(eventManager),
	_resources(resourceManager)
{

}

void	IngameHUD::printAlert(const std::string&string)
{
	_guiManager.addElement<GUI::Text>(string, sf::Vector2f(0, 0), string, _resources.getContent<Font>("neuropol"), 30);
	std::shared_ptr<GUI::Text> text = _guiManager.getElement<GUI::Text>(string);

	text->setPosition(sf::Vector2f((_guiManager.getWindowSize().x / 2) - (text->getTextureRect().width / 2), 100));
}

void	IngameHUD::hideAlert(const std::string&string)
{
	_guiManager.release(string);
}

void	IngameHUD::onEnter()
{
	_resources.load<Font>("neuropol", "../../Client/media/font/neuropol.ttf");
	_resources.load<Texture>("scoreSprite", "../../Client/media/img/ingameHUD/scoreSprite.png");
	_resources.load<Texture>("hearth", "../../Client/media/img/ingameHUD/hearth.png");

	_guiManager.addElement<GUI::Image>("scoreBox", sf::Vector2f(-50, 0), _resources.getContent<Texture>("scoreSprite"), sf::Vector2f(0.7, 0.5));
	_guiManager.addElement<GUI::Text>("scoreText", sf::Vector2f(0, 0), std::to_string(_score), _resources.getContent<Font>("neuropol"), 30);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Text>("scoreBox", "scoreText", 0, 0);
	_guiManager.addElement<GUI::Image>("hearth1", sf::Vector2f(100, 130), _resources.getContent<Texture>("hearth"), sf::Vector2f(1, 1));
	_guiManager.addElement<GUI::Image>("hearth2", sf::Vector2f(50, 130), _resources.getContent<Texture>("hearth"), sf::Vector2f(1, 1));
	_guiManager.addElement<GUI::Image>("hearth3", sf::Vector2f(0, 130), _resources.getContent<Texture>("hearth"), sf::Vector2f(1, 1));
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
