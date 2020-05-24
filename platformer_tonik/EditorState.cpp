#include "stdafx.h"
#include "EditorState.h"

void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, 80, 80);
	this->collision = false;
	this->type = TileTypes::DEFAULT;
	this->cameraSpeed = 500.f;
}

void EditorState::initView()
{
	this->view.setSize(sf::Vector2f(1366, 768));
	this->view.setCenter(683.f, 384.f);
}

void EditorState::initBackground()
{

}


void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Geomanist-Regular.otf"))
	{
		throw("BLAD::EDITORSTATE::NIE ZALADOWANO CZCIONKI");
	}
}

void EditorState::initText()
{

	this->cursorText.setFont(this->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y);
}

void EditorState::initKeybinds()
{
	std::ifstream source("Config/editorstate_keys.ini");

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

void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 500.f, "Quit");
	this->pmenu->addButton("LOAD", 325.f, "Load");
	this->pmenu->addButton("SAVE", 225.f, "Save");
}

void EditorState::initButtons()
{

}

void EditorState::initGui()
{
	this->sidebar.setSize(sf::Vector2f(60.f, 768.f));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(-1.f);

	//FIXPOTEM
	this->selectorRect.setSize(sf::Vector2f(80.f, 80.f));
	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(-1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tilemap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(15.f, 15.f, 400.f, 400.f,
		80.f, this->tilemap->getTileSheet(),
		this->font, "TS"
		);


}

void EditorState::initTilemap()
{
	//FIX POTEM
	this->tilemap = new Tilemap(80.f, 50, 40, "Resources/Images/Tiles/texturesheet.png");
}


EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initView();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTilemap();
	this->initGui();
}

EditorState::~EditorState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}

	delete this->pmenu;

	delete this->tilemap;
	
	delete this->textureSelector;
}

//Funkcje
void EditorState::updateInput(const float& dt)
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	//Ruch widokiem kamery
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f, -this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.f, this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-this->cameraSpeed * dt, 0.f );
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(this->cameraSpeed * dt, 0.f);
	}

	//Dodaj obszar do mapy obszarów
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) /*&& this->getKeytime()*/)
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				this->tilemap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type);
			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	}
	//Usuñ obszar z mapy obszarów
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) /*&& this->getKeytime()*/)
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				this->tilemap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
			}
		}
	}

	//W³¹cz kolizjê
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getKeytime())
	{
		if (this->collision)
			this->collision = false;
		else
			this->collision = true;
	}
	//Typ
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INCREASE_TYPE"))) && this->getKeytime())
	{
		//DODAJ GRANICÊ TYPÓW
		this->type++;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DECREASE_TYPE"))) && this->getKeytime())
	{
		if(this->type > 0)
			this->type--;
	}
}

void EditorState::updateButtons()
{
	/*Odœwie¿a wszystkie przyciski w Edytorze i zajmuje siê ich funkcjonalnoœci¹*/
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosWindow);
	}
}

void EditorState::updateGui(const float& dt)
{
	this->textureSelector->update(this->mousePosWindow, dt);
	
	if (!this->textureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		//Fix
		this->selectorRect.setPosition(this->mousePosGrid.x * 80, this->mousePosGrid.y * 80);
	}
	this->cursorText.setPosition(this->mousePosView.x + 85.f, this->mousePosView.y - 100.f);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y <<
		"\n" << this->mousePosGrid.x << " " << this->mousePosGrid.y <<
		"\n" << this->textureRect.left << " " << this->textureRect.top <<
		"\n" << "Collision: "<< this->collision <<
		"\n" << "Type: " << this->type;
	this->cursorText.setString(ss.str());

}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();

	if (this->pmenu->isButtonPressed("LOAD"))
		this->tilemap->loadFromFile("test.szybcior");

	if (this->pmenu->isButtonPressed("SAVE"))
		this->tilemap->saveToFile("test.szybcior");
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Odœwie¿anie bez pauzy
	{
		this->updateGui(dt);
		this->updateButtons();
		this->updateEditorInput(dt);
	}
	else // Odœwie¿anie z pauz¹
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}

	this->updateButtons();

}

void EditorState::rednerButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	if(!this->textureSelector->getActive())
	{
		target.setView(this->view);
		target.draw(this->selectorRect);
	}

	target.setView(this->window->getDefaultView());
	this->textureSelector->render(target);
	target.draw(this->sidebar);

	target.setView(this->view);
	target.draw(this->cursorText);


}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->view);
	this->tilemap->render(*target);
	
	target->setView(this->window->getDefaultView());
	this->rednerButtons(*target);
	this->renderGui(*target);


	if (this->paused) // Renderowanie menu pauzy
	{
		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);
	}
}