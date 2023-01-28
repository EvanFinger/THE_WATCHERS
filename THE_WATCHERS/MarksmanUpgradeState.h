#ifndef MARKSMAN_UPGRADE_STATE
#define MARKSMAN_UPGRADE_STATE_H


#include "TricksterUpgradeState.h"



class MarksmanUpgradeState :
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
    MarksmanUpgradeState(sf::RenderWindow* window, std::map<std::string, sf::Keyboard::Key>* supportedKeys, std::stack<State*>* states);
    virtual ~MarksmanUpgradeState();

    //Functions


    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

#endif