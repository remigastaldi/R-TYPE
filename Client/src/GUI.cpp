#include "GUI.hpp"
#include "ResourcesManager.hpp"
#include "Resources.hpp"

GUI::Button::Button(sf::Vector2f position, sf::Texture& normalTexture, sf::Texture& hoverTexture,
					std::string text, sf::Font& font, std::function<void(void)> function, sf::Color colorText, 
					int sizeText) :
	_position(position),
	_function(function),
	_isButtonPressed(false)
	{
	_normalSprite = loadSprite(normalTexture);
	_hoverSprite = loadSprite(hoverTexture);
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

sf::Sprite	GUI::Button::loadSprite(sf::Texture& texture)
{
	sf::Sprite sprite(texture);

	sprite.setPosition(_position.x, _position.y);

	return sprite;
}

void	GUI::Button::draw(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
		_normalSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) && _isButtonPressed == false)
		_isButtonPressed = true;
	if (_isButtonPressed == true)
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

void GUI::Button::checkClick(sf::Vector2i mousePos)
{
	if (_normalSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
		_function();
}