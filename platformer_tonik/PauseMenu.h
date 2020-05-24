#pragma once

#include"Gui.h"


class PauseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;
	
public:
	PauseMenu(sf::RenderWindow &window, sf::Font& font);
	virtual ~PauseMenu();

	//Akcesory
	std::map<std::string, gui::Button*>& getButtons();

	//Funkcje
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

