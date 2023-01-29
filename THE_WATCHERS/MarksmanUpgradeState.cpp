#include "stdafx.h"
#include "MarksmanUpgradeState.h"

void MarksmanUpgradeState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/yoster.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MarksmanUpgradeState::initKeybinds()
{
	std::ifstream file("Config/mainmenustate_keybinds.ini");

	if (file.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (file >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	file.close();
}

void MarksmanUpgradeState::initTextures()
{

}

void MarksmanUpgradeState::initTitle()
{
	this->title.setFont(this->font);
	this->title.setCharacterSize(this->window->getSize().x / 20.f);
	this->title.setString("The Way Of The Marksman");

	this->title.setPosition(
		this->window->getSize().x / 2.f - this->title.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 6.f - this->title.getGlobalBounds().height / 2.f
	);
}

void MarksmanUpgradeState::initButtons()
{
	float start_button_width = this->window->getSize().x / 6.4f, start_button_height = this->window->getSize().y / 12.8f;

	this->buttons["GAME_STATE_BUTTON"] = new gui::Button(0, this->window->getSize().x / 1.239f, this->window->getSize().y / 1.174f, start_button_width, start_button_height,
		&this->font, start_button_width / 6.25f, "START",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(0, this->window->getSize().x / 27.429f, this->window->getSize().y / 1.174f, start_button_width, start_button_height,
		&this->font, start_button_width / 6.25f, "BACK",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

}

MarksmanUpgradeState::MarksmanUpgradeState(sf::RenderWindow* window, std::map<std::string, sf::Keyboard::Key>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initFonts();
	this->initKeybinds();
	this->initTextures();
	this->initTitle();
	this->initButtons();




	this->background.setSize(sf::Vector2f(window->getSize()));
	this->background.setFillColor(sf::Color(31, 34, 50, 255));
}

MarksmanUpgradeState::~MarksmanUpgradeState()
{
	auto iterator = this->buttons.begin();
	for (iterator = this->buttons.begin(); iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
	}
}

void MarksmanUpgradeState::updateInput(const float& dt)
{

}

void MarksmanUpgradeState::updateButtons()
{
	/*Updates all buttons in this state w/ functionalities*/
	for (auto& iterator : this->buttons)
	{
		iterator.second->update(this->mousePosView);
	}

	//Begins Game State
	if (this->buttons["GAME_STATE_BUTTON"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	//Back to Character Select State
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
		this->states->pop();
	}
}

void MarksmanUpgradeState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();


}

void MarksmanUpgradeState::renderButtons(sf::RenderTarget* target)
{
	for (auto& iterator : this->buttons)
	{
		iterator.second->render(*target);
	}
}

void MarksmanUpgradeState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->title);
	this->renderButtons(target);
}
