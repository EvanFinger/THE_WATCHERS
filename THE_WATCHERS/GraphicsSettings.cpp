#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	this->title = "default";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->verticalSync = false;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();
}

//Functions
void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream file("Config/graphics.ini");

	if (file.is_open())
	{
		file << this->title;
		file << this->resolution.width << " " << resolution.height;
		file << fullscreen;
		file << this->frameRateLimit;
		file << this->verticalSync;
		file << this->contextSettings.antialiasingLevel;
	}

	file.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream file("Config/graphics.ini");

	if (file.is_open())
	{
		std::getline(file, this->title);
		file >> this->resolution.width >> resolution.height;
		file >> fullscreen;
		file >> this->frameRateLimit;
		file >> this->verticalSync;
		file >> this->contextSettings.antialiasingLevel;
	}

	file.close();
}