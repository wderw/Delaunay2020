#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Vector2.h"

class Application
{
public: 
	Application();

	void run();
	void processEvents();
	void render(std::vector<Vector2>&);

private:
	std::unique_ptr<sf::ContextSettings> settings;
	std::unique_ptr<sf::RenderWindow> window;
};
