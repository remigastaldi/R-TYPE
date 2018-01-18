/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-17T14:12:41+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-18T14:55:36+01:00
 */


#include "GUIElements.hpp"
#include "ResourcesManager.hpp"
#include "Resources.hpp"

sf::Sprite	GUI::loadSprite(const sf::Texture& texture, const sf::Vector2f& position)
{
	sf::Sprite sprite(texture);

	sprite.setPosition(position.x, position.y);

	return (sprite);
}

GUI::Button::Button(const sf::Vector2f& position, const sf::Texture& normalTexture, const sf::Texture& hoverTexture,
	const std::string& text, const sf::Font& font, const std::function<void(void)>& function, const sf::Color colorText,
	size_t textSize)
		: _function(function),
	_position(position),
	_normalSprite(loadSprite(normalTexture, position)),
	_clickedSprite(),
	_hoverSprite(loadSprite(hoverTexture, position)),
	_text(text, font, textSize)
{
	_text.setFillColor(colorText);
	_text.setPosition(_position.x + (_normalSprite.getGlobalBounds().width / 2) - (_text.getGlobalBounds().width / 2), _position.y + (_normalSprite.getGlobalBounds().height / 2) - (_text.getGlobalBounds().top + _text.getGlobalBounds().height / 2));
}

GUI::Button::Button(const sf::Vector2f& position, const sf::Texture& normalTexture, const sf::Texture& hoverTexture,
	const std::string& text, const sf::Font& font, const std::function<void(void)>& function, size_t textSize)
		:	_function(function),
		_position(position),
		_normalSprite(loadSprite(normalTexture, position)),
		_clickedSprite(),
		_hoverSprite(loadSprite(hoverTexture, position)),
		_text(text, font, textSize)
{
	_text.setPosition(_position.x + (_normalSprite.getGlobalBounds().width / 2) - (_text.getGlobalBounds().width / 2), _position.y + (_normalSprite.getGlobalBounds().height / 2) - (_text.getGlobalBounds().top + _text.getGlobalBounds().height / 2));
}

void	GUI::Button::event(const sf::Vector2i &mousePos)
{
	if (_normalSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
		_function();
}

void	GUI::Button::update(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		if (_normalSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
			window.draw(_hoverSprite);
		else
			window.draw(_normalSprite);
		window.draw(_text);
}

GUI::Checkbox::Checkbox(const sf::Vector2f& position, const sf::Texture& uncheckedTexture, const sf::Texture& checkedTexture, const std::function<void(bool)>& function)
	:	_function(function),
	_position(position),
	_uncheckedSprite(loadSprite(uncheckedTexture, position)),
	_checkedSprite(loadSprite(checkedTexture, position)),
	_isChecked(false)
{}

void	GUI::Checkbox::event(const sf::Vector2i& mousePos)
{
	if (_uncheckedSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		_function(_isChecked);
		_isChecked = !_isChecked;
	}
}

void	GUI::Checkbox::update(sf::RenderWindow& window)
{
	if (_isChecked)
		window.draw(_checkedSprite);
	else
		window.draw(_uncheckedSprite);
}

GUI::Text::Text(const sf::Vector2f& position, const std::string& text, const sf::Font& font, const sf::Color& color, const sf::Text::Style& style, size_t textSize)
	: _text(text, font, textSize)
{
	_text.setPosition(position.x, position.y);
	_text.setFillColor(color);
	_text.setStyle(style);
}

GUI::Text::Text(const sf::Vector2f& position, const std::string& text, const sf::Font& font, const sf::Color& color, size_t textSize)
	: _text(text, font, textSize)
{
	_text.setPosition(position.x, position.y);
	_text.setFillColor(color);
}

GUI::Text::Text(const sf::Vector2f& position, const std::string& text, const sf::Font& font, const sf::Text::Style& style, size_t textSize)
	: _text(text, font, textSize)
{
	_text.setPosition(position.x, position.y);
	_text.setStyle(style);
}

GUI::Text::Text(const sf::Vector2f& position, const std::string& text, const sf::Font& font, size_t textSize)
	: _text(text, font, textSize)
{
	_text.setPosition(position.x, position.y);
}

void	GUI::Text::update(sf::RenderWindow& window)
{
	window.draw(_text);
}

GUI::TextBox::TextBox(const sf::Vector2f& position, const sf::Texture& texture, const sf::Font& font, const sf::Text::Style& style, const sf::Color& color, size_t textSize)
	:	_text("", font, textSize),
	_backgroundSprite(loadSprite(texture, position))
{
	_text.setPosition(position);
	_text.setFillColor(color);
	_text.setStyle(style);
}

GUI::TextBox::TextBox(const sf::Vector2f& position, const sf::Texture& texture, const sf::Font& font, const sf::Text::Style& style, size_t textSize)
	:	_text("", font, textSize),
	_backgroundSprite(loadSprite(texture, position))
{
	_text.setPosition(position);
	_text.setFillColor(sf::Color::White);
	_text.setStyle(style);
}

GUI::TextBox::TextBox(const sf::Vector2f& position, const sf::Texture& texture, const sf::Font& font, const sf::Color& color, size_t textSize)
	:	_text("", font, textSize),
	_backgroundSprite(loadSprite(texture, position))
{
	_text.setPosition(position);
	_text.setFillColor(color);
	_text.setStyle(sf::Text::Style::Regular);
}

void	GUI::TextBox::event(const sf::Event& event)
{
	std::string str;

	if (event.key.code == sf::Keyboard::BackSpace)
		str.erase(0, str.size() - 1);
	else
		str  += static_cast<char>(event.text.unicode);

	_text.setString(str);
}

void	GUI::TextBox::update(sf::RenderWindow& window)
{
	window.draw(_backgroundSprite);
	window.draw(_text);
}
