#ifndef STATE_H
#define STATE_H


#include "Player.h"
#include "Gui.h"
#include "GraphicsSettings.h"

class State;

class StateData
{
public:
	StateData() {};

	//Variables
	float gridSize;
	sf::RenderWindow* window; 
	GraphicsSettings* gfxSettings;
	std::map < std::string, sf::Keyboard::Key>* supportedKeys;
	std::stack<State*>* states;
};

class State
{
private:

protected:
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, sf::Keyboard::Key>* supportedKeys;
	std::map<std::string, sf::Keyboard::Key> keybinds;
	bool quit;
	bool paused;
	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;
	virtual void initTextures() = 0;

public:
	State(StateData* state_data);
	virtual ~State();

	const bool& getQuit() const;
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions();
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float&  dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif