#ifndef CHARACTER_SELECT_STATE_H
#define CHARACTER_SELECT_STATE_H

#include "SwordUpgradeState.h"



class CharacterSelectState :
    public State
{
private:
    //Variables
    sf::RectangleShape background;
    sf::Font font;
    sf::Text title;
    //character description variables
    sf::Image playerImage;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    sf::Text playerSummary;

    std::map<std::string, gui::Button*> buttons;

    //Functions
    void initFonts();
    void initKeybinds();
    void initTextures();
    void initTitle();
    void initPlayerDescription();
    void initButtons();


public:
    CharacterSelectState(StateData* state_data);
    virtual ~CharacterSelectState();

    //Functions


    void updateInput(const float& dt);
    void updateButtons();
    void updatePlayerDescription();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

#endif