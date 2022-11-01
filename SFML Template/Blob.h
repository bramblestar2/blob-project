#pragma once
#include <SFML/Graphics.hpp>
#include "ShaderTest.h"

class Blob : private sf::CircleShape
{
public:
	Blob(const double SIZE);
	Blob();
	~Blob();

	double bounce();
	void bounceX();
	void bounceY();

	void setSpeed(const double);
	void setSize(const double);
	void setColor(sf::Color);
	void setPos(sf::Vector2f);
	void setAngle(const double);

	double getAngle();
	double getSize();
	double getSpeed();
	sf::Color getColor();
	sf::FloatRect getFloatRect();
	sf::Vector2f getPos();
	sf::CircleShape getShape();

	double calculateReflection(const double);
	double calculateAngle(sf::Vector2f);
	bool checkCollision(sf::CircleShape);
	sf::Vector2f calculateDirection(const double);

	void update();
	void draw(sf::RenderWindow* window);
	void drawDirectionLine(sf::RenderWindow* window);

	bool operator>(Blob& right);
	bool operator<(Blob& right);
	bool operator==(Blob& right);
	Blob& operator+=(Blob& right);
private:
	void movePosition();
	void smoothSizeChange(); //Smooth Visuals
	float lerp(float, float, float); //interpolation - Smooth Visuals

	double speed;
	double blobSize;
	double angle; //Heading Direction
};

