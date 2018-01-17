#include "GUI.hpp"
#include "ResourcesManager.hpp"
#include "Resources.hpp"

sf::Sprite	&&GUI::loadSprite(sf::Texture& texture, sf::Vector2f position)
{
	sf::Sprite sprite(texture);

	sprite.setPosition(position.x, position.y);

	return std::move(sprite);
}

GUI::Button::Button(sf::Vector2f position, sf::Texture& normalTexture, sf::Texture& hoverTexture,
					std::string text, sf::Font& font, std::function<void(void)> function, sf::Color colorText, 
					int sizeText) :
	_position(position),
	_function(function),
	_isButtonPressed(false)
	{
		_normalSprite = loadSprite(normalTexture, position);
		_hoverSprite = loadSprite(hoverTexture, position);
		loadText(text, font, colorText, sizeText);
	}

void	GUI::Button::loadText(std::string text, sf::Font& font, sf::Color color, int size)
{
	_text.setFont(font);
	_text.setString(text);
	_text.setColor(color);
	_text.setCharacterSize(size);
	_text.setPosition(_position.x + (_normalSprite.getGlobalBounds().width / 2) - (_text.getGlobalBounds().width / 2), _position.y + (_normalSprite.getGlobalBounds().height / 2) - (_text.getGlobalBounds().top + _text.getGlobalBounds().height / 2));
}

void	GUI::Button::draw(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
		_normalSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
		_function();
	else 
	{
		if (_normalSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
			window.draw(_hoverSprite);
		else
			window.draw(_normalSprite);
		window.draw(_text);
	}
}

GUI::Checkbox::Checkbox(sf::Vector2f position, sf::Texture& uncheckedTexture, sf::Texture& checkedTexture, std::function<void(void)> function) :
	_position(position),
	_function(function),
	_isChecked(false)
{
	_uncheckedSprite = loadSprite(uncheckedTexture, position);
	_checkedSprite = loadSprite(checkedTexture, position);
}

#include <iostream>

void	GUI::Checkbox::draw(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
		_uncheckedSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
		_isChecked = !_isChecked;

	if (_isChecked)
	{
		std::cout << "checked" << std::endl;
		_function();
		window.draw(_checkedSprite);
	}
	else
	{
		std::cout << "unchecked" << std::endl;
		window.draw(_uncheckedSprite);
	}
}