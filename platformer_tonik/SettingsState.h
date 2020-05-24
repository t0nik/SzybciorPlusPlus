#pragma once

#include "State.h"
#include "Gui.h"

class SettingsState :
	public State
{
private:
	//Zmienne
	GraphicsSettings& gfxSettings;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropDownLists;

	sf::Text optionsText;

	std::vector<sf::VideoMode> modes;

	//Funkcje
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initGui();
	void initText();

public:
	SettingsState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SettingsState();


	//Akcesory

	//Funkcje
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void rednerGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

