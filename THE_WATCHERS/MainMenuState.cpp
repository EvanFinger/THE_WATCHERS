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

void MainMenuState::initButtons()
{
	float button_width = this->window->getSize().x / 6.4f, button_height = this->window->getSize().y / 12.8f;
	float button_xPos = this->window->getSize().x / 2.f - button_width / 2.f;
	float button_yOffset = this->title.getPosition().y + this->title.getGlobalBounds().height * 2.5f;

	this->buttons["CHARACTER_SELECT_STATE_BUTTON"] = new Button(0,button_xPos, button_yOffset, button_width, button_height,
		&this->font, button_width / 6.25f, "START",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ACHIEVEMENT_STATE_BUTTON"] = new Button(0,button_xPos, button_yOffset + button_height * 1.25f, button_width, button_height,
		&this->font, button_width / 6.25f, "ACHIEVEMENTS",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS_STATE_BUTTON"] = new Button(0,button_xPos, button_yOffset + button_height * 2.5f, button_width, button_height,
		&this->font, button_width / 6.25f, "SETTINGS",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new Button(0,button_xPos, button_yOffset + button_height * 3.75f, button_width, button_height,
		&this->font, button_width / 6.25f, "QUIT",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}



MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, sf::Keyboard::Key>* supportedKeys, std::stack<State*>* states)
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

MainMenuState::~MainMenuState()
{
	auto iterator = this->buttons.begin();
	for (iterator = this->buttons.begin(); iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
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
	if (this->buttons["CHARACTER_SELECT_STATE_BUTTON"]->isPressed())
	{
		this->states->push(new CharacterSelectState(this->window, this->supportedKeys, this->states));
	}

	//Quit Game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
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
