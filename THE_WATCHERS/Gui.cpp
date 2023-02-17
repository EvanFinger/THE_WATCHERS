#include "stdafx.h"
#include "Gui.h"
/*
--------------------------------------------------

BUTTON CLASS (credit in .h)

--------------------------------------------------
*/
#ifndef BUTTON

gui::Button::Button(
	bool toggleable, 
	float x, float y, float width, float height,
	sf::Font* font, unsigned int fontSize, std::string text,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id)
{	
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->mouseDown = false;
	this->toggleable = toggleable;
	this->isVoid = false;
	this->toggled = false;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setOutlineColor(sf::Color::Transparent);
	this->shape.setFillColor(idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(textIdleColor);
	this->text.setCharacterSize(fontSize);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height 
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;


	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;
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

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

//Modifiers

void gui::Button::setText(const std::string text) 
{
	this->text.setString(text);
}

void gui::Button::setPosition(float x, float y)
{
	this->shape.setPosition(sf::Vector2f(x, y));

	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height
	);
}

void gui::Button::setSize(float width, float height, unsigned int font_Size)
{
	this->shape.setSize(sf::Vector2f(width, height));

	this->text.setCharacterSize(font_Size);
}

void gui::Button::setSize(float width, float height)
{
	this->shape.setSize(sf::Vector2f(width, height));
}




//Funtions
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
	this->isVoid = false;
}

void gui::Button::deactivate()
{
	this->isVoid = true;
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

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
		this->shape.setOutlineColor(this->outlineIdleColor);
		this->mouseDown = false;
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
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
#endif 
/*
--------------------------------------------------

DROPDOWN MENU CLASS (credit in .h)

--------------------------------------------------
*/
#ifndef DROPDOWN_LIST

gui::DropdownList::DropdownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned numberOfElements, unsigned default_index)
	: font(font), showList(false)
{
	//unsigned numberOfElements = sizeof(list) / sizeof(std::string);
	
	this->activeElement = new gui::Button(
		0,
		x, y, width, height,
		&this->font, 12, list[default_index],
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 200)
	);

	for (size_t i = 0; i < numberOfElements; i++)
	{
		this->list.push_back(
				new gui::Button(
					0, 
					x, y + (i+1) * height, width, height,
					&this->font, 12, list[i],
					sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
					sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
					sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
					i
				)
			);
	}

	
	
}

gui::DropdownList::~DropdownList()
{
	delete this->activeElement;
	if (this->showList)
	{
		for (size_t i = 0; i < this->list.size(); i++)
		{
			delete this->list[i];
		}
	}
	
}

const unsigned short gui::DropdownList::getActiveId() const
{
	return this->activeElement->getId();
}

void gui::DropdownList::update(const sf::Vector2f& mousePos)
{	
	this->activeElement->update(mousePos);

	if (this->activeElement->isPressed())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& iterator : this->list)
		{
			iterator->update(mousePos);

			if (iterator->isPressed())
			{
				this->showList = false;
				this->activeElement->setText(iterator->getText());
				this->activeElement->setId(iterator->getId());
			}
		}
	}
}

void gui::DropdownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showList)
	{
		for (auto& iterator : this->list)
		{
			iterator->render(target);
		}
	}
	
}

#endif

/*
--------------------------------------------------

ARROW SELECTION CLASS (credit in .h)

--------------------------------------------------
*/
#ifndef ARROW_SELECTOR

gui::ArrowSelection::ArrowSelection(
	float x, float y, float width, float height,
	sf::Font& font, std::string list[],
	unsigned short num_of_elements, unsigned short default_index
)
	:font(font)
{
	this->activeIndex = default_index;
	for (size_t i = 0; i < num_of_elements; i++)
	{
		this->list.push_back(
			list[i]
		);
	}

	this->indexLeft = new gui::Button(
		0,
		x, y, width * 0.2f, height,
		&this->font, 12, "<-",
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 200)
	);

	this->shape.setPosition(
		x + width * 0.2f,
		y
	);
	this->shape.setSize(sf::Vector2f(width * 0.6f, height));
	this->shape.setFillColor(sf::Color(70, 70, 70, 200));
	this->shape.setOutlineThickness(1);
	this->shape.setOutlineColor(sf::Color(255, 255, 255, 200));
	
	this->activeItem.setFont(this->font);
	this->activeItem.setFillColor(sf::Color(255, 255, 255, 150));
	this->activeItem.setCharacterSize(24);
	this->activeItem.setString(this->list[default_index]);
	this->activeItem.setPosition(
		this ->shape.getPosition().x + this->shape.getGlobalBounds().width * 0.5 - this->activeItem.getGlobalBounds().width * 0.5,
		this->shape.getPosition().y + this->shape.getGlobalBounds().height * 0.5 - this->activeItem.getGlobalBounds().height
	);

	this->indexRight = new gui::Button(
		0,
		x + width * 0.8f, y, width * 0.2f, height,
		&this->font, 12, "->",
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 200)
	);
}

gui::ArrowSelection::~ArrowSelection()
{
	delete this->indexLeft;
	delete this->indexRight;
}

const unsigned short gui::ArrowSelection::getActiveIndex() const
{
	return this->activeIndex;
}

void gui::ArrowSelection::update(const sf::Vector2f& mousePos)
{
	this->indexLeft->update(mousePos);
	if (this->indexLeft->isPressed())
	{
		if (this->activeIndex > 0)
			this->activeIndex -= 1;
		else
			this->activeIndex = this->list.size() - 1;
	}

	this->indexRight->update(mousePos);
	if (this->indexRight->isPressed())
	{
		if (this->activeIndex < this->list.size() - 1)
			this->activeIndex += 1;
		else
			this->activeIndex = 0;
	}

	this->activeItem.setString(this->list[activeIndex]);
}

void gui::ArrowSelection::render(sf::RenderTarget& target)
{
	this->indexLeft->render(target);
	target.draw(this->shape);
	target.draw(this->activeItem);
	this->indexRight->render(target);
}

#endif

/*
--------------------------------------------------

ARROW SELECTION CLASS (credit in .h)

--------------------------------------------------
*/
#ifndef TOGGLE_SWITCH

gui::ToggleSwitch::ToggleSwitch(float x, float y, float width, float height, sf::Color switch_background, sf::Color switch_active, sf::Color switch_lever, bool init_state)
{
	this->switchBackground = switch_background;
	this->switchActive = switch_active;
	this->switchLever = switch_lever;

	this->switchOff.setPosition(x, y);
	this->switchOff.setSize(sf::Vector2f(width * 0.5f, height * 0.5f));
	this->switchOff.setFillColor(this->switchLever);

	this->switchOn.setPosition(x + width * 0.5, y);
	this->switchOn.setSize(sf::Vector2f(width * 0.5f, height * 0.5f));
	this->switchOn.setFillColor(this->switchBackground);

	this->hoverSwitchBackground = sf::Color(
		this->switchBackground.r, this->switchBackground.g, this->switchBackground.b, this->switchBackground.a - 50
	);
	this->hoverSwitchActive = sf::Color(
		this->switchActive.r, this->switchActive.g, this->switchActive.b, this->switchActive.a - 50
	);
	this->hoverSwitchLever = sf::Color(
		this->switchLever.r, this->switchLever.g, this->switchLever.b, this->switchLever.a - 50
	);

	this->clickedSwitchBackground = sf::Color(
		this->switchBackground.r, this->switchBackground.g, this->switchBackground.b, this->switchBackground.a - 100
	);
	this->clickedSwitchActive = sf::Color(
		this->switchActive.r, this->switchActive.g, this->switchActive.b, this->switchActive.a - 100
	);
	this->clickedSwitchLever = sf::Color(
		this->switchLever.r, this->switchLever.g, this->switchLever.b, this->switchLever.a - 100
	);

	this->state = BTN_IDLE;
	this->mouseDown = false;
	this->toggled = init_state;



}

gui::ToggleSwitch::~ToggleSwitch()
{
}

const bool gui::ToggleSwitch::getToggled() const
{
	return this->toggled;
}

void gui::ToggleSwitch::update(const sf::Vector2f& mousePos)
{
	this->state = BTN_IDLE;

	if (this->switchOff.getGlobalBounds().contains(mousePos) || this->switchOn.getGlobalBounds().contains(mousePos))
	{
		this->state = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->state = BTN_ACTIVE;
			this->mouseDown = true;
		}

		if (this->mouseDown && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->state = BTN_CLICKED;
			this->mouseDown = false;

			if (!this->toggled)
			{
				this->toggled = true;
			}
			else if (this->toggled)
			{
				this->toggled = false;
			}
		}

		
	}
	switch (state)
		{
		case BTN_IDLE:
			if (toggled)
			{ 
				this->switchOff.setFillColor(this->switchActive);
				this->switchOn.setFillColor(this->switchLever);
			}
			else
			{
				this->switchOff.setFillColor(this->switchLever);
				this->switchOn.setFillColor(this->switchBackground);
			}
			break;
		case BTN_HOVER:
			if (toggled)
			{
				this->switchOff.setFillColor(this->hoverSwitchActive);
				this->switchOn.setFillColor(this->hoverSwitchLever);
			}
			else
			{
				this->switchOff.setFillColor(this->hoverSwitchLever);
				this->switchOn.setFillColor(this->hoverSwitchBackground);
			}
			break;
		case BTN_ACTIVE:
			if (toggled)
			{
				this->switchOff.setFillColor(this->clickedSwitchActive);
				this->switchOn.setFillColor(this->clickedSwitchLever);
			}
			else
			{
				this->switchOff.setFillColor(this->clickedSwitchLever);
				this->switchOn.setFillColor(this->clickedSwitchBackground);
			}
			break;
		}
}

void gui::ToggleSwitch::render(sf::RenderTarget& target)
{
	target.draw(this->switchOff);
	target.draw(this -> switchOn);
}

#endif 