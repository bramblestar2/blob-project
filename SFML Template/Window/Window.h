#pragma once
#include <SFML/Graphics.hpp>
#include "../BlobSim.h"
#include "../ShaderTest.h"

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

	bool paused;

	sf::RenderWindow* window;
	sf::Event event;

	BlobSim sim;
	int blobCount;

	ShaderTest shader;
};

