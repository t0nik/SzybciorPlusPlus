#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
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
		throw "ERROR::SETTINGSSTATE::NIE_UDALO_SIE_ZALADOWAC_TEKSTURY_TLA";
	}

	this->background.setTexture(&this->backgroundTexture);

}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Geomanist-Regular.otf"))
	{
		throw("BLAD::SETTINGSTATE::NIE ZALADOWANO CZCIONKI");
	}
}

void SettingsState::initKeybinds()
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

void SettingsState::initGui()
{
	this->buttons["BACK"] = new gui::Button(1100.f, 600.f, 250.f, 75.f,
		&this->font, "Back", 41,
		sf::Color(0, 0, 0, 255), sf::Color(240, 240, 240, 255), sf::Color(10, 10, 10, 255),
		sf::Color(0, 50, 100, 0), sf::Color(173, 220, 230, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(900.f, 600.f, 250.f, 75.f,
		&this->font, "Apply", 42,
		sf::Color(0, 0, 0, 255), sf::Color(240, 240, 240, 255), sf::Color(10, 10, 10, 255),
		sf::Color(0, 50, 100, 0), sf::Color(173, 220, 230, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
	}
	this->dropDownLists["RESOLUTION"] =  new gui::DropDownList(350, 300, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(155.f, 300.f));
	this->optionsText.setCharacterSize(35);
	this->optionsText.setFillColor(sf::Color(0, 0, 0, 255));
	
	
	this->optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n ");
}

SettingsState::SettingsState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states), gfxSettings(gfxSettings)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}

SettingsState::~SettingsState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}

	auto j = this->dropDownLists.begin();
	for (j = this->dropDownLists.begin(); j != this->dropDownLists.end(); ++j)
	{
		delete j->second;
	}

}

//Akcesory

//Funkcje
void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGui(const float& dt)
{
	/*Odœwie¿a wszystkie elementy gui i zajmuje siê ich funkcjonalnoœci¹*/
	//Przyciski
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosWindow);
	}

	//Funkcjonalnoœæ przycisków
	//WyjdŸ z gry
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	if (this->buttons["APPLY"]->isPressed())
	{
		//TEST USUÑ PÓNIEJ
		this->gfxSettings.resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];

		this->window->create(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Default);
	}

	//Dropdown listy
	for (auto& j : this->dropDownLists)
	{
		j.second->update(this->mousePosWindow, dt);
	}

	//Funkcjonalnoœæ dropdown list
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);

}

void SettingsState::rednerGui(sf::RenderTarget& target)
{
	//Przyciski
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	//Dropdown listy
	for (auto& j : this->dropDownLists)
	{
		j.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->rednerGui(*target);

	target->draw(this->optionsText);

	//USUN POZNIEJ!
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 150);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}
