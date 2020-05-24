#pragma once

#include"Player.h"
#include "GraphicsSettings.h"

class State
{
private:

protected:

	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	//Zasoby
	std::map<std::string, sf::Texture> textures;

	//Funkcje inicjalizuj¹ce
	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();
	
	//Akcesory
	const bool& getQuit() const;
	const bool getKeytime();

	//Funkcje
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions(sf::View* view = NULL);
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

