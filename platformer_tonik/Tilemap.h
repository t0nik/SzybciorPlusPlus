#pragma once

#include"Tile.h"
#include"Entity.h"

class Tile;
class Entity;

class Tilemap
{
private:
	void clear();

	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	unsigned layers;
	std::vector< std::vector< std::vector< Tile* > > > map;
	std::string textureFile;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;

	//Ogranicza obszar wokó³ entity
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

public:
	Tilemap(float gridSize, unsigned witdth, unsigned height, std::string texture_file);
	virtual ~Tilemap();

	//Akcesory
	const sf::Texture* getTileSheet() const;

	//Funkcje
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void updateCollision(Entity* entity, const float& dt);

	void update();
	void render(sf::RenderTarget& target, Entity* entity = NULL);



};

