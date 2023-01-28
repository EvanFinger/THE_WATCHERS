#include "CharacterSelectState.h"

void CharacterSelectState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/yoster.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void CharacterSelectState::initKeybinds()
{
	std::ifstream file("Config/characterselectstate_keybinds.ini");

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

void CharacterSelectState::initTextures()
{

}

void CharacterSelectState::initTitle()
{
	this->title.setFont(this->font);
	this->title.setCharacterSize(this->window->getSize().x / 20.f);
	this->title.setString("Choose Your Way");

	this->title.setPosition(
		this->window->getSize().x / 19.2f,
		this->window->getSize().y / 21.6f
	);
}

void CharacterSelectState::initPlayerDescription()
{
	if (!this->playerImage.loadFromFile("Images/Players/player_idle_0.png"))
		throw("Swordmaster Image could not be found!");

	this->playerTexture.loadFromImage(playerImage);
	this->playerSprite.setTexture(playerTexture);
	this->playerSprite.setScale(15, 15);
	this->playerSprite.setPosition(
		this->title.getPosition().x + this->title.getGlobalBounds().width + this->title.getGlobalBounds().height,
		this->title.getPosition().y);

	this->playerSummary.setFont(this->font);
	this->playerSummary.setCharacterSize(20);
	this->playerSummary.setFillColor(sf::Color::White);
	this->playerSummary.setString("D");

	this->playerSummary.setPosition(
		this->window->getSize().x / 12.8,
		this->title.getGlobalBounds().height * 7.f
	);
}

void CharacterSelectState::initButtons()
{
	float start_button_width = this->window->getSize().x / 6.4f, start_button_height = this->window->getSize().y / 12.8f;

	float character_button_pos_x = this->window->getSize().x / 12.8;
	float character_button_length = this->title.getGlobalBounds().width / 1.143f;
	float character_button_height = this->window->getSize().y / 10.8;

	this->buttons["UPGRADES_STATE_BUTTON"] = new Button(0, character_button_pos_x + (character_button_length - start_button_width), this->window->getSize().y / 1.174f, 
		start_button_width, start_button_height,
		&this->font, start_button_width / 6.25f, "START",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["CHARACTER_BUTTON_A"] = new Button(1, character_button_pos_x, this->title.getGlobalBounds().height * 2.5f,
		character_button_length, character_button_height,
		&this->font, character_button_length / 6.25f, "SWORD",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["CHARACTER_BUTTON_B"] = new Button(1, character_button_pos_x, this->title.getGlobalBounds().height * 4.f,
		character_button_length, character_button_height,
		&this->font, character_button_length / 6.25f, "MARKSMAN",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["CHARACTER_BUTTON_C"] = new Button(1, character_button_pos_x, this->title.getGlobalBounds().height * 5.5f,
		character_button_length, character_button_height,
		&this->font, character_button_length / 6.25f, "TRICKSTER",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new Button(0, character_button_pos_x, this->window->getSize().y / 1.174f, 
		start_button_width, start_button_height,
		&this->font, start_button_width / 6.25f, "BACK",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

CharacterSelectState::CharacterSelectState(sf::RenderWindow* window, std::map<std::string, sf::Keyboard::Key>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initFonts();
	this->initKeybinds();
	this->initTextures();
	this->initTitle();
	this->initPlayerDescription();
	this->initButtons();




	this->background.setSize(sf::Vector2f(window->getSize()));
	this->background.setFillColor(sf::Color(31, 34, 50, 255));
}//31, 34, 50, 255

CharacterSelectState::~CharacterSelectState()
{
	auto iterator = this->buttons.begin();
	for (iterator = this->buttons.begin(); iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
	}
}


void CharacterSelectState::updateInput(const float& dt)
{

}

void CharacterSelectState::updateButtons()
{
	/*Updates all buttons in this state w/ functionalities*/
	for (auto& iterator : this->buttons)
	{
		iterator.second->update(this->mousePosView);
	}

	if (this->buttons.at("CHARACTER_BUTTON_A")->isPressed())
	{
		this->buttons.at("CHARACTER_BUTTON_B")->toggleOff();
		this->buttons.at("CHARACTER_BUTTON_C")->toggleOff();
		this->title.setString("The Sword Master");
	}
	else if (this->buttons.at("CHARACTER_BUTTON_B")->isPressed())
	{
		this->buttons.at("CHARACTER_BUTTON_A")->toggleOff();
		this->buttons.at("CHARACTER_BUTTON_C")->toggleOff();
		this->title.setString("The Marksman");
	}
	else if (this->buttons.at("CHARACTER_BUTTON_C")->isPressed())
	{
		this->buttons.at("CHARACTER_BUTTON_A")->toggleOff();
		this->buttons.at("CHARACTER_BUTTON_B")->toggleOff();
		this->title.setString("The Trickster");
	}

	//To Upgrades State
	if (this->buttons.at("UPGRADES_STATE_BUTTON")->isPressed())
	{
		if(this->buttons.at("CHARACTER_BUTTON_A")->isToggled())
			this->states->push(new SwordUpgradeState(this->window, this->supportedKeys, this->states));
		else if (this->buttons.at("CHARACTER_BUTTON_B")->isToggled())
			this->states->push(new MarksmanUpgradeState(this->window, this->supportedKeys, this->states));
		else if (this->buttons.at("CHARACTER_BUTTON_C")->isToggled())
			this->states->push(new TricksterUpgradeState(this->window, this->supportedKeys, this->states));
	}

	//Back to Main Menu State
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
		this->states->pop();
	}
}

void CharacterSelectState::updatePlayerDescription()
{
	if (this->buttons.at("CHARACTER_BUTTON_A")->isToggled())
	{
		
	}
	else if (this->buttons.at("CHARACTER_BUTTON_B")->isToggled())
	{

	}
	else if (this->buttons.at("CHARACTER_BUTTON_C")->isToggled())
	{

	}
}

void CharacterSelectState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();

	this->updatePlayerDescription();


}

void CharacterSelectState::renderButtons(sf::RenderTarget* target)
{
	for (auto& iterator : this->buttons)
	{
		iterator.second->render(*target);
	}
}

void CharacterSelectState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->title);
	target->draw(this->playerSprite);
	target->draw(this->playerSummary);
	this->renderButtons(target);
	
}
