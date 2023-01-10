#include "Game.h"


	//Static Functions

	//Initializer Functions

void Game::initVariables()
{
	this->window = nullptr;
	this->fullscreen = false;
	this->dt = 0.f;
}

void Game::initWindow()
{
	/*Creates window using edscriptors form window.ini file.*/

	std::ifstream file("Config/window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned int framerate_limit = 120;
	bool vertical_sync = false;
	unsigned antialiasing_level = 0;

	if (file.is_open())
	{
		std::getline(file, title);
		file >> window_bounds.width >> window_bounds.height;
		file >> fullscreen;
		file >> framerate_limit;
		file >> vertical_sync;
		file >> antialiasing_level;
	}

	file.close();

	this->fullscreen = fullscreen;
	sf::ContextSettings window_settings;
	this->windowSettings.antialiasingLevel = antialiasing_level;

	if(this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync);
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

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}



	//Constructer/Destructers
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initKeys();
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


