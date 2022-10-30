#pragma once
#include <SFML/Graphics.hpp>

class Blob : private sf::CircleShape
{
public:
	Blob(const double SIZE);
	Blob();
	~Blob();

	void bounce(const double);
	void bounceX();
	void bounceY();

	void setSpeed(const double);
	void setSize(const double);
	void setColor(sf::Color);
	void setPos(sf::Vector2f);
	void setAngle(const double);

	double getAngle();
	sf::Color getColor();
	sf::FloatRect getFloatRect();
	sf::Vector2f getPos();
	double getSize();
	sf::CircleShape getShape();

	bool checkCollision(sf::CircleShape);

	void update();
	void draw(sf::RenderWindow* window);
	void drawDirectionLine(sf::RenderWindow* window);

	bool operator>(Blob& right);
	bool operator<(Blob& right);
	bool operator==(Blob& right);
	Blob& operator+=(Blob& right);
private:
	sf::Vector2f calculateDirection();
	void movePosition();
	void smoothSizeChange(); //Smooth Visuals
	float lerp(float, float, float); //interpolation - Smooth Visuals

	double speed;
	double blobSize;
	double angle; //Heading Direction
};

