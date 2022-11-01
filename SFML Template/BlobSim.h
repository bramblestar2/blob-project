#pragma once
#include "Blob.h"
#include "ShaderTest.h"

class BlobSim
{
public:
	BlobSim();
	~BlobSim(); //Free memory here

	void setSlingEvent(sf::RenderWindow*); //For fun
	void slingShot(); //For fun
	void newSimulation(const int, const sf::Vector2u);

	void updateEvents(const sf::Event);
	void update();
	void draw(sf::RenderWindow*);
private:
	//smallest to biggest blob
	void changeLoadOrder();
	void swapPtr(Blob&, Blob&);
	void bubbleSort();
	void debugging(sf::RenderWindow*);

	void initVariables();

	sf::Color calculateColor(const float, const sf::Color, const sf::Vector2f); //Smooth Visuals
	float lerp(float, float, float); //Interpolation - Smooth Visuals

	void collisionChecks();
	sf::Vector2f getMinMax(); //Gets the min and max of blob sizes

	bool loadOrderDebug;
	bool debug;

	int blobsStart;
	int blobCount;
	sf::RenderWindow* window; //For sling event
	Blob* blobs;

	sf::RectangleShape borders[4];
	sf::Vector2u window_size;

	sf::Font font;
};

