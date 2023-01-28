#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <cstdlib>
#include <sstream>

#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

enum buton_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE, BTN_CLICKED};

class Button
{
private:
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	bool mouseDown;
	bool toggleable;
	bool toggled;
	bool isVoid;
	
	

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(bool toggleable, float x, float y, float width, float height,
		sf::Font* font, unsigned int fonstSize, std::string text, 
		sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	//Access
	const bool isPressed() const;
	const bool isToggled() const;
	void toggleOn();
	void toggleOff();
	void activate();
	void deactivate();


	//Functions
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

#endif