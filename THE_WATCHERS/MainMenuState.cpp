#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/yoster.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
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

void MainMenuState::initTextures()
{

}

void MainMenuState::initTitle()
{
	this->title.setFont(this->font);
	this->title.setCharacterSize(this->window->getSize().x / 20.f);
	this->title.setString("THE WATCHERS");

	this->title.setPosition(
		this->window->getSize().x / 2.f - this->title.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 6.f - this->title.getGlobalBounds().height / 2.f
		);
}

void MainMenuState::initGui()
{
	float button_width = this->window->getSize().x / 6.4f, button_height = this->window->getSize().y / 12.8f;
	float button_xPos = this->window->getSize().x / 2.f - button_width / 2.f;
	float button_yOffset = this->title.getPosition().y + this->title.getGlobalBounds().height * 2.5f;

	this->buttons["1CHARACTER_SELECT_STATE_BUTTON"] = new gui::Button(0,button_xPos, button_yOffset, button_width, button_height,
		&this->font, button_width / 6.25f, "START",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["2ACHIEVEMENT_STATE_BUTTON"] = new gui::Button(0,button_xPos, button_yOffset + button_height * 1.25f, button_width, button_height,
		&this->font, button_width / 6.25f, "ACHIEVEMENTS",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["3SETTINGS_STATE_BUTTON"] = new gui::Button(0,button_xPos, button_yOffset + button_height * 2.5f, button_width, button_height,
		&this->font, button_width / 6.25f, "SETTINGS",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["4EXIT_STATE"] = new gui::Button(0,button_xPos, button_yOffset + button_height * 3.75f, button_width, button_height,
		&this->font, button_width / 6.25f, "QUIT",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}



MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initFonts();
	this->initKeybinds();
	this->initTextures();
	this->initTitle();
	this->initGui();
	

	

	this->background.setSize(sf::Vector2f(window->getSize()));
	this->background.setFillColor(sf::Color(31, 34, 50, 255));
}

MainMenuState::~MainMenuState()
{
	auto iterator = this->buttons.begin();
	for (iterator = this->buttons.begin(); iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
	}
}

void MainMenuState::refresh()
{
	

	this->background.setSize(sf::Vector2f(window->getSize()));
	this->initTitle();

	int i = 0;
	for (auto& iterator : this->buttons)
	{
		iterator.second->setSize(
			this->window->getSize().x / 6.4f, 
			(this->window->getSize().y / 12.8f),
			(this->window->getSize().x / 6.4f) / 6.25f
		);
		iterator.second->setPosition(
			this->window->getSize().x / 2.f - (this->window->getSize().x / 6.4f) / 2.f, 
			(this->title.getPosition().y + this->title.getGlobalBounds().height * 2.5f) + (this->window->getSize().y / 12.8f) * 1.25 * i
		);
		i ++;
	}
}

void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	/*Updates all buttons in this state w/ functionalities*/
	for (auto &iterator : this->buttons)
	{
		iterator.second->update(this->mousePosView);
	}
	
	//New Game
	if (this->buttons["1CHARACTER_SELECT_STATE_BUTTON"]->isPressed())
	{
		this->states->push(new CharacterSelectState(this->stateData));
	}

	if (this->buttons["3SETTINGS_STATE_BUTTON"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	//Quit Game
	if (this->buttons["4EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->refresh();
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
	
	
	
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& iterator : this->buttons)
	{
		iterator.second->render(*target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->title);
	this->renderButtons(target);
}
