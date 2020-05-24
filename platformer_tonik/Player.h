#pragma once

#include "Entity.h"

class Player :
	public Entity
{
private:
	//Zmienne

	//Funkcje inicjalizuj¹ce
	void initVariables();
	void initComponents();
public:
	Player(float x, float y, sf::Texture& texture);
	virtual ~Player();

	//Funkcje
	void update(const float& dt);
	
};