#pragma once

#include <SFML/Graphics.hpp>
#include "carType.hpp"
#include "../../Framework/Shapes.hpp"
#include <unordered_map>

class Door
{
public:
	Door(const carType::Type &type);
	~Door();

	enum class Side
	{
		front_left,
		front_right,
		back_left,
		back_right
	}; 

	sf::ConvexShape* getDoor(const size_t &index) { return doors[index].getShape(); }
	sf::ConvexShape* getCenter(const size_t &index) { return center[index].getShape(); }

	void setPosition(const sf::ConvexShape *car, const carType::Type &type);
	void moveOne(const size_t &index, const sf::Vector2f &offset);
	void move(const sf::Vector2f &offset);

	void rotate(const double &angle);

	void openDoor(sf::ConvexShape *door, float *angle, const size_t &index);
	void closeDoor(sf::ConvexShape *door, float *angle, const size_t &index);

	void drawDoors();
	void drawCenter();

private:

	carType::Type *type;

	Shape *doors;
	Shape *center;

	float *angleOpen;
	float *angleClose;

	void setPath(std::string pathToShape, std::string pathToTexture, const std::string &string, const std::string &nameTexture, const int &count);
	std::pair<sf::Vector2f,size_t> setHinge(const size_t &index);
	void rotate(sf::ConvexShape *door, const float *angle,const sf::Vector2f &hinge,const size_t &originIndex);
};