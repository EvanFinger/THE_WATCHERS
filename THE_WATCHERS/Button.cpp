#include "Button.h"

Button::Button(bool toggleable, float x, float y, float width, float height,
	sf::Font* font, unsigned int fontSize, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{	
	this->buttonState = BTN_IDLE;
	this->mouseDown = false;
	this->toggleable = toggleable;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setOutlineThickness(5);
	this->shape.setOutlineColor(sf::Color::Transparent);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(fontSize);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);

}

Button::~Button()
{

}



//Access
const bool Button::isPressed() const
{
	return buttonState == BTN_CLICKED;
}

const bool Button::isToggled() const
{
	return toggled;
}

void Button::toggleOn()
{
	this->toggled = true;
}

void Button::toggleOff()
{
	this->toggled = false;
}

//Funtions

void Button::update(const sf::Vector2f mousePos)
{
	/*Update the bools for hover/pressed*/

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
				this->buttonState = BTN_ACTIVE;
				this->mouseDown = true;
		}

		if (this->mouseDown && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_CLICKED;
			this->mouseDown = false;
			
			if (this->toggleable && !this->toggled)
			{
				this->toggled = true;
			}
			else if (this->toggleable && this->toggled)
			{
				this->toggled = false;
			}
		}
	}

	if(toggled)
		this->shape.setOutlineColor(sf::Color::White);
	else
		this->shape.setOutlineColor(sf::Color::Transparent);

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->mouseDown = false;
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}