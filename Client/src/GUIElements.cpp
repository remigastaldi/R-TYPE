/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-17T14:12:41+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-20T20:06:29+01:00
 */


#include "GUIElements.hpp"
#include "ResourcesManager.hpp"
#include "Resources.hpp"

sf::Sprite  GUI::loadSprite(const sf::Texture& texture, const sf::Vector2f& position)
{
	sf::Sprite sprite(texture);

	sprite.setPosition(position.x, position.y);

	return (sprite);
}

GUI::Button::Button(EventManager::Manager &manager, const std::string &event, const sf::Vector2f& position, const sf::Sprite& normalSprite, const sf::Sprite& hoverSprite)
	:	_eventManager(manager),
	_event(event),
	_normalSprite(normalSprite),
	_hoverSprite(hoverSprite)
{
	_normalSprite.setPosition(position);
	_hoverSprite.setPosition(position);
}

void	GUI::Button::update(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	if (_normalSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			_eventManager.fire<int, std::string>(_event, "Play");
		window.draw(_hoverSprite);
	}
	else
		window.draw(_normalSprite);
}

GUI::Checkbox::Checkbox(EventManager::Manager &manager, const std::string &event, const sf::Vector2f& position, const sf::Sprite& uncheckedSprite, const sf::Sprite& checkedSprite)
	:	_eventManager(manager),
	_event(event),
	_uncheckedSprite(uncheckedSprite),
	_checkedSprite(checkedSprite),
	_isChecked(false)
{
	_uncheckedSprite.setPosition(position);
	_checkedSprite.setPosition(position);
}

void	GUI::Checkbox::event(const sf::Vector2i& mousePos)
{
	if (_uncheckedSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		_eventManager.fire<int, bool>(_event, _isChecked);
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

GUI::TextBox::TextBox(EventManager::Manager &manager, const std::string &event, const sf::Vector2f& position, const sf::Texture& texture, const sf::Font& font, const sf::Text::Style& style, const sf::Color& color, size_t textSize)
	:	_eventManager(manager),
	_event(event),
	_text("", font, textSize),
	_backgroundSprite(loadSprite(texture, position))
{
	_text.setPosition(position);
	_text.setFillColor(color);
	_text.setStyle(style);
}

GUI::TextBox::TextBox(EventManager::Manager &manager, const std::string &event, const sf::Vector2f& position, const sf::Texture& texture, const sf::Font& font, const sf::Text::Style& style, size_t textSize)
	:	_eventManager(manager),
	_event(event),
	_text("", font, textSize),
	_backgroundSprite(loadSprite(texture, position))
{
	_text.setPosition(position);
	_text.setFillColor(sf::Color::White);
	_text.setStyle(style);
}

GUI::TextBox::TextBox(EventManager::Manager &manager, const std::string &event, const sf::Vector2f& position, const sf::Texture& texture, const sf::Font& font, const sf::Color& color, size_t textSize)
	:	_eventManager(manager),
	_event(event),
	_text("", font, textSize),
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
		str.pop_back();
	else
		str  += static_cast<char>(event.text.unicode);

	_text.setString(str);
}

void	GUI::TextBox::update(sf::RenderWindow& window)
{
	window.draw(_backgroundSprite);
	window.draw(_text);
}

GUI::Image::Image(const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& textureRect, const sf::Color& color, const sf::Vector2f& absoluteScale, const sf::Vector2f& relativeScale, const sf::Vector2f& origin) :
	_sprite(loadSprite(texture, position))
{
	_sprite.setTextureRect(textureRect);
	_sprite.setColor(color);
	_sprite.setScale(absoluteScale);
	_sprite.scale(relativeScale);
	_sprite.setOrigin(origin);
}

GUI::Image::Image(const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& textureRect, const sf::Color& color, const sf::Vector2f& absoluteScale, const sf::Vector2f& origin) :
	_sprite(loadSprite(texture, position))
{
	_sprite.setTextureRect(textureRect);
	_sprite.setColor(color);
	_sprite.setScale(absoluteScale);
	_sprite.setOrigin(origin);
}

GUI::Image::Image(const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& textureRect, const sf::Color& color, const sf::Vector2f& origin) :
	_sprite(loadSprite(texture, position))
{
	_sprite.setTextureRect(textureRect);
	_sprite.setColor(color);
	_sprite.setOrigin(origin);
}

GUI::Image::Image(const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& textureRect, const sf::Vector2f& abosuleScale) :
	_sprite(loadSprite(texture, position))
{
	_sprite.setTextureRect(textureRect);
	_sprite.setScale(abosuleScale);
}

GUI::Image::Image(const sf::Vector2f& position, const sf::Texture& texture, const sf::Vector2f& abosuleScale) :
	_sprite(loadSprite(texture, position))
{
	_sprite.setScale(abosuleScale);
}

void	GUI::Image::update(sf::RenderWindow& window)
{
	window.draw(_sprite);
}
