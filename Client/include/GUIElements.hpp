/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-17T04:31:52+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-18T14:55:07+01:00
 */


#pragma once

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
		Button(const sf::Vector2f&, const sf::Texture&, const sf::Texture&, const std::string&, const sf::Font&, const std::function<void(void)>&, const sf::Color = sf::Color::White, size_t = 30);
		Button(const sf::Vector2f&, const sf::Texture&, const sf::Texture&, const std::string&, const sf::Font&, const std::function<void(void)>&, size_t = 30);

		void	update(sf::RenderWindow&) override;
		void	event(const sf::Vector2i&);

		void	setText(sf::Text text) { _text = text; }
		void	setNormalSprite(sf::Sprite normalSprite) { _normalSprite = normalSprite; }
		void	setClickedSprite(sf::Sprite clickedSprite) { _clickedSprite = clickedSprite; }

		const sf::Sprite	&	getNormalSprite() const { return _normalSprite; }
		const sf::FloatRect	getNormalSpriteSize() const { return _normalSprite.getGlobalBounds(); }
		const sf::Sprite&		getClickedSprite() const { return _clickedSprite; }
		const sf::FloatRect getClickedSpriteSize() const { return _clickedSprite.getGlobalBounds(); }
		const sf::Sprite	&	getHoverSprite() const { return _hoverSprite; }
		const sf::FloatRect	getHoverSpriteSize() const { return _hoverSprite.getGlobalBounds(); }
		const sf::Text&		getText() const { return _text; }
		const sf::Vector2f &	getPosition() const { return _position; }

		typedef Button ElementType;
	private:
		std::function<void(void)>	_function;
		sf::Vector2f				_position;

		sf::Sprite					_normalSprite;
		sf::Sprite					_clickedSprite;
		sf::Sprite					_hoverSprite;

		sf::Text					_text;
	};

	class Checkbox : public Element
	{
	public:
		Checkbox(const sf::Vector2f&, const sf::Texture&, const sf::Texture&, const std::function<void(bool)>&);
		void			update(sf::RenderWindow&) override;
		void			event(const sf::Vector2i&);

		const sf::Vector2f&		getPosition() const { return _position; }
		const sf::Sprite&		getUncheckedSprite() const { return _uncheckedSprite; }
		const sf::Sprite&		getCheckedSprite() const { return _checkedSprite; }
		bool					getIsChecked() const { return _isChecked; }

		typedef Checkbox ElementType;
	private:
		std::function<void(bool)>	_function;

		sf::Vector2f	_position;
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
	private:
		sf::Text _text;
	};

	class TextBox : public Element
	{
	public:
		TextBox(const sf::Vector2f&, const sf::Texture&, const sf::Font&, const sf::Text::Style&, const sf::Color&, size_t);
		TextBox(const sf::Vector2f&, const sf::Texture&, const sf::Font&, const sf::Color&, size_t);
		TextBox(const sf::Vector2f&, const sf::Texture&, const sf::Font&, const sf::Text::Style&, size_t);

		void	update(sf::RenderWindow&);
		void	event(const sf::Event&);
	private:
		sf::Text	_text;
		sf::Sprite	_backgroundSprite;
	};
}
