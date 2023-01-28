#include "Gui.h"

gui::Button::Button(bool toggleable, float x, float y, float width, float height,
	sf::Font* font, unsigned int fontSize, std::string text,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{	
	this->buttonState = BTN_IDLE;
	this->mouseDown = false;
	this->toggleable = toggleable;
	this->isVoid = false;
	this->toggled = false;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setOutlineThickness(5);
	this->shape.setOutlineColor(sf::Color::Transparent);
	this->shape.setFillColor(idleColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(textIdleColor);
	this->text.setCharacterSize(fontSize);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height 
	);

	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;


	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	

}

gui::Button::~Button()
{

}



//Access
const bool gui::Button::isPressed() const
{
	return buttonState == BTN_CLICKED;
}

const bool gui::Button::isToggled() const
{
	return toggled;
}

void gui::Button::toggleOn()
{
	this->toggled = true;
}

void gui::Button::toggleOff()
{
	this->toggled = false;
}

void gui::Button::activate()
{
	this->isVoid = true;
}

void gui::Button::deactivate()
{
	this->isVoid = true;
}


//Funtions

void gui::Button::update(const sf::Vector2f& mousePos)
{
	/*Update the bools for hover/pressed*/

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos) && !isVoid)
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
		this->text.setFillColor(this->textIdleColor);
		this->mouseDown = false;
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);

		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}


}

void gui::Button::render(sf::RenderTarget& target)
{
	if (!isVoid)
	{
		target.draw(this->shape);
		target.draw(this->text);
	}
}
