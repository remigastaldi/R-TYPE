/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-19T18:05:32+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-19T18:45:47+01:00
 */


#include "StartPage/StartPage.hpp"

StartPage::StartPage(GUI::Manager& manager) :
	_manager(manager)
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
	_resources.load<Texture>("../../Client/media/img/startPage/background_04_static.png");
	_resources.load<Texture>("../../Client/media/img/startPage/button.png");
	_resources.load<Texture>("../../Client/media/img/startPage/buttonHovered.png");
	_resources.load<Font>("../../Client/media/font/Gravedigger.otf");
	_resources.load<Font>("../../Client/media/font/neuropol.ttf");

	sf::Font &font = _resources.getContent<Font>("../../Client/media/font/Gravedigger.otf");
	sf::Font &fontButtons = _resources.getContent<Font>("../../Client/media/font/neuropol.ttf");
	sf::Texture &button = _resources.getContent<Texture>("../../Client/media/img/startPage/button.png");
	sf::Texture &hoverButton = _resources.getContent<Texture>("../../Client/media/img/startPage/buttonHovered.png");

	sf::Vector2f center((_manager.getWindowSize().x / 2) - (button.getSize().x / 2), (_manager.getWindowSize().y / 2) - (button.getSize().y / 2));

	_manager.addElement<GUI::Image>("Background", sf::Vector2f(0, 0), _resources.getContent<Texture>("../../Client/media/img/startPage/background_04_static.png"), sf::Vector2f(0, 0));
	_manager.addElement<GUI::Text>("GameTitle", sf::Vector2f(center.x + 10, center.y - 300), "R-TYPE", font, 60);
	
	_manager.addElement<GUI::Button>("StartPagePlayButton", sf::Vector2f(center.x, center.y - 100), button, hoverButton, std::bind(&StartPage::funcPlay, this));
	_manager.addElement<GUI::Text>("StartPagePlayText", sf::Vector2f(810, 400), "Play", fontButtons, sf::Color::Black, 30);
	_manager.centerElementWithAnOther<GUI::Button, GUI::Text>("StartPagePlayButton", "StartPagePlayText");

	_manager.addElement<GUI::Button>("StartPageOptionsButton", sf::Vector2f(center.x, center.y), button, hoverButton, std::bind(&StartPage::funcOptions, this));
	_manager.addElement<GUI::Text>("StartPageOptionsText", sf::Vector2f(810, 500), "Options", fontButtons, sf::Color::Black, 30);
	_manager.centerElementWithAnOther<GUI::Button, GUI::Text>("StartPageOptionsButton", "StartPageOptionsText");

	_manager.addElement<GUI::Button>("StartPageExitButton", sf::Vector2f(center.x, center.y + 100), button, hoverButton, std::bind(&StartPage::funcExit, this));
	_manager.addElement<GUI::Text>("StartPageExitText", sf::Vector2f(810, 600), "Exit", fontButtons, sf::Color::Black, 30);
	_manager.centerElementWithAnOther<GUI::Button, GUI::Text>("StartPageExitButton", "StartPageExitText");
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
