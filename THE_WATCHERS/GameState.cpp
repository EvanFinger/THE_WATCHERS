#include "GameState.h"

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

void GameState::initHealthbar()
{
	this->healthbar = new HealthBar(this->player->durabilityComponent->healthComponent->getMaxHealth(), 0, 0, this->textures["HEALTHBAR_SHEET"]);
}

void GameState::initPlayer()
{
	this->player = new Player(0, 0, 5, this->textures["PLAYER_SHEET"]);
	this->player->setScale(2, 2);
}

//Constructor/destructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, sf::Keyboard::Key>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initTextures();
	this->initPlayer();
	this->initHealthbar();
	
}

GameState::~GameState()
{
	delete this->player;
	delete this->healthbar;
}


void GameState::updateInput(const float& dt)
{
	//Update Player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->move(0.f, -1.f, dt);
		this->player->durabilityComponent->damage(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
	
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
	this->updateHealthbar();

	this->player->update(dt);
	
}


void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	
	this->player->render(target);
	this->healthbar->render(target);

}
