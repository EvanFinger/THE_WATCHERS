#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "HealthBar.h"
#include "Tilemap.h"

class GameState :
    public State
{
private:
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    PauseMenu* pauseMenu;
    sf::Font font;

    Player* player;

    HealthBar* healthbar;

    Tilemap* tilemap;

    bool keyPressed;

    //Functions
    void initRenderTextureSprite();
    void initView();
    void initFonts();
    void initKeybinds();
    void initTextures();
    void initPauseMenu();
    void initHealthbar();
    void initTilemap();
    void initPlayer();

public:
    GameState(StateData* state_data);
    virtual ~GameState();

    //Functions
    void updatePlayerView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseButtonInput();
    void updateHealthbar();
    void update(const float& dt);

    void render(sf::RenderTarget* target = nullptr);
};

#endif