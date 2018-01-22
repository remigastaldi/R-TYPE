#pragma once

#include "ResourcesManager.hpp"
#include "Resources.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Parallax
{
public:
	Parallax(sf::RenderWindow&, ResourcesManager&);

	void	loadLayer(const std::string&, float, bool);
	void	update();
	void	updatePos();

private:
	sf::RenderWindow		&_win;

	std::vector<std::pair<sf::Sprite, float>>	_layers;

	ResourcesManager		&_resources;
};
