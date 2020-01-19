#include <iostream>

#include "Application.h"
#include "DelaunayMachine.h"

Application::Application() : event(std::make_unique<sf::Event>())
{
	settings = std::make_unique<sf::ContextSettings>();
	settings->antialiasingLevel = 8;

	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1440, 900), "Delaunay2020", sf::Style::Default, *settings);
	window->setVerticalSyncEnabled(true);
}

void Application::run()
{
	std::vector<Vector2> pointvec;
	for (int i = 0; i < pointCount; ++i)
	{
		double quake = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
		Vector2 v(rand() % ((int)window->getSize().x - 120) + 60 + quake,
			      rand() % ((int)window->getSize().y - 120) + 60 + quake);
		pointvec.push_back(v);
	}

	//DelaunayMachine delaunayMachine(pointset);
	//delaunayMachine.delaunay_incremental_AFL();

	while (window->isOpen())
	{
		processEvents();
		render(pointvec);
	}
}

void Application::processEvents()
{	
	while (window->pollEvent(*event))
	{
		switch (event->type)
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

void Application::render(std::vector<Vector2>& pointvec)
{
	window->clear();
	circle->setFillColor(sf::Color::Green);
	for (int i = 0; i < pointCount; ++i)
	{
		circle->setPosition(sf::Vector2f(pointvec[i].x, pointvec[i].y));
		window->draw(*circle);
	}	
	window->display();
}
