#include "Window.h"
#include <iostream>

Window::Window()
{
	initWindow();

	blobCount = 100;
	paused = false;

	sim = BlobSim();
	sim.newSimulation(blobCount, sf::Vector2u(window->getSize().x - 60,
									   window->getSize().y - 60));
	sim.setSlingEvent(window);

	//shader.loadBoth("Shaders/Blur/Basic.vertex", "Shaders/Blur/Basic.frag");
}

Window::~Window()
{
	delete window;
}

void Window::run()
{
	while (window->isOpen())
	{
		if (window->hasFocus() && !paused)
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
	//shader.drawShader(window);
	

	window->display();
}

void Window::update()
{
	sim.update();

	std::cout << blobCount << "           \r";
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
			if (event.key.code == sf::Keyboard::N)
				sim.newSimulation(blobCount, sf::Vector2u(window->getSize().x - 60,
												   window->getSize().y - 60));

			if (event.key.code == sf::Keyboard::Right)
				blobCount++;
			else if (event.key.code == sf::Keyboard::Left)
				blobCount--;

			if (event.key.code == sf::Keyboard::Space)
				paused = !paused ? true : false;
		}

		sim.updateEvents(event);
	}
}

void Window::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(600, 600), "Blobs", sf::Style::Default);
	window->setFramerateLimit(30);
}
