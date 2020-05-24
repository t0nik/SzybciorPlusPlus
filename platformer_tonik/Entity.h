#pragma once

#include "HitboxComponent.h"
#include "MovementComponent.h"

class Entity
{
private:
	void initVariables();

protected:

	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;

public:
	Entity();
	virtual ~Entity();

	//Funkcje komponentów
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height);
	void createMovementComponent(const float maxVelocity, const float gravity, const float acceleration, const float deceleration);

	//Akcesory
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2u getGridPosition(const unsigned gridSizeU) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect& getNextPositionBounds(const float& dt) const;

	//Modyfikatory
	virtual void setPosition(const float x, const float y);
	
	//Funckje
	virtual void move(const float dir_x, const float dir_y, const float& dt);
	virtual void jump(const float dir_y, const float& dt);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
};

