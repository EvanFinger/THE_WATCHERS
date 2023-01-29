#include "stdafx.h"
#include "Game.h"


	//Static Functions

	//Initializer Functions

void Game::initVariables()
{
	this->window = nullptr;
	this->dt = 0.f;
	this->gridSize = 50.f;
}

void Game::initGfxSettings()
{
	this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initWindow()
{
	/*Creates window using edscriptors form window.ini file.*/
	if(this->gfxSettings.fullscreen)
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution, 
			this->gfxSettings.title, 
			sf::Style::Fullscreen, 
			this->gfxSettings.contextSettings
		);
	else
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Titlebar | sf::Style::Close, 
			this->gfxSettings.contextSettings
		);

	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys()
{
	std::ifstream file("Config/supported_keys.ini");

	if (file.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (file >> key >> key_value)
		{
			this->supportedKeys[key] = static_cast<sf::Keyboard::Key>(key_value);
		}
	}

	file.close();
}

void Game::initStatedata()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}



	//Constructer/Destructers
Game::Game()
{
	this->initVariables();
	this->initGfxSettings();
	this->initWindow();
	this->initKeys();
	this->initStatedata();
	this->initStates();
	
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}






//Functions

void Game::endApplication()
{
	std::cout << "Ending Application" << "\n";
}

void Game::updateDt()
{
	/*Updates dt variable with time taken to update/render entire frame.*/

	this->dt = this->dtClock.restart().asSeconds();

}
void Game::updateSFMLEvents()
{
	/*Polls for mouse/keyboard events.*/
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//Application Ending
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	//Render Items
	if (!this->states.empty())
		this->states.top()->render(this->window);

	this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
		this->updateDt();
		this->update();
		this->render();
    }
}


