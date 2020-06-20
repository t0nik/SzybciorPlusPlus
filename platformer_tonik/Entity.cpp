#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
}

//Funkcje komponent�w

void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float gravity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, gravity, acceleration, deceleration);
}

const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	return this->sprite.getPosition();
}

const sf::Vector2u Entity::getGridPosition(const unsigned gridSizeU) const
{
	if (this->hitboxComponent)
		return sf::Vector2u(
			static_cast<unsigned>(this->hitboxComponent->getPosition().x) / gridSizeU,
			static_cast<unsigned>(this->hitboxComponent->getPosition().y) / gridSizeU);


	return sf::Vector2u(
		static_cast<unsigned>(this->sprite.getPosition().x) / gridSizeU,
		static_cast<unsigned>(this->sprite.getPosition().y) / gridSizeU);

}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();

		return this->sprite.getGlobalBounds();
}

const sf::FloatRect& Entity::getNextPositionBounds(const float& dt) const
{
	if (this->hitboxComponent && this->movementComponent)
	{
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);

	}
	return sf::FloatRect();
}


//Funkcje

void Entity::setPosition(const float x, const float y)
{
	if(this->hitboxComponent)
		this->hitboxComponent->setPosition(x, y);
	else
		this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt); //Ustawia pr�dko��
	}

}

void Entity::stopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}

bool Entity::onGround()
{
	return false;
}

void Entity::jump(const float dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->jump(dir_y, dt);
	}
}

void Entity::update(const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->update(dt);
	}
	if (this->hitboxComponent)
		this->hitboxComponent->update();
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
}

