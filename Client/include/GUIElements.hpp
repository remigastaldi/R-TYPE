/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-17T04:31:52+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-20T03:39:39+01:00
 */


#pragma once

#include "EventManager.hpp"

#include <memory>
#include <functional>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace GUI {

	class Element
	{
	public:
		virtual ~Element() {};
		virtual void update(sf::RenderWindow&) = 0;
	};

	inline sf::Sprite	loadSprite(const sf::Texture&, const sf::Vector2f&);

	class Button : public Element {
	public:
		Button(EventManager::Manager &manager, const std::string &event ,const sf::Vector2f&, const sf::Texture&, const sf::Texture&);

		void	update(sf::RenderWindow&) override;

		void	setPosition(const sf::Vector2f& pos) { _normalSprite.setPosition(pos); _hoverSprite.setPosition(pos); }
		void	setEvent(const std::string &event) { _event = event; }
		void	setNormalSprite(const sf::Sprite& normalSprite) { _normalSprite = normalSprite; }
		void	setHoverSprite(const sf::Sprite& hoverSprite) { _hoverSprite = hoverSprite; }

		const sf::Vector2f&		getPosition() const { return _normalSprite.getPosition(); }
		const sf::FloatRect		getTextureRect() const { return _normalSprite.getGlobalBounds(); }
		const sf::Sprite&		getNormalSprite() const { return _normalSprite; }
		const sf::FloatRect		getNormalSpriteSize() const { return _normalSprite.getGlobalBounds(); }
		const sf::Sprite&		getHoverSprite() const { return _hoverSprite; }
		const sf::FloatRect		getHoverSpriteSize() const { return _hoverSprite.getGlobalBounds(); }

		typedef Button ElementType;

	private:
		EventManager::Manager &_eventManager;
		std::string	_event;

		sf::Sprite					_normalSprite;
		sf::Sprite					_hoverSprite;
	};

	class Checkbox : public Element
	{
	public:
		Checkbox(EventManager::Manager &manager, const std::string &event ,const sf::Vector2f&, const sf::Texture&, const sf::Texture&);
		void			update(sf::RenderWindow&) override;
		void			event(const sf::Vector2i&);

		void	setPosition(const sf::Vector2f& pos) { _uncheckedSprite.setPosition(pos); _checkedSprite.setPosition(pos); }
		void	setUncheckedTexture(const sf::Texture& uncheckedTexture) { _uncheckedSprite.setTexture(uncheckedTexture); }
		void	setCheckedTexture(const sf::Texture& checkedTexture) { _checkedSprite.setTexture(checkedTexture); }
		void	setIsChecked(bool isChecked) { _isChecked = isChecked; }
		void	setEvent(const std::string &event) { _event = event; }

		const sf::FloatRect				getTextureRect() const { return _uncheckedSprite.getGlobalBounds(); }
		const sf::Sprite&				getUncheckedSprite() const { return _uncheckedSprite; }
		const sf::Sprite&				getCheckedSprite() const { return _checkedSprite; }
		bool							getIsChecked() const { return _isChecked; }
		typedef Checkbox ElementType;

	private:
		EventManager::Manager &_eventManager;
		std::string	_event;

		sf::Sprite		_uncheckedSprite;
		sf::Sprite		_checkedSprite;
		bool			_isChecked;
	};

	class Text : public Element
	{
	public:
		Text(const sf::Vector2f&, const std::string&, const sf::Font&, const sf::Color& = sf::Color::White, const sf::Text::Style& = sf::Text::Style::Regular, size_t = 30);
		Text(const sf::Vector2f&, const std::string&, const sf::Font&, const sf::Text::Style& = sf::Text::Style::Regular, size_t = 30);
		Text(const sf::Vector2f&, const std::string&, const sf::Font&, const sf::Color& = sf::Color::White, size_t = 30);
		Text(const sf::Vector2f&, const std::string&, const sf::Font&, size_t = 30);

		void update(sf::RenderWindow&) override;

		void	setPosition(const sf::Vector2f& pos) { _text.setPosition(pos); }
		void	setText(const std::string& text) { _text.setString(text); }
		void	setFont(const sf::Font& font) { _text.setFont(font); }
		void	setColor(const sf::Color& color) { _text.setFillColor(color); }
		void	setStyle(const sf::Text::Style& style) { _text.setStyle(style); }
		void	setCharSize(unsigned int charSize) { _text.setCharacterSize(charSize); }

		const sf::FloatRect	getTextureRect() const { return _text.getGlobalBounds(); }
		const sf::Vector2f	getPosition() const { return _text.getPosition(); }
		const std::string	getString() const { return _text.getString(); }
		const sf::Font		*getFont() const { return _text.getFont(); }
		const sf::Color		getColor() const { return _text.getFillColor(); }
		const sf::Uint32	getStyle() const { return _text.getStyle(); }
		const size_t		getCharSize() const { return _text.getCharacterSize(); }

	private:
		sf::Text _text;
	};

	class TextBox : public Element
	{
	public:
		TextBox(EventManager::Manager &manager, const std::string &event, const sf::Vector2f&, const sf::Texture&, const sf::Font&, const sf::Text::Style&, const sf::Color&, size_t = 30);
		TextBox(EventManager::Manager &manager, const std::string &event, const sf::Vector2f&, const sf::Texture&, const sf::Font&, const sf::Color& = sf::Color::White, size_t = 30);
		TextBox(EventManager::Manager &manager, const std::string &event, const sf::Vector2f&, const sf::Texture&, const sf::Font&, const sf::Text::Style& = sf::Text::Style::Regular, size_t = 30);

		void	update(sf::RenderWindow&);
		void	event(const sf::Event&);

		const sf::Vector2f	getPosition() const { return _backgroundSprite.getPosition(); }
		const sf::Texture	*getTexture() const { return _backgroundSprite.getTexture(); }
		const sf::Font		*getFont() const { return _text.getFont(); }
		const sf::Uint32	getStyle() const { return _text.getStyle(); }
		const sf::Color		getColor() const { return _text.getFillColor(); }
		const size_t		getSize() const { return _text.getCharacterSize(); }
		const sf::FloatRect	getTextureRect() const { return _text.getGlobalBounds(); }

		void	setText(const std::string& text) { _text.setString(text); }
		void	setFont(const sf::Font& font) { _text.setFont(font); }
		void	setColor(const sf::Color& color) { _text.setFillColor(color); }
		void	setStyle(const sf::Text::Style& style) { _text.setStyle(style); }
		void	setCharSize(unsigned int charSize) { _text.setCharacterSize(charSize); }

	private:
		sf::Text	_text;
		sf::Sprite	_backgroundSprite;
	};

	class Image : public Element
	{
	public:
		Image(const sf::Vector2f&, const sf::Texture&, const sf::Vector2f& = sf::Vector2f(0, 0));
		Image(const sf::Vector2f&, const sf::Texture&, const sf::IntRect& = sf::IntRect(0,0,0,0), const sf::Vector2f& = sf::Vector2f(0, 0));
		Image(const sf::Vector2f&, const sf::Texture&, const sf::IntRect&, const sf::Color& = sf::Color::White, const sf::Vector2f& = sf::Vector2f(0, 0));
		Image(const sf::Vector2f&, const sf::Texture&, const sf::IntRect&, const sf::Color&, const sf::Vector2f& = sf::Vector2f(0,0), const sf::Vector2f& = sf::Vector2f(0, 0));
		Image(const sf::Vector2f&, const sf::Texture&, const sf::IntRect&, const sf::Color&, const sf::Vector2f&, const sf::Vector2f& = sf::Vector2f(0,0), const sf::Vector2f& = sf::Vector2f(0, 0));

		void	update(sf::RenderWindow&);

		void	setPosition(const sf::Vector2f& position) { _sprite.setPosition(position); }
		void	setTexture(const sf::Texture& texture) { _sprite.setTexture(texture); }
		void	setTextureRect(const sf::IntRect& textureRect) { _sprite.setTextureRect(textureRect); }
		void	setColor(const sf::Color& color) { _sprite.setColor(color); }
		void	setAbsoluteScale(const sf::Vector2f& scale) { _sprite.setScale(scale); }
		void	setRelativeScale(const sf::Vector2f& scale) { _sprite.scale(scale); }

		const sf::Vector2f	getPosition() const { return _sprite.getPosition(); }
		const sf::Texture	*getTexture() const { return _sprite.getTexture(); }
		const sf::IntRect	getTextureRect() const { return _sprite.getTextureRect(); }
		const sf::Color		getColor() const { return _sprite.getColor(); }
		const sf::Vector2f	getAbsoluteScale() const { return _sprite.getScale(); }

	private:
		sf::Sprite	_sprite;
	};
}
