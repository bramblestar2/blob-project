#include "Blob.h"
#include <math.h>
#include <iostream>

Blob::Blob(const double SIZE)
{
    angle = 0;
    setSize(SIZE);
    speed = 0;
    setFillColor(sf::Color::White);

}

Blob::Blob()
{
    angle = 0;
    setSize(0);
    speed = 0;
}

Blob::~Blob()
{
}

double Blob::bounce()
{
    sf::Vector2f dir = calculateDirection(angle);
    double newAngle = angle - (3.14 / 2);
    sf::Vector2f pointTwo = sf::Vector2f(getPos().x + (dir.x * blobSize * 2), getPos().y + (dir.y * blobSize * 2));
    return 0;
}

void Blob::bounceX()
{
    angle = fmod((angle + (3.14/2)), (2 * 3.14));
}

void Blob::bounceY()
{
    angle = -angle;
}

double Blob::calculateReflection(const double a)
{
    return 0.0;
}

bool Blob::checkCollision(sf::CircleShape a)
{
    bool colliding = false;

    double distance = 0;

    {
        double xDistance = pow(a.getPosition().x - getPosition().x, 2);
        double yDistance = pow(a.getPosition().y - getPosition().y, 2);
        distance = sqrt(xDistance + yDistance);
    }

    //Is colliding if distance is less than a + b
    if (distance < (getRadius() + a.getRadius())/1.2)
    {
        colliding = true;
    }

    return colliding;
}

sf::FloatRect Blob::getFloatRect()
{
    return getGlobalBounds();
}

sf::Vector2f Blob::getPos()
{
    return getPosition();
}

double Blob::getSize()
{
    return blobSize;
}

double Blob::getSpeed()
{
    return speed;
}

sf::CircleShape Blob::getShape()
{
    return *this;
}

void Blob::update()
{
    if (blobSize > 1)
    {
        movePosition();
    }
    smoothSizeChange();
}

void Blob::draw(sf::RenderWindow* window)
{
    window->draw(*this);
}

void Blob::drawDirectionLine(sf::RenderWindow* window)
{
    sf::VertexArray line(sf::Lines, 2);
    sf::Vector2f dir = calculateDirection(angle);

    line[0].position = getPosition();
    line[1].position = sf::Vector2f(getPos().x + (dir.x * blobSize * 2), getPos().y + (dir.y * blobSize * 2));
    
    line[0].color = sf::Color(0,0,255);
    line[1].color = sf::Color(0,0,255);

    window->draw(line);
}


sf::Vector2f Blob::calculateDirection(const double angle)
{
    return sf::Vector2f(cos(angle), sin(angle));
}

double Blob::calculateAngle(sf::Vector2f dir)
{
    sf::Vector2f pointOne = getPos();
    sf::Vector2f pointTwo = sf::Vector2f(getPos().x + (dir.x * blobSize * 2), getPos().y + (dir.y * blobSize * 2));

    return atan2(pointTwo.y - pointOne.y, pointTwo.x - pointOne.x);
}

void Blob::movePosition()
{
    sf::Vector2f dir = calculateDirection(angle);
    move((dir.x * speed) / (blobSize / 20), (dir.y * speed) / (blobSize / 20));
}

void Blob::smoothSizeChange()
{
    setRadius(lerp(getRadius(), blobSize, 0.3f));
    setOrigin(getRadius(), getRadius());
}

float Blob::lerp(float a, float b, float t)
{
    return a + t * (b - a);
}


void Blob::setSpeed(const double a)
{
    speed = a;
}

void Blob::setSize(const double a)
{
    blobSize = a;
}

double Blob::getAngle()
{
    return angle;
}

void Blob::setColor(sf::Color color)
{
    setFillColor(color);
}

void Blob::setPos(sf::Vector2f a)
{
    setPosition(a);
}

void Blob::setAngle(const double a)
{
    angle = a;
}

sf::Color Blob::getColor()
{
    return getFillColor();
}

 //////////////////////////////////////////////////////////////////////////////////////////////////////
//   ________  ________  _______   ________  ________  _________  ________  ________  ________        //
//  |\   __  \|\   __  \|\  ___ \ |\   __  \|\   __  \|\___   ___\\   __  \|\   __  \|\   ____\       //
//  \ \  \|\  \ \  \|\  \ \   __/|\ \  \|\  \ \  \|\  \|___ \  \_\ \  \|\  \ \  \|\  \ \  \___|_      //
//   \ \  \\\  \ \   ____\ \  \_|/_\ \   _  _\ \   __  \   \ \  \ \ \  \\\  \ \   _  _\ \_____  \     //
//    \ \  \\\  \ \  \___|\ \  \_|\ \ \  \\  \\ \  \ \  \   \ \  \ \ \  \\\  \ \  \\  \\|____|\  \    //
//     \ \_______\ \__\    \ \_______\ \__\\ _\\ \__\ \__\   \ \__\ \ \_______\ \__\\ _\ ____\_\  \   //
//      \|_______|\|__|     \|_______|\|__|\|__|\|__|\|__|    \|__|  \|_______|\|__|\|__|\_________\  //
//                                                                                      \|_________|  //
 //////////////////////////////////////////////////////////////////////////////////////////////////////

bool Blob::operator>(Blob& right)
{
    return blobSize > right.blobSize;
}

bool Blob::operator<(Blob& right)
{
    return blobSize < right.blobSize;
}

bool Blob::operator==(Blob& right)
{
    return blobSize == right.blobSize;
}

Blob& Blob::operator+=(Blob& right)
{
    blobSize += right.blobSize/3;
    right.blobSize = 0;
    return *this;
}
