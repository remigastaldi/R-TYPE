#include "Parallax.hpp"

Parallax::Parallax(sf::RenderWindow &win, ResourcesManager &resourcesManager) :
	_win(win),
	_layers(),
	_resources(resourcesManager)
{
}

void	Parallax::loadLayer(const std::string &layer, float speedLayer, bool flipVerticaly)
{
	_resources.load<Texture>("layer" + std::to_string(_layers.size() + 1), layer);

	sf::Sprite	sprite(_resources.getContent<Texture>("layer" + std::to_string(_layers.size() + 1)));
	sf::Sprite	flippedSprite(_resources.getContent<Texture>("layer" + std::to_string(_layers.size() + 1)));

	_layers.push_back(std::pair<sf::Sprite, float>(sprite, speedLayer));

	sf::FloatRect globalBounds = sprite.getGlobalBounds();

	if (flipVerticaly)
		flippedSprite.setTextureRect(sf::IntRect(globalBounds.width, globalBounds.height, -globalBounds.width, -globalBounds.height));
	else
		flippedSprite.setTextureRect(sf::IntRect(globalBounds.width, 0, -globalBounds.width, globalBounds.height));

	flippedSprite.setPosition(sprite.getGlobalBounds().width, 0);

	_layers.push_back(std::pair<sf::Sprite, float>(flippedSprite, speedLayer));
}

void	Parallax::update()
{
	for (auto const& it : _layers)
	{
		_win.draw(it.first);
	}
}

void	Parallax::updatePos()
{
	for (auto &it : _layers)
	{
		it.first.move(-it.second, 0);

		if (it.first.getPosition().x <  0 - it.first.getGlobalBounds().width)
			it.first.setPosition(_win.getSize().x, 0);
	}
}