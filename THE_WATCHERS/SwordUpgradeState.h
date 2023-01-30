#ifndef SWORD_MASTER_UPGRADE_STATE_H
#define SWORD_MASTER_UPGRADE_STATE

#include "MarksmanUpgradeState.h"


class SwordUpgradeState :
    public State
{
private:
    //Variables
    sf::RectangleShape background;
    sf::Font font;
    sf::Text title;

    std::map<std::string, gui::Button*> buttons;

    //Functions
    void initFonts();
    void initKeybinds();
    void initTextures();
    void initTitle();
    void initButtons();


public:
    SwordUpgradeState(StateData* state_data);
    virtual ~SwordUpgradeState();

    //Functions


    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

#endif