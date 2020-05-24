#include "stdafx.h"
#include "TileMap.h"

void Tilemap::clear()
{
	for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{

				delete this->map[x][y][z];
				this->map[x][y][z] = NULL;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();

	//std::cout << this->map.size() << "\n";
}

Tilemap::Tilemap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 5;
	this->textureFile = texture_file;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector<Tile*> >());
	for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());
			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}

	if(!this->tileSheet.loadFromFile(texture_file))
		std::cout << "ERROR::TILEMAP::NIE UDALO SIE ZALADOWAC TEKSTURY OBSZARU::NAZWAPLIKU: " << texture_file << "\n";

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(-1.f);
}

Tilemap::~Tilemap()
{
	this->clear();
}

//Akcesory
const sf::Texture* Tilemap::getTileSheet() const
{
	return &this->tileSheet;
}


//Funkcje
void Tilemap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	/*We� trzy indeksy z pozycji myszki na siatce i dodaj obszar w tej pozycji je�li tablica mapy obszar�w pozwala na to*/

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == NULL)
		{
			/*Mo�na doda� obszar*/
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type);
			//std::cout << "DEBUG: DODANO OBSZAR!" << "\n";
		}

	}

}

void Tilemap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	/*We� trzy indeksy z pozycji myszki na siatce i usu� obszar w tej pozycji je�li tablica mapy obszar�w pozwala na to*/

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != NULL)
		{
			/*Mo�na usun�� obszar*/
			delete this->map[x][y][z];
			this->map[x][y][z] = NULL;
			//std::cout << "DEBUG: USUNIETO OBSZAR!" << "\n";
		}


	}
}

void Tilemap::saveToFile(const std::string file_name)
{
	/*Zapisuje map� obszar�w do pliku textowego
	Format:
	Podstawowe:
	Rozmiar x y
	Rozmiar siatki
	Warstwy
	Plik z tekstur�

	Wszystkie obszary:
	Pozycja na siatce x y warstwa, Prostok�t z tekstur� x y,
	Kolizja, Typ
	*/

	std::ofstream ofstreamfile;

	ofstreamfile.open(file_name);

	if (ofstreamfile.is_open())
	{
		ofstreamfile << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					if (this->map[x][y][z])
						ofstreamfile << x << " " << y << " " << z << " " <<
						this->map[x][y][z]->getAsString()
						<< " "; //OSTATNIA SPACJA NIE MA BYC ZAPISANA
				}
			}
		}
	}
	else
	{
		std::cout << "BLAD::TILEMAP::NIE MOZNA ZAPISAC MAPY DO PLIKU::NAZWAPLIKU:" << file_name << "\n";
	}

	ofstreamfile.close();
}

void Tilemap::loadFromFile(const std::string file_name)
{
	std::ifstream ifstreamfile;

	ifstreamfile.open(file_name);

	if (ifstreamfile.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool collision = false;
		short type = 0;

		//Podstawowe
		ifstreamfile >> size.x >> size.y >> gridSize >> layers >> texture_file;


		//Wszystkie obszary
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector<Tile*> >());
		for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());
				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, NULL);
				}
			}
		}
	
		if (!this->tileSheet.loadFromFile(texture_file))
			std::cout << "ERROR::TILEMAP::NIE UDALO SIE ZALADOWAC TEKSTURY OBSZARU::NAZWAPLIKU: " << texture_file << "\n";

		//Za�aduj wszystkie obszary
		while (ifstreamfile >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z] = new Tile(
				x, y,
				this->gridSizeF, this->tileSheet,
				sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU),
				collision, type);
		}

	}
	else
	{
		std::cout << "BLAD::TILEMAP::NIE MOZNA ZALADOWAC MAPY Z PLIKU::NAZWAPLIKU:" << file_name << "\n";
	}

	ifstreamfile.close();
}

void Tilemap::updateCollision(Entity* entity, const float& dt)
{
	//GRANICE �WIATA
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	//OBSZARY
	this->fromX = entity->getGridPosition(this->gridSizeU).x - 1;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeU).x + 3;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeU).y - 1;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeU).y + 3;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;

	for (size_t x = this->fromX; x < this->toX; x++)
	{
		for (size_t y = this->fromY; y < this->toY; y++)
		{
			sf::FloatRect playerBounds = entity->getGlobalBounds();
			sf::FloatRect wallBounds = this->map[x][y][this->layer]->getGlobalBounds();
			sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

			if (this->map[x][y][this->layer]->getCollision() && this->map[x][y][this->layer]->intersects(nextPositionBounds))
			{
				//Dolna kolizja
				if (playerBounds.top < wallBounds.top
					&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left
					)
				{
					entity->stopVelocityY();
					entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
				}
				
				//G�rna kolizja
				else if (playerBounds.top > wallBounds.top
					&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left
					)
				{
					entity->stopVelocityY();
					entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
				}
				//Prawa kolizja
				else if (playerBounds.left < wallBounds.left
					&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
					&& playerBounds.top < wallBounds.top + wallBounds.height
					&& playerBounds.top + playerBounds.height > wallBounds.top
					)
				{
					entity->stopVelocityX();
					entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
				}

				//Lewa kolizja
				else if (playerBounds.left > wallBounds.left
					&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
					&& playerBounds.top < wallBounds.top + wallBounds.height
					&& playerBounds.top + playerBounds.height > wallBounds.top
					)
				{
					entity->stopVelocityX();
					entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
				}

			}
		}
	}
}

void Tilemap::update()
{

}

void Tilemap::render(sf::RenderTarget& target, Entity* entity)
{
	for (auto &x : this->map)
	{
		for (auto& y : x)
		{
			for (auto *z : y)
			{
				if (z != NULL)
				{
					z->render(target);
					if (z->getCollision())
					{
						this->collisionBox.setPosition(z->getPosition());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
}
