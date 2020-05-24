#pragma once

class GraphicsSettings
{
public:
	GraphicsSettings();

	//Zmienne
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;


	//Funkcje
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};
