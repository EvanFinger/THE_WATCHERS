#include "stdafx.h"
#include "GameState.h"


void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/yoster.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

//Init functions
void GameState::initKeybinds()
{
	std::ifstream file("Config/gamestate_keybinds.ini");

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

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Images/Players/blue_ball_idle_0.png"))
	{
		throw("ERROR::GAME_STATE FAILED TO LOAD PLAYER TEXTURE");
	}

	if (!this->textures["HEALTHBAR_SHEET"].loadFromFile("Images/Misc/hp_heart.png"))
	{
		throw("ERROR::GAME_STATE FAILED TO LOAD PLAYEr HEALTH TEXTURE");
	}
	
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);
	this->pauseMenu->addButton();
}

void GameState::initHealthbar()
{
	this->healthbar = new HealthBar(this->player->durabilityComponent->healthComponent->getMaxHealth(), 0, 0, this->textures["HEALTHBAR_SHEET"]);
}

void GameState::initPlayer()
{
	this->player = new Player(0, 0, 20, this->textures["PLAYER_SHEET"]);
	this->player->setScale(2, 2);
}

//Constructor/destructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, sf::Keyboard::Key>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initFonts();
	this->initKeybinds();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayer();
	this->initHealthbar();

	this->keyPressed = false;
	
}

GameState::~GameState()
{
	delete this->player;
	delete this->healthbar;
	delete this->pauseMenu;
}


void GameState::updateInput(const float& dt)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && !keyPressed)
	{
		this->keyPressed = true;
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}	
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) //Prevents infinite key loop
	{
		this->keyPressed = false;
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	//Update Player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
}

void GameState::updatePauseButtonInput()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
		this->endState();
	if (this->pauseMenu->isButtonPressed("RESUME"))
		this->unpauseState();
}

void GameState::updateHealthbar()
{
	this->healthbar->maxHealth = this->player->durabilityComponent->healthComponent->getMaxHealth();
	this->healthbar->health = this->player->durabilityComponent->healthComponent->getHealth();
}

void GameState::update(const float& dt)
{		
	this->updateMousePositions();
	this->updateInput(dt);

	if (!this->paused)//unpaused
	{
		
		
		this->updatePlayerInput(dt);
		this->updateHealthbar();

		this->player->update(dt);
	}
	else //paused
	{
		this->pauseMenu->update(this->mousePosView);
		this->updatePauseButtonInput();
	}
}


void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	
	this->player->render(target);
	this->healthbar->render(target);

	if (this->paused) //render pause window
	{
		this->pauseMenu->render(*target);
	}

}
