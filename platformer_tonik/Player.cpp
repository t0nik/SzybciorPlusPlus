#include "stdafx.h"
#include "Player.h"

//Funkcje inicjalizuj¹ce
void Player::initVariables()
{

}

void Player::initComponents()
{
	this->createHitboxComponent(this->sprite, 30.f, 0.f, 73.f, 128.f);
	this->createMovementComponent(600.f, 800.f, 150.f, 100.f);
}

//Konstruktory / Destruktory

Player::Player(float x, float y, sf::Texture& texture)
{
	this->initVariables();
	this->setPosition(x, y);
	this->setTexture(texture);
	this->initComponents();
}

Player::~Player()
{

}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	this->hitboxComponent->update();
}