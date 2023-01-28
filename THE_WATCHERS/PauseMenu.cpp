#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	:font(font)
{
	//init bg
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x), 
			static_cast<float>(window.getSize().y)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//init container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x / 3.f),
			static_cast<float>(window.getSize().y / 2.f)
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(window.getSize().x / 2.f - this->container.getSize().x / 2.f),
		static_cast<float>(window.getSize().y / 2.f - this->container.getSize().y / 2.f)
	);

	//init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(window.getSize().x / 26.6f);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2,
		this->container.getPosition().y + 20.f
	);

}

PauseMenu::~PauseMenu()
{
	auto iterator = this->buttons.begin();
	for (iterator = this->buttons.begin(); iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

const bool& PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton()
{

	float button_width = this->container.getGlobalBounds().width * 0.8f;
	float button_height = this->container.getGlobalBounds().width * 0.2f;
	float button_X_offset = this->container.getPosition().x + this->container.getSize().x / 2.f - button_width / 2.f;

	this->buttons["RESUME"] = new gui::Button(
		0, 
		button_X_offset, 
		this->menuText.getPosition().y + this->menuText.getGlobalBounds().height + button_height * 0 + 20.f * 1, 
		button_width,
		button_height,
		&this->font, button_width / 6.25f, "Resume",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["QUIT"] = new gui::Button(
		0,
		button_X_offset,
		this->menuText.getPosition().y + this->menuText.getGlobalBounds().height + button_height * 1 + 20.f * 2,
		button_width,
		button_height,
		&this->font, button_width / 6.25f, "Quit",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& iterator : this->buttons)
	{
		iterator.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto &iterator : buttons)
	{
		iterator.second->render(target);
	}

	target.draw(this->menuText);
}


//Functions