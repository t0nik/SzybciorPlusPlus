#include "stdafx.h"
#include "GameState.h"

void GameState::initDeferredRender()
{
	this->renderTexture.create(1920, 1080);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
}

//Funkcje inicjalizuj¹ce
void GameState::initView()
{
	this->view.setSize(sf::Vector2f(1920.f, 1080.f));
	this->view.setCenter(1920.f/2, 1080.f/2);
}

void GameState::initKeybinds()
{
	std::ifstream ifstream("Config/gamestate_keys.ini");

	if (ifstream.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifstream >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}

	}

	ifstream.close();
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Geomanist-Regular.otf"))
	{
		throw("BLAD::GAMESTATE::NIE ZALADOWANO CZCIONKI");
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Sprites/Player/test.png"))
	{
		throw "ERROR::GAMESTATE::NIE_MOZNA_ZALADOWAC_TEKSTURY_IDLE_GRACZA";
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 500.f, "Quit");
}

void GameState::initPlayers()
{
	this->player = new Player(1120, 1360, this->textures["PLAYER_IDLE"]);
}

void GameState::initTilemap()
{
	this->tilemap = new Tilemap(this->stateData->gridSize, 100, 80, "Resources/Images/Tiles/texturesheet.png");
	this->tilemap->loadFromFile("test.szybcior");
}

//Konstruktory / Destruktory
GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initTilemap();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->tilemap;
}

//Funckje
void GameState::updateView(const float& dt)
{
	this->view.setCenter(std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y));
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updateGravity(const float& dt)
{
	//Grawitacja
		this->player->move(0.f, 1.f, dt);
}

void GameState::updatePlayerInput(const float& dt)
{

	//Odœwie¿a input playera
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("JUMP"))) /*&& this->player->onGround()*/)
		this->player->jump(3.f, dt);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTilemap(const float& dt)
{
	this->tilemap->update();
	this->tilemap->updateCollision(this->player, dt);
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Odœwie¿anie bez pauzy
	{
		this->updateView(dt);

		this->updateGravity(dt);

		this->updatePlayerInput(dt);

		this->updateTilemap(dt);

		this->player->update(dt);
	}
	else // Odœwie¿anie z pauz¹
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tilemap->render(this->renderTexture);

	this->player->render(this->renderTexture);

	if (this->paused) // Renderowanie menu pauzy
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	//KOÑCOWY RENDER
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}