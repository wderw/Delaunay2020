#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Application
{
public: 
	Application();

	void run();
	void processEvents();
	void render();

private:
	std::unique_ptr<sf::ContextSettings> settings;
	std::unique_ptr<sf::RenderWindow> window;
};
