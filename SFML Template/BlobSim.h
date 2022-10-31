#pragma once
#include "Blob.h"

class BlobSim
{
public:
	BlobSim();
	~BlobSim(); //Free memory here

	void setSlingEvent(sf::RenderWindow* window); //For fun
	void newSimulation(const int BLOB_COUNT, const sf::Vector2u SPAWN_AREA);

	void updateEvents(const sf::Event);
	void update();
	void draw(sf::RenderWindow* window);
private:
	//smallest to biggest blob
	void changeLoadOrder();
	void swapPtr(Blob&, Blob&);
	void bubbleSort();

	void initVariables();

	sf::Color calculateColor(const float, const sf::Color, const sf::Vector2f); //Smooth Visuals
	float lerp(float, float, float); //Interpolation - Smooth Visuals

	void collisionChecks();
	sf::Vector2f getMinMax(); //Gets the min and max of blob sizes
	void slingShot(); //For fun

	bool loadOrderDebug;
	bool debug;

	int blobsStart;
	int blobCount;
	sf::RenderWindow* window; //For sling event
	Blob* blobs;

	sf::RectangleShape borders[4];
	sf::Vector2u window_size;
};

