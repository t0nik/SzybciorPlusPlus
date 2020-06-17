#pragma once

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float gravity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	//Funkcje inicjalizuj¹ce

public:
	MovementComponent(sf::Sprite& sprite,  float maxVelocity, float gravity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Akcesory
	const sf::Vector2f& getVelocity() const;

	const bool& onGround() const;

	//Functions
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();
	void move(const float dir_x, const float dir_y, const float& dt);
	void jump(const float dir_y, const float& dt);
	void update(const float &dt);
};

