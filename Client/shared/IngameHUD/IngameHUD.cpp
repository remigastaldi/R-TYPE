/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-21T00:50:03+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-21T03:48:16+01:00
 */


#include "IngameHUD.hpp"

IngameHUD::IngameHUD(ResourcesManager &resourceManager, GUI::Manager& guiManager, EventManager::Manager &eventManager)
	: _name("LobbyPlayer"),
		_score(0),
		_guiManager(guiManager),
		_eventManager(eventManager),
		_resources(resourceManager),
		_playersHealth({{"playerHeart", 3}}),
		_listeners()
	{
		_listeners["printAlert"] = _eventManager.listen<int, std::string>("printAlert", [&] (const std::string &ev) -> int {
			printAlert(ev);
			return (0);
	});

	_listeners["hideAlert"] = _eventManager.listen<int, std::string>("hideAlert", [&] (const std::string &ev) -> int {
			hideAlert(ev);
			return (0);
	});

	_listeners["changePlayerHealth"] = _eventManager.listen<int, std::string, int>("changePlayerHealth", [&] (const std::string &playerName, int health) -> int {
		changePlayerHealth(playerName, health);
		return (0);
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
	_resources.get<Texture>("border");
	_resources.get<Texture>("border2");
	
	
	for (int i = 1 ; i < 36 ; ++i)
	{
		if (i < 18)
		{
			if (rand() % 2 == 1)
				_border.emplace_back(std::make_tuple<std::shared_ptr<GUI::Image>, int, int>(_guiManager.addElement<GUI::Image>("border" + std::to_string(i), sf::Vector2f((121 + (rand() % 8)) * (i - 1), 50 + (rand() % 6)), _resources.getContent<Texture>("border2"), sf::Vector2f(1, 1)), (rand() % 2) + 1, (rand() % 3) + 1));
			else
				_border.emplace_back(std::make_tuple<std::shared_ptr<GUI::Image>, int, int>(_guiManager.addElement<GUI::Image>("border" + std::to_string(i), sf::Vector2f((121 + (rand() % 8)) * (i - 1), 50 + (rand() % 6)), _resources.getContent<Texture>("border"), sf::Vector2f(1, 1)), (rand() % 2) + 1, (rand() % 3) + 1));
		}
		else
		{
			if (rand() % 2 == 1)
				_border.emplace_back(std::make_tuple<std::shared_ptr<GUI::Image>, int, int>(_guiManager.addElement<GUI::Image>("border" + std::to_string(i), sf::Vector2f((121 + (rand() % 8)) * ((i - 18) - 1), 1030 + (rand() % 6)), _resources.getContent<Texture>("border2"), sf::Vector2f(1, 1)), (rand() % 2) + 1, (rand() % 3) + 1));
			else
				_border.emplace_back(std::make_tuple<std::shared_ptr<GUI::Image>, int, int>(_guiManager.addElement<GUI::Image>("border" + std::to_string(i), sf::Vector2f((121 + (rand() % 8)) * ((i - 18) - 1), 1030 + (rand() % 6)), _resources.getContent<Texture>("border"), sf::Vector2f(1, 1)), (rand() % 2) + 1, (rand() % 3) + 1));
		}

		std::get<0>(_border.at(i - 1))->setOrigin(sf::Vector2f(61, 51));
		
	}

	_guiManager.addElement<GUI::Image>("scoreBox", sf::Vector2f(-50, 100), _resources.getContent<Texture>("scoreSprite"), sf::Vector2f(0.7, 0.5));
	_guiManager.addElement<GUI::Text>("scoreText", sf::Vector2f(0, 100), std::to_string(_score), _resources.getContent<Font>("neuropol"), 30);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Text>("scoreBox", "scoreText", 0, 0);
	_guiManager.addElement<GUI::Image>("playerHeart1", sf::Vector2f(0, 230), _resources.getContent<Texture>("heart"), sf::Vector2f(1, 1));
	_guiManager.addElement<GUI::Image>("playerHeart2", sf::Vector2f(50, 230), _resources.getContent<Texture>("heart"), sf::Vector2f(1, 1));
	_guiManager.addElement<GUI::Image>("playerHeart3", sf::Vector2f(100, 230), _resources.getContent<Texture>("heart"), sf::Vector2f(1, 1));
}

void	IngameHUD::onExit()
{
	_guiManager.releaseAll();
	_eventManager.unlisten<int, std::string>("printAlert", _listeners["printAlert"]);
	_eventManager.unlisten<int, std::string>("hideAlert", _listeners["hideAlert"]);
	_eventManager.unlisten<int, std::string>("changePlayerHealth", _listeners["changePlayerHealth"]);
}

void	IngameHUD::update()
{
	int i = 0;

	for (auto &it : _border)
	{
		std::get<0>(it)->setRotate(std::get<2>(it));
		std::get<0>(it)->setPosition(sf::Vector2f(std::get<0>(it)->getPosition().x - std::get<1>(it), std::get<0>(it)->getPosition().y));

		if (std::get<0>(it)->getPosition().x < -61)
			std::get<0>(it)->setPosition(sf::Vector2f(121 * 17, std::get<0>(it)->getPosition().y));
	}
}

void  IngameHUD::changePlayerHealth(const std::string &playerName, int health)
{
	(void) playerName;
	if (health < _playersHealth["playerHeart"])
	{
		for (int i = _playersHealth["playerHeart"]; i > health; --i)
		{
			_guiManager.release("playerHeart" + std::to_string(i));
		}
	}
	else
	{
		for (int i = _playersHealth["playerHeart"]; i < health; ++i)
		{
			_guiManager.addElement<GUI::Image>("playerHeart" + std::to_string(i), sf::Vector2f(i * 50, 130), _resources.getContent<Texture>("heart"), sf::Vector2f(1, 1));
		}
	}
}
