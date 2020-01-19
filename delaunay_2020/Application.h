#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Vector2.h"

using namespace d20;

class Application
{
public: 
	Application();

	void run();
	void processEvents();
	void render();
	void preparePointset();
	void performTriangulationAndMeasurements();

private:
	std::unique_ptr<sf::ContextSettings> settings;
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<sf::Event> event;
	std::unique_ptr<sf::CircleShape> vertexShape{ std::make_unique<sf::CircleShape>(0.3f, 3) };
	std::shared_ptr<std::vector<Vector2>> pointset;
};
