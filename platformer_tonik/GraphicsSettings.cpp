#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	this->title = "STANDARDOWY";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->verticalSync = false;
	this->frameRateLimit = 144;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();
}

void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofstream(path);

	if (ofstream.is_open())
	{
		ofstream << this->title;
		ofstream << this->resolution.width << " " << this->resolution.height;
		ofstream << this->fullscreen;
		ofstream << this->frameRateLimit;
		ofstream << this->verticalSync;
		ofstream << this->contextSettings.antialiasingLevel;
	}

	ofstream.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{

	std::ifstream ifstream(path);

	if (ifstream.is_open())
	{
		std::getline(ifstream, title);
		ifstream >> this->resolution.width >> this->resolution.height;
		ifstream >> this->fullscreen;
		ifstream >> this->frameRateLimit;
		ifstream >> this->verticalSync;
		ifstream >> this->contextSettings.antialiasingLevel;
	}

	ifstream.close();
}