#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	//Inicjalizacja t³a
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));
	
	//Inicjalizacja containera
	this->container.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x) / 4.f,
		static_cast<float>(window.getSize().y) - 90.f
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		30.f);

	//Inicjalizacja tekstu
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(50);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 35.f);
}

PauseMenu::~PauseMenu()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

//Funkcje

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 250.f;
	float height = 75.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
	this->buttons[key] = new gui::Button(x, y, width, height,
		&this->font, text, 42,
		sf::Color(230, 230, 230, 200), sf::Color(50, 50, 50, 200), sf::Color(10, 10, 10, 200),
		sf::Color(0, 50, 100, 0), sf::Color(170, 220, 230, 0), sf::Color(20, 20, 20, 0));

}

void PauseMenu::update(const sf::Vector2i& mousePosWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto &i : this->buttons)
	{
		(i.second->render(target));
	}

	target.draw(this->menuText);
}

