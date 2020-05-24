#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
	bool collision, short type)
{
	this->tile.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->tile.setFillColor(sf::Color::White);
	//this->tile.setOutlineThickness(-1.f);
	//this->tile.setOutlineColor(sf::Color::White);
	this->tile.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
	this->tile.setTexture(&texture);
	this->tile.setTextureRect(texture_rect);

	this->collision = collision;
	this->type = type;
}

Tile::~Tile()
{

}

//Akcesory
const bool& Tile::getCollision() const
{
	return this->collision;
}


const sf::Vector2f& Tile::getPosition() const
{
	return this->tile.getPosition();
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->tile.getGlobalBounds();
}


//Funkcje
const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return this->tile.getGlobalBounds().intersects(bounds);
}

const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << this->tile.getTextureRect().left << " " << this->tile.getTextureRect().top << " " << this->collision << " " << this->type;
	
	return ss.str();
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->tile);
}