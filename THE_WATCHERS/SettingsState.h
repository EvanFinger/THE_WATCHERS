#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H
#include "State.h"

class SettingsState :
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

    SettingsState(sf::RenderWindow* window, std::map<std::string, sf::Keyboard::Key>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingsState();

    //Access

    //Functions

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

#endif