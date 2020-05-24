#include "stdafx.h"
#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->quit = false;
	this->paused = false;
	this->keytime = 0.f;
	this->keytimeMax = 10.f;
}

State::~State()
{

}

//Akcesory

const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

//Funkcje

void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::updateMousePositions(sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	
	if(view)
		this->window->setView(*view);

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2u(
		//FIX FIX FIX
		static_cast<unsigned> (this->mousePosView.x) / 80,
		static_cast<unsigned> (this->mousePosView.y) / 80
	);

	this->window->setView(this->window->getDefaultView());
}

void State::updateKeytime(const float& dt)
{
	if(this->keytime < this->keytimeMax)
		this->keytime += 40.f * dt;
}
