#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "Tilemap.h"

class PauseMenu;
class Player;
class TileMap;
class sf::View;
class sf::Font;
class sf::RenderTarget;

class GameState :
	public State
{
private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pmenu;

	Player* player;
	
	Tilemap* tilemap;

	//Funkcje inicjalizuj¹ce
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initTilemap();


public:
	GameState(StateData* state_data);
	virtual ~GameState();

	//Funkcje
	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updateGravity(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void updateTilemap(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

