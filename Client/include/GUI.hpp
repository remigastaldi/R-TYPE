#pragma once

#include <memory>
#include <functional>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
 
namespace GUI {

	inline sf::Sprite	&&loadSprite(sf::Texture&, sf::Vector2f);

	class Button {
	public:
		Button(sf::Vector2f, sf::Texture&, sf::Texture&, std::string, sf::Font&, std::function<void(void)>, sf::Color = sf::Color::White, int = 30);

		void	draw(sf::RenderWindow&);
		void	checkClick(sf::Vector2i);

		void	setText(sf::Text text) { _text = text; }
		void	setNormalSprite(std::shared_ptr<sf::Image> normalSprite) { _normalSprite = _normalSprite; }
		void	setClickedSprite(std::shared_ptr<sf::Image> clickedSprite) { _clickedSprite = _clickedSprite; }

		sf::Sprite		getNormalSprite() const { return _normalSprite; }
		sf::FloatRect	getNormalSpriteSize() const { return _normalSprite.getGlobalBounds(); }
		sf::Sprite		getClickedSprite() const { return _clickedSprite; }
		sf::FloatRect	getClickedSpriteSize() const { return _clickedSprite.getGlobalBounds(); }
		sf::Sprite		getHoverSprite() const { return _hoverSprite; }
		sf::FloatRect	getHoverSpriteSize() const { return _hoverSprite.getGlobalBounds(); }
		sf::Text		getText() const { return _text; }
		sf::Vector2f	getPosition() const { return _position; }

	private:
		void		loadText(std::string, sf::Font&, sf::Color, int);

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
		Checkbox(sf::Vector2f, sf::Texture&, sf::Texture&, std::function<void(void)>);
		void			draw(sf::RenderWindow&);

		sf::Vector2f	getPosition() const { return _position; }
		sf::Sprite		getUncheckedSprite() const { return _uncheckedSprite; }
		sf::Sprite		getCheckedSprite() const { return _checkedSprite; }
		bool			getIsChecked() const { return _isChecked; }

	private:
		std::function<void(void)>	_function;

		sf::Vector2f	_position;
		sf::Sprite		_uncheckedSprite;
		sf::Sprite		_checkedSprite;
		bool			_isChecked;
	};
}