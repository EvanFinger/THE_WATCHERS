#include "stdafx.h"
#include "GameState.h"


void GameState::initRenderTextureSprite()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0, 0,
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);
		
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			this->stateData->gfxSettings->resolution.width / 2.f,
			this->stateData->gfxSettings->resolution.height / 2.f
		)
	);
}

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

void GameState::initTilemap()
{
	tilemap = new Tilemap();
}

void GameState::initPlayer()
{
	this->player = new Player(0, 0, 20, this->textures["PLAYER_SHEET"]);
	this->player->setScale(2, 2);
}

//Constructor/destructor
GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initRenderTextureSprite();
	this->initView();
	this->initFonts();
	this->initKeybinds();
	this->initTextures();
	this->initTilemap();
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
	delete this->tilemap;
}


void GameState::updatePlayerView(const float& dt)
{
	this->view.setCenter(
	this->player->getEntityPosition()
	);
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
		
		this->updatePlayerView(dt);
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
	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tilemap->render(this->renderTexture);
	this->player->render(&this->renderTexture);

	if (this->paused) //render pause window
	{
		target->setView(this->renderTexture.getDefaultView());
		this->pauseMenu->render(this->renderTexture);
	}

	//Finalize the render (things that move with player)
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);

	//render static objects
	this->healthbar->render(target);
}
