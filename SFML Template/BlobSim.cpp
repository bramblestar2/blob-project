#include "BlobSim.h"
#include <time.h>
#include <iostream>
#include <string>

BlobSim::BlobSim()
{
	srand(time(NULL));
	initVariables();

	font.loadFromFile("Fonts/font1.ttf");

	loadOrderDebug = false;
	debug = false;
	blobsStart = -1;

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
		*(blobs + i) = Blob(rand() % 10 + 11);
		(blobs + i)->setSpeed(5);
		(blobs + i)->setPos(sf::Vector2f(rand() % SPAWN_AREA.x + 30,
										 rand() % SPAWN_AREA.x + 30));
		(blobs + i)->setAngle((double)(rand() % 360)/100.);
	}
}

void BlobSim::updateEvents(const sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::H)
		{
			debug = debug ? false : true;
		}
		if (event.key.code == sf::Keyboard::G)
			loadOrderDebug = loadOrderDebug ? false : true;
	}
}

void BlobSim::update()
{
	if (blobCount != NULL && blobs != nullptr)
	{
		blobsStart = -1;
		for (int i = 0; i < blobCount; i++)
			if (blobs[i].getSize() > 1)
				if (blobsStart == -1)
					blobsStart = i;

		if (window != nullptr)
			slingShot();

		changeLoadOrder();

		collisionChecks();
		
		for (int i = 0; i < blobCount; i++)
		{
			blobs[i].update();
			blobs[i].setColor(calculateColor(blobs[i].getSize(), 
							  blobs[i].getColor(), getMinMax()));
		}
	}
}

void BlobSim::draw(sf::RenderWindow* window)
{
	if (blobCount != NULL && blobs != nullptr)
	{
		for (int i = blobsStart; i < blobCount; i++)
		{
			window->draw(blobs[i].getShape());
			//blobs[i].draw(window);
			if (debug)
				blobs[i].drawDirectionLine(window);
		}
	}
	for (int i = 0; i < 4; i++)
		window->draw(borders[i]);


	if (loadOrderDebug && blobCount != NULL && blobs != nullptr)
	{
		debugging(window);
	}
}

void BlobSim::debugging(sf::RenderWindow* window)
{
	sf::VertexArray connections(sf::LinesStrip, 0);

	for (int i = blobsStart; i < blobCount; i++)
	{
		if (blobs[i].getShape().getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
		{
			for (int k = blobsStart; k <= blobCount; k++)
			{
				if (i != k)
				{
					connections.append(sf::Vertex());
					connections.append(sf::Vertex());
					connections[connections.getVertexCount() - 2].position = blobs[i].getPos();
					connections[connections.getVertexCount() - 1].position = blobs[k].getPos();
					connections[connections.getVertexCount() - 2].color = sf::Color(255, 255, 255, 50);
					connections[connections.getVertexCount() - 1].color = sf::Color(255, 255, 255, 50);

					if (blobs[i].getSize() < blobs[k].getSize() + 2 &&
						blobs[i].getSize() > blobs[k].getSize() - 2)
					{
						connections[connections.getVertexCount() - 2].color = sf::Color(255, 0, 0);
						connections[connections.getVertexCount() - 1].color = sf::Color(255, 0, 0);
					}

					//0 - Position
					//1 - Blop size
					//2 - Angle / Speed
					//3 - Color
					sf::Text debugText[4];

					debugText[0].setString(std::to_string(blobs[i].getPos().x) + " (X) - " + 
						std::to_string(blobs[i].getPos().y) + " (Y)");

					debugText[1].setString(std::to_string(blobs[i].getSize()) + " (Size)");

					debugText[2].setString(std::to_string(blobs[i].getAngle()) + " (Angle) / " + 
						std::to_string(blobs[i].getSpeed()) + " (Speed)");

					debugText[3].setString(std::to_string(blobs[i].getColor().r) + "(R) / " +
						std::to_string(blobs[i].getColor().g) + "(G) / " + std::to_string(blobs[i].getColor().b) + " (B)");

					for (int k = 0; k < 4; k++)
					{
						debugText[k].setCharacterSize(20);
						debugText[k].setFont(font);
						debugText[k].setPosition(sf::Vector2f(0, debugText[k].getGlobalBounds().height * (k*2)));

						window->draw(debugText[k]);
					}
				}
			}
		}

		//Shows order on the blobs
		sf::Text text;
		text.setFont(font);
		text.setPosition(blobs[i].getPos());
		text.setString(std::to_string(blobCount - i));
		text.setCharacterSize(blobs[i].getSize() / 2);
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);

		window->draw(text);

	}
	window->draw(connections);
}

void BlobSim::changeLoadOrder()
{
	bubbleSort();
}

void BlobSim::swapPtr(Blob& a, Blob& b)
{
	Blob temp = a;
	a = b;
	b = temp;
}

void BlobSim::bubbleSort()
{
	for (int i = 0; i < blobCount - 1; i++)
		for (int k = 0; k < blobCount - i - 1; k++)
		{
			if (blobs[k].getSize() > blobs[k+1].getSize())
				swapPtr(blobs[k], blobs[k+1]);
		}
}

void BlobSim::initVariables()
{
	blobCount = NULL;
	blobs = nullptr;
	window = nullptr;
}

sf::Color BlobSim::calculateColor(const float BLOB_SIZE, const sf::Color CURRENT_COLOR, const sf::Vector2f MAXMIN)
{
	float num = MAXMIN.x - (MAXMIN.y - 1);
	float percentage = ((BLOB_SIZE - (MAXMIN.y - 1)) / num) * 100;

	float t = 0.1f;

	return sf::Color(lerp(CURRENT_COLOR.r, (percentage * 230) / 100, t),
		150, lerp(CURRENT_COLOR.g, (percentage * 150) / 100, t));
}

float BlobSim::lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

void BlobSim::collisionChecks()
{
	for (int i = blobsStart; i < blobCount; i++)
	{
		if (blobs[i].getSize() > 5.f)
		{
			for (int k = blobsStart; k < blobCount; k++)
			{
				if (k != i)
					if (blobs[i].checkCollision(blobs[k].getShape()))
					{
						if (blobs[i].getSize() > blobs[k].getSize() + 2)
							blobs[i] += blobs[k];
						else if (blobs[i].getSize() < blobs[k].getSize() - 2)
							blobs[k] += blobs[i];
						else
						{
							sf::Vector2f posOne = blobs[i].getPos();
							sf::Vector2f posTwo = blobs[k].getPos();

							blobs[i].setAngle(blobs[k].calculateAngle(-(posTwo - posOne)));
							blobs[k].setAngle(blobs[i].calculateAngle((posTwo - posOne)));
							blobs[i].setSpeed(blobs[i].getSpeed() + (blobs[i].getSpeed() * 0.2));
							blobs[k].setSpeed(blobs[k].getSpeed() + (blobs[k].getSpeed() * 0.2));
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
					{
						sf::Vector2f posOne = blobs[i].getPos();
						sf::Vector2f posTwo;

						if (k == 0) //Left border
						{
							posTwo = sf::Vector2f(borders[0].getPosition().x + (blobs[i].getSize() * 2), posOne.y);
							blobs[i].setPos(sf::Vector2f((borders[0].getPosition().x + borders[0].getLocalBounds().width) 
														 + blobs[i].getSize(), blobs[i].getPos().y));
						}
						else //Right border
						{
							posTwo = sf::Vector2f(borders[1].getPosition().x, posOne.y);
							blobs[i].setPos(sf::Vector2f(borders[1].getPosition().x - blobs[i].getSize(), blobs[i].getPos().y));
						}

						double perpAngle = blobs[i].calculateAngle(posOne - posTwo);

						blobs[i].setAngle(perpAngle-blobs[i].getAngle());
					}
					//Top and bottom border
					if (k >= 2 && k <= 3)
					{
						blobs[i].bounceY();

						if (k == 2) //Top
							blobs[i].setPos(sf::Vector2f(blobs[i].getPos().x, 
								(borders[k].getPosition().y + borders[k].getLocalBounds().height) + blobs[i].getSize()));
						else //Bottom
							blobs[i].setPos(sf::Vector2f(blobs[i].getPos().x,
								borders[k].getPosition().y - blobs[i].getSize()));

					}
				}
			}
		}
	}
}

//returns v2f(MAX, MIN)
//returns -1 for both if theres no blobs
sf::Vector2f BlobSim::getMinMax()
{
	double max = -1, min = -1;
	bool start = false;
	for (int i = 0; i < blobCount; i++)
	{
		if (blobs[i].getSize() > 1)
		{
			if (!start)
			{
				max = blobs[i].getSize();
				min = blobs[i].getSize();
				start = true;
			}
			else
			{
				if (blobs[i].getSize() > max)
					max = blobs[i].getSize();
				else if (blobs[i].getSize() < min)
					min = blobs[i].getSize();
			}
		}
	}

	return sf::Vector2f(max, min);
}

void BlobSim::slingShot()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (int i = blobsStart; i < blobCount; i++)
		{
			double xDistance = pow(blobs[i].getPos().x - sf::Mouse::getPosition(*window).x, 2);
			double yDistance = pow(blobs[i].getPos().y - sf::Mouse::getPosition(*window).y, 2);
			double distance = sqrt(xDistance + yDistance);

			sf::Vector2i pointOne = sf::Mouse::getPosition(*window);
			if (distance < blobs[i].getSize())
			{
				sf::Vector2i pointTwo = sf::Mouse::getPosition(*window);
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					pointTwo = sf::Mouse::getPosition(*window);
				}

				blobs[i].setAngle(atan2(pointOne.y - pointTwo.y, pointOne.x - pointTwo.x));
			}
		}
	}
}
