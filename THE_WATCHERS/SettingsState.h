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
    std::map<std::string, gui::DropdownList*> dropDownLists;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    

    //Functions
    void initVariables();
    void initFonts();
    void initKeybinds();
    void initTextures();
    void initTitle();
    void initGui();
    void initText();

public:

    SettingsState(sf::RenderWindow* window, std::map<std::string, sf::Keyboard::Key>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingsState();

    //Access

    //Functions

    void updateInput(const float& dt);
    void updateGui();
    void update(const float& dt);
    void renderGui(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

#endif