#pragma once

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "Tilemap.h"

class EditorState :
	public State
{
private:
	//Zmienne
	sf::View view;

	sf::Font font;
	sf::Text cursorText;
	PauseMenu* pmenu;

	std::map<std::string, gui::Button*> buttons;

	Tilemap* tilemap;

	sf::RectangleShape sidebar;

	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;

	gui::TextureSelector* textureSelector;


	bool collision;
	short type;
	float cameraSpeed;

	//Funkcje
	void initVariables();
	void initView();
	void initBackground();
	void initFonts();
	void initText();
	void initKeybinds();
	void initPauseMenu();
	void initButtons();
	void initGui();
	void initTilemap();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	//Funkcje
	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGui(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void rednerButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

