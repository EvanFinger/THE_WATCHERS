#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H


#include "Gui.h"


class PauseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;
public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	std::map<std::string, gui::Button*>& getButtons();

	const bool& isButtonPressed(const std::string key);
	void addButton();
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};


#endif