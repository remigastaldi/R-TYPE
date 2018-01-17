#include "GUI.hpp"
#include "ResourcesManager.hpp"
#include "Resources.hpp"

sf::Sprite	&&GUI::loadSprite(const sf::Texture& texture, const sf::Vector2f& position)
{
	sf::Sprite sprite(texture);

	sprite.setPosition(position.x, position.y);

	return std::move(sprite);
}

GUI::Button::Button(const sf::Vector2f& position, const sf::Texture& normalTexture, const sf::Texture& hoverTexture,
	const std::string& text, const sf::Font& font, const std::function<void(void)>& function, const sf::Color colorText,
	int sizeText) :
	_position(position),
	_function(function),
	_isButtonPressed(false)
{
	_normalSprite = loadSprite(normalTexture, position);
	_hoverSprite = loadSprite(hoverTexture, position);
	_text.setFont(font);
	_text.setString(text);
	_text.setColor(colorText);
	_text.setCharacterSize(sizeText);
	_text.setPosition(_position.x + (_normalSprite.getGlobalBounds().width / 2) - (_text.getGlobalBounds().width / 2), _position.y + (_normalSprite.getGlobalBounds().height / 2) - (_text.getGlobalBounds().top + _text.getGlobalBounds().height / 2));
}

GUI::Button::Button(const sf::Vector2f& position, const sf::Texture& normalTexture, const sf::Texture& hoverTexture,
	const std::string& text, const sf::Font& font, const std::function<void(void)>& function, int sizeText) :
	_position(position),
	_function(function),
	_isButtonPressed(false)
{
	_normalSprite = loadSprite(normalTexture, position);
	_hoverSprite = loadSprite(hoverTexture, position);
	_text.setFont(font);
	_text.setString(text);
	_text.setCharacterSize(sizeText);
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

GUI::Checkbox::Checkbox(const sf::Vector2f& position, const sf::Texture& uncheckedTexture, const sf::Texture& checkedTexture, const std::function<void(bool)>& function) :
	_position(position),
	_function(function),
	_isChecked(false)
{
	_uncheckedSprite = loadSprite(uncheckedTexture, position);
	_checkedSprite = loadSprite(checkedTexture, position);
}

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

GUI::Text::Text(const sf::Vector2f& position, const std::string& text, const sf::Font& font, const sf::Color& color, const sf::Text::Style& style, int charSize)
{
	_text.setFont(font);
	_text.setString(text);
	_text.setPosition(position.x, position.y);
	_text.setCharacterSize(charSize);
	_text.setColor(color);
	_text.setStyle(style);
}

GUI::Text::Text(const sf::Vector2f& position, const std::string& text, const sf::Font& font, const sf::Color& color, int charSize)
{
	_text.setFont(font);
	_text.setString(text);
	_text.setPosition(position.x, position.y);
	_text.setCharacterSize(charSize);
	_text.setColor(color);
}

GUI::Text::Text(const sf::Vector2f& position, const std::string& text, const sf::Font& font, const sf::Text::Style& style, int charSize)
{
	_text.setFont(font);
	_text.setString(text);
	_text.setPosition(position.x, position.y);
	_text.setCharacterSize(charSize);
	_text.setStyle(style);
}

GUI::Text::Text(const sf::Vector2f& position, const std::string& text, const sf::Font& font, int charSize)
{
	_text.setFont(font);
	_text.setString(text);
	_text.setPosition(position.x, position.y);
	_text.setCharacterSize(charSize);
}

void	GUI::Text::update(sf::RenderWindow& window)
{
	window.draw(_text);
}

GUI::TextBox::TextBox(const sf::Vector2f& position, const sf::Texture& texture, const sf::Font& font, const sf::Text::Style& style, const sf::Color& color, int sizeChar)
{
	_backgroundSprite = loadSprite(texture, position);
	_text.setFont(font);
	_text.setPosition(position);
	_text.setColor(color);
	_text.setStyle(style);
	_text.setCharacterSize(sizeChar);
}

GUI::TextBox::TextBox(const sf::Vector2f& position, const sf::Texture& texture, const sf::Font& font, const sf::Text::Style& style, int sizeChar)
{
	_backgroundSprite = loadSprite(texture, position);
	_text.setFont(font);
	_text.setPosition(position);
	_text.setColor(sf::Color::White);
	_text.setStyle(style);
	_text.setCharacterSize(sizeChar);
}

GUI::TextBox::TextBox(const sf::Vector2f& position, const sf::Texture& texture, const sf::Font& font, const sf::Color& color, int sizeChar)
{
	_backgroundSprite = loadSprite(texture, position);
	_text.setFont(font);
	_text.setPosition(position);
	_text.setColor(color);
	_text.setStyle(sf::Text::Style::Regular);
	_text.setCharacterSize(sizeChar);
}

void	GUI::TextBox::event(const sf::Event& event)
{
	std::string str;
	
	if (event.key.code == sf::Keyboard::BackSpace)
		str.substr(0, str.size() - 1);
	else
		str  += static_cast<char>(event.text.unicode);
	
	_text.setString(str);
}

void	GUI::TextBox::update(sf::RenderWindow& window)
{
	window.draw(_backgroundSprite);
	window.draw(_text);
}