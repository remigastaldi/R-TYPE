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
	_resources.load<Texture>("../../Client/media/img/startPage/startPageBackground3.jpg");
	_resources.load<Texture>("../../Client/media/img/startPage/button.png");
	_resources.load<Texture>("../../Client/media/img/startPage/buttonHovered.png");
	_resources.load<Font>("../../Client/media/font/Gravedigger.otf");
	std::function<void(void)> playFunc = std::bind(&StartPage::funcPlay, this);
	std::function<void(void)> optionsFunc = std::bind(&StartPage::funcOptions, this);
	std::function<void(void)> exitFunc = std::bind(&StartPage::funcExit, this);

	_manager.addElement<GUI::Image>("Background", sf::Vector2f(0, 0), _resources.getContent<Texture>("../../Client/media/img/startPage/startPageBackground3.jpg"));
	_manager.addElement<GUI::Text>("GameTitle", sf::Vector2f(160,200), "R-TYPE", _resources.getContent<Font>("../../Client/media/font/Gravedigger.otf"), 60);

	_manager.addElement<GUI::Button>("StartPagePlayButton", sf::Vector2f(150, 400), _resources.getContent<Texture>("../../Client/media/img/startPage/button.png"), _resources.getContent<Texture>("../../Client/media/img/startPage/buttonHovered.png"),
		"Play", _resources.getContent<Font>("../../Client/media/font/Gravedigger.otf"), playFunc, sf::Color::Black);
	_manager.addElement<GUI::Button>("StartPageOptionsButton", sf::Vector2f(150, 500), _resources.getContent<Texture>("../../Client/media/img/startPage/button.png"), _resources.getContent<Texture>("../../Client/media/img/startPage/buttonHovered.png"),
		"Options", _resources.getContent<Font>("../../Client/media/font/Gravedigger.otf"), optionsFunc, sf::Color::Black);
	_manager.addElement<GUI::Button>("StartPageExitButton", sf::Vector2f(150, 600), _resources.getContent<Texture>("../../Client/media/img/startPage/button.png"),
		_resources.getContent<Texture>("../../Client/media/img/startPage/buttonHovered.png"), "Exit", _resources.getContent<Font>("../../Client/media/font/Gravedigger.otf"), std::bind(&StartPage::funcExit, this), sf::Color::Black);
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
