#include "stdafx.h"
#include "SettingsState.h"

//Inits

void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/yoster.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initKeybinds()
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

void SettingsState::initTextures()
{

}

void SettingsState::initTitle()
{
	this->title.setFont(this->font);
	this->title.setCharacterSize(this->window->getSize().x / 20.f);
	this->title.setString("SETTINGS");

	this->title.setPosition(
		this->window->getSize().x / 2.f - this->title.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 6.f - this->title.getGlobalBounds().height / 2.f
	);
}

void SettingsState::initGui(unsigned short default_index, bool fullscreen)
{
	float button_width = this->window->getSize().x / 6.4f, button_height = this->window->getSize().y / 12.8f;
	float button_xPos = this->window->getSize().x / 2.f - button_width / 2.f;
	float button_yOffset = this->title.getPosition().y + this->title.getGlobalBounds().height * 2.5f;

	this->buttons["BACK"] = new gui::Button(
		0, 
		this->window->getSize().x / 27.429f, this->window->getSize().y / 1.174f, button_width, button_height,
		&this->font, button_width / 6.25f, "Back",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["APPLY"] = new gui::Button(
		0, 
		this->window->getSize().x / 1.239f, this->window->getSize().y / 1.174f, button_width, button_height,
		&this->font, button_width / 6.25f, "APPLY",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["SAVE"] = new gui::Button(
		0,
		this->window->getSize().x / 1.239f - button_width, this->window->getSize().y / 1.174f, button_width, button_height,
		&this->font, button_width / 6.25f, "SAVE",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	//Resolution
	std::vector<std::string> modes_str;
	for (auto& iterator : this->modes)
	{
		modes_str.push_back(std::to_string(iterator.width) + "x" + std::to_string(iterator.height));
	}
	std::string list[]= { "123", "456", "789"};

	this->arrowSelectors["RESOLUTION"] = new gui::ArrowSelection(
		this->stateData->window->getSize().x / 6.4, this->stateData->window->getSize().y / 10.8, 250, 40,
		this->font, modes_str.data(), modes_str.size(), default_index
	);

	//FullScreen
	this->toggleSwitches["FULLSCREEN"] = new gui::ToggleSwitch(
		this->stateData->window->getSize().x / 4.8f, this->stateData->window->getSize().y / 4.5, 
		this->stateData->window->getSize().x / 12.8, this->stateData->window->getSize().y / 21.6,
		sf::Color(20, 30, 60, 200), sf::Color(50, 60, 60, 200), sf::Color(255, 255, 255, 200),
		fullscreen
	);


	
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font);

	this->optionsText.setPosition(sf::Vector2f(this->stateData->window->getSize().x / 19.2f, this->stateData->window->getSize().y / 10.8));

	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));


	this->optionsText.setString(
		"Resolution\n\n\nFullscreen\n\n\nVsync\n\n\nAntialiasing\n\n\n"

	);
}

SettingsState::SettingsState(StateData* state_data)
	: State(state_data), gfxSettings(*state_data->gfxSettings)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initTextures();
	this->initTitle();
	this->initGui();
	this->initText();
}

SettingsState::~SettingsState()
{
	//Deletes GUI elements after state is ended
	// 
	//buttons
	auto iterator = this->buttons.begin();
	for (iterator = this->buttons.begin(); iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
	}
	//dropdowns
	auto iterator2 = this->dropDownLists.begin();
	for (iterator2 = this->dropDownLists.begin(); iterator2 != this->dropDownLists.end(); ++iterator2)
	{
		delete iterator2->second;
	}

	auto iterator3 = this->arrowSelectors.begin();
	for (iterator3 = this->arrowSelectors.begin(); iterator3 != this->arrowSelectors.end(); ++iterator3)
	{
		delete iterator3->second;
	}
	
	auto iterator4 = this->toggleSwitches.begin();
	for (iterator4 = this->toggleSwitches.begin(); iterator4 != this->toggleSwitches.end(); ++iterator4)
	{
		delete iterator4->second;
	}
}

//Access

//Functions

void SettingsState::refreshState(unsigned short default_index, bool fullscreen)
{
	auto iterator = this->buttons.begin();
	for (iterator = this->buttons.begin(); iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
	}

	auto iterator2 = this->dropDownLists.begin();
	for (iterator2 = this->dropDownLists.begin(); iterator2 != this->dropDownLists.end(); ++iterator2)
	{
		delete iterator2->second;
	}

	auto iterator3 = this->arrowSelectors.begin();
	for (iterator3 = this->arrowSelectors.begin(); iterator3 != this->arrowSelectors.end(); ++iterator3)
	{
		delete iterator3->second;
	}

	auto iterator4 = this->toggleSwitches.begin();
	for (iterator4 = this->toggleSwitches.begin(); iterator4 != this->toggleSwitches.end(); ++iterator4)
	{
		delete iterator4->second;
	}
	initGui(default_index, fullscreen);
	initTitle();
	initText();
}

void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGui()
{
	/*Updates all gui elements in this state w/ functionalities*/
	//BUTTONS
	for (auto& iterator : this->buttons)
	{
		iterator.second->update(this->mousePosView);
	}
	//BUTTON FUNCTIONALITIES
	
	//Quit Game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}
	//Apply Selected Settings
	if (this->buttons["APPLY"]->isPressed())
	{
		this->stateData->gfxSettings->resolution = this->modes[this->arrowSelectors["RESOLUTION"]->getActiveIndex()];
		this->stateData->gfxSettings->fullscreen = this->toggleSwitches["FULLSCREEN"]->getToggled();

		if (!this->stateData->gfxSettings->fullscreen)
			this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Titlebar | sf::Style::Close);
		else
			this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Fullscreen);

		this->refreshState(this->arrowSelectors["RESOLUTION"]->getActiveIndex(), this->toggleSwitches["FULLSCREEN"]->getToggled());
	}
	if (this->buttons["SAVE"]->isPressed())
	{
		this->stateData->gfxSettings->resolution = this->modes[this->arrowSelectors["RESOLUTION"]->getActiveIndex()];

		//set active window to new settings
		if(!this->stateData->gfxSettings->fullscreen)
			this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Titlebar | sf::Style::Close);
		else
			this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Fullscreen);
		//Save Changes to .ini
		this->stateData->gfxSettings->saveToFile("Config/graphics.ini");

		//update gui scale and position
		this->refreshState(this->arrowSelectors["RESOLUTION"]->getActiveIndex(), this->toggleSwitches["FULLSCREEN"]->getToggled());
	}

	//DROPDOWNS
	for (auto& iterator : this->dropDownLists)
	{
		iterator.second->update(this->mousePosView);
	}
	//DROPDOWNS FUNCTIONALITIES

	//ARROW SELECTORS
	for (auto& iterator : this->arrowSelectors)
	{
		iterator.second->update(this->mousePosView);
	}

	//TOGGLE SWITCHES
	for (auto& iterator : this->toggleSwitches)
	{
		iterator.second->update(this->mousePosView);
	}
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui();


}

void SettingsState::renderGui(sf::RenderTarget* target)
{
	for (auto& iterator : this->buttons)
	{
		iterator.second->render(*target);
	}

	for (auto& iterator : this->dropDownLists)
	{
		iterator.second->render(*target);
	}

	for (auto& iterator : this->arrowSelectors)
	{
		iterator.second->render(*target);
	}

	for (auto& iterator : this->toggleSwitches)
	{
		iterator.second->render(*target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->title);
	this->renderGui(target);

	target->draw(this->optionsText);


	//REMOVE LATER
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);

}


