#include "Window.h"

Window::Window()
{
	initWindow();
}

Window::~Window()
{
	delete window;
}

void Window::run()
{
	while (window->isOpen())
	{
		update();
		updateDt();
		updateSFMLEvents();
		render();
	}
}

void Window::render()
{
	window->clear();

	window->display();
}

void Window::update()
{
}

void Window::updateDt()
{
	dt = dtClock.restart().asSeconds();
}

void Window::updateSFMLEvents()
{
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed ||
			event.key.code == sf::Keyboard::Escape)
			window->close();
	}
}

void Window::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(100, 100), "TITLE", sf::Style::Default);
}
