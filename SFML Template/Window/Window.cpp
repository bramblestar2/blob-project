#include "Window.h"

Window::Window()
{
	initWindow();

	sim = BlobSim();
	sim.newSimulation(blobCount, sf::Vector2u(window->getSize().x - 60,
									   window->getSize().y - 60));
	sim.setSlingEvent(window);
}

Window::~Window()
{
	delete window;
}

void Window::run()
{
	while (window->isOpen())
	{
		if (window->hasFocus())
		{
			update();
		}
			updateSFMLEvents();
			render();
	}
}

void Window::render()
{
	window->clear();

	sim.draw(window);

	window->display();
}

void Window::update()
{
	sim.update();
}

void Window::updateSFMLEvents()
{
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed ||
			event.key.code == sf::Keyboard::Escape)
			window->close();
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
				sim.newSimulation(blobCount, sf::Vector2u(window->getSize().x - 60,
												   window->getSize().y - 60));
		}

		sim.updateEvents(event);
	}
}

void Window::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(600, 600), "TITLE", sf::Style::Default);
	window->setFramerateLimit(30);
}
