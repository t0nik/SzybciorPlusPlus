#include "stdafx.h"
#include "MovementComponent.h"
MovementComponent::MovementComponent(sf::Sprite& sprite,
	float maxVelocity, float gravity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), gravity(gravity),
	acceleration(acceleration), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

//Funkcje

void MovementComponent::stopVelocity()
{
	/*Resetuje pr�dko�� do 0*/

	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	/*Resetuje pr�dko�� x do 0*/

	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	/*Resetuje pr�dko�� y do 0*/

	this->velocity.y = 0.f;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	/*Przy�piesza sprite do momentu osi�gni�cia maksymalnej pr�dko�ci*/
	
	this->velocity.x += this->acceleration * dir_x;
	this->velocity.y += this->acceleration * dir_y;


}

void MovementComponent::jump(const float dir_y, const float& dt)
{
	/*Mo�liwo�� skakania*/
	if (this->velocity.y > -this->gravity)
		this->velocity.y -= this->acceleration * dir_y;
		
}

void MovementComponent::update(const float& dt)
{
	/*Sprawdza maksymaln� pr�dko�� i op�nia sprite.
	Rusza sprite.
	*/

	if (this->velocity.x > 0.f) //Sprawdzam dla dodatniego x (prawo)
	{
		//Sprawdzam maksymaln� pr�dko��
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Op�nienie x
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f) //Sprawdzam dla ujemnego x (lewo)
	{
		//Sprawdzam maksymaln� pr�dko��
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Op�nienie
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f) //Sprawdzam dla dodatniego y (grawitacja)
	{
		//Sprawdzam maksymaln� pr�dko��
		if (this->velocity.y > this->gravity)
			this->velocity.y = this->gravity;

		//Op�nienie x
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f) //Sprawdzam dla ujemnego y (skok)
	{
		//Sprawdzam maksymaln� pr�dko��
		if (this->velocity.y < -this->gravity)
			this->velocity.y = -this->gravity;
		//Op�nienie
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//Ko�cowy move
	this->sprite.move(this->velocity * dt); //U�ywa pr�dko�ci
}
