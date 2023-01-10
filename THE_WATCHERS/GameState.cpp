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
	if (!this->textures["PLAYER_IDLE_0"].loadFromFile("Images/Players/player_idle_0.png"))
	{
		throw("ERROR::GAME_STATE FAILED TO LOAD PLAYER IDLE TEXTURE");
	}
}

void GameState::initPlayer()
{
	this->player = new Player(0, 0, &this->textures["PLAYER_IDLE_0"]);
}

//Constructor/destructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, sf::Keyboard::Key>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initTextures();
	this->initPlayer();
}

GameState::~GameState()
{
	delete this->player;
}


void GameState::updateInput(const float& dt)
{
	//Update Player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(dt, 0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->player->update(dt);
	
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->player->render(target);
}
