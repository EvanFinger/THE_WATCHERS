#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "HealthBar.h"

class GameState :
    public State
{
private:
    PauseMenu* pauseMenu;
    sf::Font font;

    Player* player;

    HealthBar* healthbar;

    bool keyPressed;

    //Functions
    void initFonts();
    void initKeybinds();
    void initTextures();
    void initPauseMenu();
    void initHealthbar();
    void initPlayer();

public:
    GameState(StateData* state_data);
    virtual ~GameState();

    //Functions

    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseButtonInput();
    void updateHealthbar();
    void update(const float& dt);

    void render(sf::RenderTarget* target = nullptr);
};

#endif