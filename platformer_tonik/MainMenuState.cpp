#include "stdafx.h"
#include "MainMenuState.h"


void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile(
		"Resources/Images/Backgrounds/szybcior-bg.png"))
	{
		throw "ERROR::MAINMENUSTATE::NIE_UDALO_SIE_ZALADOWAC_TEKSTURY_TLA";
	}

	this->background.setTexture(&this->backgroundTexture);

}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Geomanist-Regular.otf"))
	{
		throw("BLAD::MAINMENUSTATE::NIE ZALADOWANO CZCIONKI");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream source("Config/mainmenustate_keys.ini");

	if (source.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (source >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}

	}

	source.close();
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new gui::Button(200.f, 400.f, 250.f, 75.f,
		&this->font, "New Game", 42,
		sf::Color(0, 0, 0, 255), sf::Color(240, 240, 240, 255), sf::Color(10, 10, 10, 255),
		sf::Color(0, 50, 100, 0), sf::Color(170, 220, 230, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS_STATE"] = new gui::Button(200.f, 550.f, 250.f, 75.f,
		&this->font, "Settings", 42,
		sf::Color(0, 0, 0, 255), sf::Color(240, 240, 240, 255), sf::Color(10, 10, 10, 255),
		sf::Color(0, 50, 100, 0), sf::Color(173, 220, 230, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new gui::Button(200.f, 700.f, 250.f, 75.f,
		&this->font, "Editor", 42,
		sf::Color(0, 0, 0, 255), sf::Color(240, 240, 240, 255), sf::Color(10, 10, 10, 255),
		sf::Color(0, 50, 100, 0), sf::Color(173, 220, 230, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(200.f, 850.f, 250.f, 75.f,
		&this->font, "Quit", 42,
		sf::Color(0, 0, 0, 255), sf::Color(240, 240, 240, 255), sf::Color(10, 10, 10, 255),
		sf::Color(0, 50, 100, 0), sf::Color(173, 220, 230, 0), sf::Color(20, 20, 20, 0));


}


MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}


void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	/*Odœwie¿a wszystkie przyciski w Stejcie i zajmuje siê ich funkcjonalnoœci¹*/
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosWindow);
	}

	//Nowa gra
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}

	//Ustawienia
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}
	//Edytor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	//WyjdŸ z gry
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();

}

void MainMenuState::rednerButtons(sf::RenderTarget& target)
{
	for (auto &i : this->buttons)
	{
		i.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->rednerButtons(*target);
	
	//USUN POZNIEJ!
	//sf::Text mouseText;
	//mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 150);
	//mouseText.setFont(this->font);
	//mouseText.setCharacterSize(12);
	//std::stringstream ss;
	//ss << this->mousePosView.x << " " << this->mousePosView.y;
	//mouseText.setString(ss.str());
	//target->draw(mouseText);
}