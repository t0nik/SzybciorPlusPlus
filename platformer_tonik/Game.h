#pragma once

#include"MainMenuState.h"

class Game
{
private:
	//Zmienne
	GraphicsSettings gfxSettings;
	sf::RenderWindow *window;
	StateData stateData;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	float gridSize;

	//Inicjalizacja (Start)
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();


public:
	//Konstruktory/Destruktory
	Game();
	virtual ~Game();

	//Funkcje

	//Zwyczajne
	void endApplication();

	//Odœwie¿anie
	void updateDt();
	void updateSMFLEvents();
	void update();

	//Rendering
	void render();

	//Kluczowe
	void run();

};

