#include "Application.h"

Application::Application()
{
	settings = std::make_unique<sf::ContextSettings>();
	settings->antialiasingLevel = 8;

	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1440, 900), "Delaunay2020", sf::Style::Default, *settings);
	window->setVerticalSyncEnabled(true);
}

void Application::run()
{
	while (window->isOpen())
	{
		processEvents();
		render();
	}
}

void Application::processEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			window->close();
			break;
		}
		default: { break; }
		}
	}
}

void Application::render()
{
	sf::CircleShape shape(100.f);
	window->clear();
	window->draw(shape);
	window->display();
}
