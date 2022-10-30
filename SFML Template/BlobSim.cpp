#include "BlobSim.h"
#include <time.h>
#include <iostream>

BlobSim::BlobSim()
{
	srand(time(NULL));
	initVariables();

	window_size = sf::Vector2u(600, 600);
	//Left and right Borders
	borders[0].setFillColor(sf::Color::Blue);
	borders[0].setSize(sf::Vector2f(10, window_size.y));

	borders[1].setFillColor(sf::Color::Blue);
	borders[1].setSize(sf::Vector2f(10, window_size.y));
	borders[1].setPosition(window_size.x - borders[1].getSize().x, 0);

	//Top and bottom Borders
	borders[2].setFillColor(sf::Color::Blue);
	borders[2].setSize(sf::Vector2f(window_size.x, 10));

	borders[3].setFillColor(sf::Color::Blue);
	borders[3].setSize(sf::Vector2f(window_size.x, 10));
	borders[3].setPosition(0, window_size.y - borders[3].getSize().y);
}

BlobSim::~BlobSim()
{
	delete[] blobs;
}

void BlobSim::setSlingEvent(sf::RenderWindow* window)
{
	this->window = window;
}

void BlobSim::newSimulation(const int BLOB_COUNT, const sf::Vector2u SPAWN_AREA)
{
	if (blobs != nullptr)
		delete[] blobs;

	blobCount = BLOB_COUNT;

	blobs = new Blob[BLOB_COUNT];

	for (int i = 0; i < BLOB_COUNT; i++)
	{
		*(blobs + i) = Blob(rand() % 30 + 11);
		(blobs + i)->setSpeed(5);
		(blobs + i)->setPos(sf::Vector2f(rand() % SPAWN_AREA.x + 30,
										 rand() % SPAWN_AREA.x + 30));
		(blobs + i)->setAngle(rand() % 360);
	}
}

void BlobSim::update()
{
	if (blobCount != NULL && blobs != nullptr)
	{
		collisionChecks();
		for (int i = 0; i < blobCount; i++)
		{
			blobs[i].update();
		}
	}
}

void BlobSim::draw(sf::RenderWindow* window)
{
	
	if (blobCount != NULL && blobs != nullptr)
		for (int i = 0; i < blobCount; i++)
		{
			blobs[i].draw(window);
			if (debug)
				blobs[i].drawDirectionLine(window);
		}

	for (int i = 0; i < 4; i++)
		window->draw(borders[i]);
}

void BlobSim::initVariables()
{
	blobCount = NULL;
	blobs = nullptr;
	window = nullptr;
}

sf::Color BlobSim::calculateColor(const float BLOB_SIZE, const sf::Color CURRENT_COLOR)
{
	return sf::Color();
}

float BlobSim::lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

void BlobSim::collisionChecks()
{
	for (int i = 0; i < blobCount; i++)
	{
		if (blobs[i].getSize() > 5.f)
		{
			for (int k = 0; k < blobCount; k++)
			{
				if (k != i)
				{
					if (blobs[i].checkCollision(blobs[k].getShape()))
					{
						if (blobs[i] > blobs[k])
							blobs[i] += blobs[k];
						else if (blobs[i] < blobs[k])
							blobs[k] += blobs[i];
						else
						{
							//Bounce off ball
							//Temp solution
							blobs[i].setAngle(blobs[i].getAngle() + 180 % 360);
							blobs[k].setAngle(blobs[k].getAngle() + 180 % 360);
						}
					}
				}
			}

			//Borders
			for (int k = 0; k < 4; k++)
			{
				if (blobs[i].getFloatRect().intersects(borders[k].getGlobalBounds()))
				{
					//Left and right border
					if (k >= 0 && k <= 1)
						blobs[i].setAngle(rand() + 90 % 360);
					//Top and bottom border
					if (k >= 2 && k <= 3)
						blobs[i].set_speed(blobs[i].get_speed().x, blobs[i].get_speed().y * -1);

					//Left border
					if (k == 0)
					{
						blobs[i].set_position(
							(borders[0].getPosition().x + borders[0].getGlobalBounds().width) +
							(blobs[i].getFloatRect().width / 4),
							blobs[i].get_position().y);
					}
					//Right border
					else if (k == 1)
					{
						blobs[i].set_position(
							(borders[1].getPosition().x) -
							(blobs[i].getFloatRect().width / 1.3),
							blobs[i].get_position().y);
					}

					//Top border
					if (k == 2)
					{
						blobs[i].set_position(blobs[i].get_position().x,
							(borders[2].getPosition().y + borders[2].getGlobalBounds().height) +
							(blobs[i].getFloatRect().height / 4));
					}
					//Bottom border
					else if (k == 3)
					{
						blobs[i].set_position(blobs[i].get_position().x,
							(borders[3].getPosition().y) -
							(blobs[i].getFloatRect().height / 1.3));
					}
				}
			}
		}
	}
}

sf::Vector2f BlobSim::getMinMax()
{
	return sf::Vector2f();
}

void BlobSim::slingShot()
{
}
