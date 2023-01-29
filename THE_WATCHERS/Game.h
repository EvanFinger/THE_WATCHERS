#ifndef GAME_H
#define GAME_H


#include "MainMenuState.h"


class Game
{
private:
	


	//Variables
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent;
	

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, sf::Keyboard::Key> supportedKeys;

	float gridSize;

	//Initialization
	void initVariables();
	void initGfxSettings();
	void initWindow();
	void initKeys();
	void initStatedata();
	void initStates();



public:

	//Constructer/Destructers
	Game();
	virtual ~Game();

	//Funtions
	//regular
	void endApplication();

	//update
	void updateDt();
	void updateSFMLEvents();
	void update();
	//render
	void render();
	//core
	void run();
};

#endif
