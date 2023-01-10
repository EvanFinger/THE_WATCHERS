#ifndef GAME_H
#define GAME_H


#include "MainMenuState.h"

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, sf::Keyboard::Key> supportedKeys;

	//Initialization
	void initVariables();
	void initWindow();
	void initKeys();
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
