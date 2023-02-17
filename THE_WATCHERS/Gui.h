#ifndef GUI_H
#define GUI_H


enum buton_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE, BTN_CLICKED};

namespace gui
{
//BUTTON CLASS (tuturial help: Suraj Sharma https://www.youtube.com/watch?v=KpRbBtlbMfg&list=PL6xSOsbVA1ebkU66okpi-KViAO8_9DJKg&index=15)
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		bool mouseDown;
		bool toggleable;
		bool toggled;
		bool isVoid;



		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		Button(
			bool toggleable, 
			float x, float y, float width, float height,
			sf::Font* font, unsigned int fontSize, std::string text,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();

		//Access
		const bool isPressed() const;
		const bool isToggled() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);\
		void setSize(float width, float height, unsigned int font_Size);
		void setSize(float width, float height);
		void setPosition(float x, float y);
		
		

		//Functions
		void activate();
		void deactivate();
		void setId(const short unsigned id);

		void toggleOn();
		void toggleOff();
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

//DROPDOWN MENU CLASS (tuturial help: Suraj Sharma https://www.youtube.com/watch?v=ew--THZM2II&list=PL6xSOsbVA1ebkU66okpi-KViAO8_9DJKg&index=47)
	class DropdownList
	{
	private:
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;

	public:
		DropdownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned numberOfElements, unsigned default_index = 0);
		~DropdownList();

		//Access
		const unsigned short getActiveId() const;

		//Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

//ARROWSELECTION CLASS (MADE BY ME)
	class ArrowSelection
	{
	private:
		sf::Font& font;
		gui::Button* indexLeft;
		gui::Button* indexRight;
		sf::RectangleShape shape;
		sf::Text activeItem;
		std::vector<std::string> list;
		unsigned short activeIndex;
	public:
		ArrowSelection(
			float x, float y, float width, float height, 
			sf::Font& font, std::string list[],
			unsigned short num_of_elements, unsigned short default_index = 0
		);
		~ArrowSelection();

		//Access
		const unsigned short getActiveIndex() const;

		//Funtions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

//TOGGLE SWITCH CLASS (MADE BY ME)
	class ToggleSwitch
	{
	private:
		sf::RectangleShape switchOff;
		sf::RectangleShape switchOn;
		unsigned short state;
		bool mouseDown, toggled;
		
		sf::Color switchBackground;
		sf::Color switchActive;
		sf::Color switchLever;

		sf::Color hoverSwitchBackground;
		sf::Color hoverSwitchActive;
		sf::Color hoverSwitchLever;

		sf::Color clickedSwitchBackground;
		sf::Color clickedSwitchActive;
		sf::Color clickedSwitchLever;

	public:
		ToggleSwitch(
			float x, float y, float width, float height,
			sf::Color switch_background, sf::Color switch_active, sf::Color switch_lever,
			bool init_state = 0
		);
		~ToggleSwitch();
		
		//Access
		const bool getToggled() const;

		//Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};
}
#endif