#include "stdafx.h"
#include"Game.h"

//Funkcje statyczne

//Inicjalizacja (Start)

void Game::initVariables()
{
    this->window = NULL;

    this->dt = 0.f;
}

void Game::initGraphicsSettings()
{
    this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initWindow()
{
    /*Tworzy okno SMFL*/
  
    if (this->gfxSettings.fullscreen)
        this->window = new sf::RenderWindow(this->gfxSettings.resolution,
            this->gfxSettings.title,
            sf::Style::Fullscreen,
            this->gfxSettings.contextSettings);
    else
        this->window = new sf::RenderWindow(this->gfxSettings.resolution,
            this->gfxSettings.title,
            sf::Style::Titlebar | sf::Style::Close,
            this->gfxSettings.contextSettings);

    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys()
{
    std::ifstream source("Config/supported_keys.ini");

    if (source.is_open())
    {
        std::string key = "";
        int key_value = 0;
        while (source >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
        
    }

    source.close();

    this->supportedKeys["ESC"] = sf::Keyboard::Key::Escape;
    this->supportedKeys["A"] = sf::Keyboard::Key::A;
    this->supportedKeys["D"] = sf::Keyboard::Key::D;
    this->supportedKeys["W"] = sf::Keyboard::Key::W;
    this->supportedKeys["S"] = sf::Keyboard::Key::S;
    this->supportedKeys["SPACE"] = sf::Keyboard::Key::Space;

//DEBUG USUN POZNIEJ!
    for (auto i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << "\n";
    }

}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, this->gfxSettings, &this->supportedKeys, &this->states));
}

//Konstruktory/Destruktory
Game::Game()
{
    /*Inicjalizacja*/
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game()
{
    /*Usuniêcie wskaŸnika na okno*/
	delete this->window;

    while (!this->states.empty())
    {

        delete this->states.top();
        this->states.pop();
    }

}



//Funkcje
void Game::endApplication()
{
    std::cout << "Koniec pracy aplikacji!" << "\n";
}

void Game::updateDt()
{
    /*Odœwie¿a zmienn¹ dt (delta_time) w czasie odœwie¿ania i renderowania jednej klatki*/
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSMFLEvents()
{
    /*Odœwie¿anie gry*/
    sf::Event event;
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}\

void Game::update()
{
    this->updateSMFLEvents();
    //Odœwie¿anie, przemieszczanie siê po States'ach
    if (!this->states.empty())
    {

        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }

    }
    //Zakoñczenie pracy aplikacji
    else
    {
        this->endApplication();
        this->window->close();
    }


}

void Game::render()
{
    /*Renderowanie*/
    this->window->clear();

    //Rzeczy do renderowania
    if (!this->states.empty())
        this->states.top()->render();
    
    this->window->display();
}

void Game::run()
{
    /*Uruchomienie gry tak d³ugo jak otwarte jest okno*/
    while (this->window->isOpen())
    {

        this->updateDt();
        this->update();
        this->render();
    }
}
