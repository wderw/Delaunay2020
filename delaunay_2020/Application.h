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
	std::unique_ptr<sf::Event> event;
	std::unique_ptr<sf::CircleShape> circle{ std::make_unique<sf::CircleShape>(4.0f, 3) };
};
