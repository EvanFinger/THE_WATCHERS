#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H
#include "State.h"

class SettingsState :
    public State
{

private:
    //Variables
    GraphicsSettings& gfxSettings;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text title;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropdownList*> dropDownLists;
    std::map<std::string, gui::ArrowSelection*> arrowSelectors;
    std::map<std::string, gui::ToggleSwitch*> toggleSwitches;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    

    //Functions
    void initVariables();
    void initFonts();
    void initKeybinds();
    void initTextures();
    void initTitle();
    void initGui(unsigned short default_index = 0, bool fullscreen = false);
    void initText();

public:

    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    //Access

    //Functions

    void refreshState(unsigned short default_index = 0, bool fullscreen = false);
    void updateInput(const float& dt);
    void updateGui();
    void update(const float& dt);
    void renderGui(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

#endif