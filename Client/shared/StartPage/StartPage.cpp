/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-19T18:05:32+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-20T03:44:09+01:00
 */


#include "StartPage/StartPage.hpp"

StartPage::StartPage(GUI::Manager& guiManager, EventManager::Manager &eventManager)
	:	_guiManager(guiManager),
	_eventManager(eventManager)
{

}

void	StartPage::funcPlay(void)
{
}


void	StartPage::funcOptions(void)
{
}

void	StartPage::funcExit(void)
{
	//_window.close();
}

void	StartPage::onEnter()
{
	_resources.load<Texture>("../../Client/media/img/startPage/background_02_static.jpg");
	_resources.load<Texture>("../../Client/media/img/startPage/rip2.png");
	//_resources.load<Texture>("../../Client/media/img/startPage/buttonHovered.png");
	_resources.load<Font>("../../Client/media/font/Gravedigger.otf");
	_resources.load<Font>("../../Client/media/font/neuropol.ttf");

	sf::Font &font = _resources.getContent<Font>("../../Client/media/font/Gravedigger.otf");
	sf::Font &fontButtons = _resources.getContent<Font>("../../Client/media/font/neuropol.ttf");
	sf::Texture &button = _resources.getContent<Texture>("../../Client/media/img/startPage/rip2.png");
	//sf::Texture &hoverButton = _resources.getContent<Texture>("../../Client/media/img/startPage/buttonHovered.png");
	sf::Sprite startButton(button);
	sf::Sprite startButtonHovered(button);
	sf::Sprite optionsButton(button);
	sf::Sprite optionsButtonHovered(button);
	sf::Sprite exitButton(button);
	sf::Sprite exitButtonHovered(button);
	
	startButton.setTextureRect(sf::IntRect(0, 0, 1132, 348));
	startButtonHovered.setTextureRect(sf::IntRect(1132, 0, 1132, 348));
	optionsButton.setTextureRect(sf::IntRect(0, 348, 1132, 348));
	optionsButtonHovered.setTextureRect(sf::IntRect(1132, 348, 1132, 348));
	exitButton.setTextureRect(sf::IntRect(0, 696, 1132, 348));
	exitButtonHovered.setTextureRect(sf::IntRect(1132, 696, 1132, 348));
	startButton.setScale(0.5, 0.5);
	startButtonHovered.setScale(0.5, 0.5);
	optionsButton.setScale(0.5, 0.5);
	optionsButtonHovered.setScale(0.5, 0.5);
	exitButton.setScale(0.5, 0.5);
	exitButtonHovered.setScale(0.5, 0.5);

	sf::Vector2f center((_guiManager.getWindowSize().x / 2) - (startButton.getGlobalBounds().width / 2), (_guiManager.getWindowSize().y / 2) - (startButton.getGlobalBounds().height / 2));
	
	_guiManager.addElement<GUI::Image>("Background", sf::Vector2f(0, 0), _resources.getContent<Texture>("../../Client/media/img/startPage/background_02_static.jpg"), sf::Vector2f(0, 0));
	_guiManager.addElement<GUI::Text>("GameTitle", sf::Vector2f(center.x + 100, center.y - 300), "R-TYPE", font, 60);

	_guiManager.addElement<GUI::Button>("StartPagePlayButton", _eventManager, "PlayGameEvent", sf::Vector2f(center.x - 100, center.y - 100), startButton, startButtonHovered);
	_guiManager.addElement<GUI::Text>("StartPagePlayText", sf::Vector2f(810, 400), "Play", fontButtons, sf::Color::White, 30);
	_guiManager.centerElementWithAnOther<GUI::Button, GUI::Text>("StartPagePlayButton", "StartPagePlayText");

	_guiManager.addElement<GUI::Button>("StartPageOptionsButton", _eventManager, "OptionsEvent" ,sf::Vector2f(center.x, center.y + 100), optionsButton, optionsButtonHovered);
	_guiManager.addElement<GUI::Text>("StartPageOptionsText", sf::Vector2f(810, 500), "Options", fontButtons, sf::Color::White, 30);
	_guiManager.centerElementWithAnOther<GUI::Button, GUI::Text>("StartPageOptionsButton", "StartPageOptionsText");

	_guiManager.addElement<GUI::Button>("StartPageExitButton", _eventManager, "ExitGameEvent" ,sf::Vector2f(center.x + 100, center.y + 300), exitButton, exitButtonHovered);
	_guiManager.addElement<GUI::Text>("StartPageExitText", sf::Vector2f(810, 600), "Exit", fontButtons, sf::Color::White, 30);
	_guiManager.centerElementWithAnOther<GUI::Button, GUI::Text>("StartPageExitButton", "StartPageExitText");


}

void	StartPage::onExit()
{

}

void	StartPage::update(const float time, ECS::Manager &ecs, EventManager::Manager &event)
{
	(void)time;
	(void)ecs;
	(void)event;
}
