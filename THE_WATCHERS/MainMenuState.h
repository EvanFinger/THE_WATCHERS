#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "CharacterSelectState.h"
#include "SettingsState.h"
#include "Button.h"

class MainMenuState :
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
    MainMenuState(sf::RenderWindow* window, std::map<std::string, sf::Keyboard::Key>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();

    //Functions


    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};


#endif