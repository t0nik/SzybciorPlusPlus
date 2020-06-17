#pragma once

#include"GameState.h"
#include"EditorState.h"
#include"SettingsState.h"
#include"Gui.h"

class MainMenuState :
	public State
{
private:
	//Zmienne
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	//Funkcje
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	//Funkcje
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void rednerButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

