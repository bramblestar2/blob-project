#pragma once
#include <SFML/Graphics.hpp>
#include "../BlobSim.h"

class Window
{
public:
	Window();
	//Free memory
	virtual ~Window();

	void run();
	void render();
	void update();
	void updateSFMLEvents();
private:
	void initWindow();
	
	sf::Clock dtClock;
	double dt;

	sf::RenderWindow* window;
	sf::Event event;

	BlobSim sim;
	const int blobCount = 100;
};

