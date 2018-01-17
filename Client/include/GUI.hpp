#pragma once

#include <memory>
#include <functional>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
 
namespace GUI {
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
		sf::Sprite	loadSprite(sf::Texture&);
		void		loadText(std::string, sf::Font&, sf::Color, int);

		std::function<void(void)>	_function;
		sf::Vector2f				_position;

		sf::Texture					_normalTexture;
		sf::Texture					_clickedTexture;
		sf::Texture					_hoverTexture;

		sf::Sprite					_normalSprite;
		sf::Sprite					_clickedSprite;
		sf::Sprite					_hoverSprite;
		sf::Text					_text;
		bool						_isButtonPressed = false;
	};
}