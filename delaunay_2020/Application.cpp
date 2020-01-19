#include <iostream>

#include "Application.h"
#include "DelaunayMachine.h"

#include <Windows.h>

Application::Application() : event(std::make_unique<sf::Event>())
{
	settings = std::make_unique<sf::ContextSettings>();
	settings->antialiasingLevel = 4;

	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1440, 900), "Delaunay2020", sf::Style::Default, *settings);
	window->setVerticalSyncEnabled(true);

	vertexShape->setFillColor(sf::Color::Green);
}

void Application::preparePointset()
{
	pointset = std::make_shared<std::vector<Vector2>>();
	for (int i = 0; i < pointCount; ++i)
	{
		double quake = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
		Vector2 v(rand() % ((int)window->getSize().x - 120) + 60 + quake,
			      rand() % ((int)window->getSize().y - 120) + 60 + quake);
		pointset->push_back(v);
	}
}

void Application::performTriangulationAndMeasurements()
{
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	DelaunayMachine delaunayMachine(pointset);
	delaunayMachine.delaunay_incremental_AFL();

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	std::cout << "Elapsed us: " << ElapsedMicroseconds.QuadPart << std::endl;
	std::cout << "Elapsed ms: " << ElapsedMicroseconds.QuadPart / 1000 << std::endl;
}

void Application::run()
{
	preparePointset();
	performTriangulationAndMeasurements();

	while (window->isOpen())
	{
		processEvents();
		render();
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

void Application::render()
{
	window->clear();	
	for (int i = 0; i < pointCount; ++i)
	{
		vertexShape->setPosition(sf::Vector2f((*pointset)[i].x, (*pointset)[i].y));
		window->draw(*vertexShape);
	}	
	window->display();
}
