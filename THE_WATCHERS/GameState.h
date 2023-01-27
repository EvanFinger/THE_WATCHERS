#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "HealthBar.h"

class GameState :
    public State
{
private:
    Player* player;

    HealthBar* healthbar;

    //Functions
    void initKeybinds();
    void initTextures();
    void initHealthbar();
    void initPlayer();

public:
    GameState(sf::RenderWindow* window, std::map<std::string, sf::Keyboard::Key>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    //Functions


    void updateInput(const float& dt);
    void updateHealthbar();
    void update(const float& dt);

    void render(sf::RenderTarget* target = nullptr);
};

#endif