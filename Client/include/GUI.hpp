#pragma once

#include <memory>
#include <functional>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
 
namespace GUI {

	inline sf::Sprite	&&loadSprite(const sf::Texture&, const sf::Vector2f&);

	class Button {
	public:
		Button(const sf::Vector2f&, const sf::Texture&, const sf::Texture&, const std::string&, const sf::Font&, const std::function<void(void)>&, const sf::Color = sf::Color::White, int = 30);
		Button(const sf::Vector2f&, const sf::Texture&, const sf::Texture&, const std::string&, const sf::Font&, const std::function<void(void)>&, int = 30);

		void	draw(sf::RenderWindow&);

		void	setText(sf::Text text) { _text = text; }
		void	setNormalSprite(std::shared_ptr<sf::Image> normalSprite) { _normalSprite = _normalSprite; }
		void	setClickedSprite(std::shared_ptr<sf::Image> clickedSprite) { _clickedSprite = _clickedSprite; }

		const sf::Sprite	&	getNormalSprite() const { return _normalSprite; }
		const sf::FloatRect&	getNormalSpriteSize() const { return _normalSprite.getGlobalBounds(); }
		const sf::Sprite&		getClickedSprite() const { return _clickedSprite; }
		const sf::FloatRect	&getClickedSpriteSize() const { return _clickedSprite.getGlobalBounds(); }
		const sf::Sprite	&	getHoverSprite() const { return _hoverSprite; }
		const sf::FloatRect	&getHoverSpriteSize() const { return _hoverSprite.getGlobalBounds(); }
		const sf::Text&		getText() const { return _text; }
		const sf::Vector2f &	getPosition() const { return _position; }

	private:
		void		loadText(const std::string&, const sf::Font&, const sf::Color, int);

		std::function<void(void)>	_function;
		sf::Vector2f				_position;

		sf::Sprite					_normalSprite;
		sf::Sprite					_clickedSprite;
		sf::Sprite					_hoverSprite;

		sf::Text					_text;
		bool						_isButtonPressed;
	};

	class Checkbox
	{
	public:
		Checkbox(const sf::Vector2f&, const sf::Texture&, const sf::Texture&, const std::function<void(bool)>&);
		void			draw(sf::RenderWindow&);

		const sf::Vector2f&	getPosition() const { return _position; }
		const sf::Sprite&		getUncheckedSprite() const { return _uncheckedSprite; }
		const sf::Sprite&		getCheckedSprite() const { return _checkedSprite; }
		bool			getIsChecked() const { return _isChecked; }

	private:
		std::function<void(bool)>	_function;

		sf::Vector2f	_position;
		sf::Sprite		_uncheckedSprite;
		sf::Sprite		_checkedSprite;
		bool			_isChecked;
	};

	class Text
	{
	public:
		Text(const sf::Vector2f&, const std::string&, const sf::Font&, const sf::Color& = sf::Color::White, const sf::Text::Style& = sf::Text::Style::Regular, int = 30);
		Text(const sf::Vector2f&, const std::string&, const sf::Font&, const sf::Text::Style& = sf::Text::Style::Regular, int = 30);
		Text(const sf::Vector2f&, const std::string&, const sf::Font&, const sf::Color& = sf::Color::White, int = 30);
		Text(const sf::Vector2f&, const std::string&, const sf::Font&, int = 30);

		void draw(sf::RenderWindow&);
	private:
		sf::Text _text;
	};
}