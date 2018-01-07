#pragma once

#include <SFML/Graphics.hpp>

class Shape : public sf::ConvexShape
{
public:
	Shape();
	~Shape();

	inline virtual sf::Vector2f getPosition() { return shape->getPosition(); }
	inline virtual sf::Vector2f getOrigin() { return shape->getOrigin(); }
	inline virtual float getRotation() { return shape->getRotation(); }

	virtual void setShape(const std::string &pathToShape, const std::string &pathToTexture, const std::string &nameTexture);
	virtual void setShape(const sf::ConvexShape *shape,const sf::Color &color = sf::Color::Black);
	inline virtual void setPosition(const sf::Vector2f &pos) { shape->setPosition(pos); }
	inline virtual void setRotation(const float &angle) { shape->setRotation(angle); }
	inline virtual void setOrigin(const sf::Vector2f &origin) { shape->setOrigin(origin); }
	inline virtual void setOrigin(const float &x,const float &y) { shape->setOrigin(x,y); }
	inline virtual void setFillColor(const sf::Color &color) { shape->setFillColor(color); }

	inline virtual void move(const sf::Vector2f &offset) { shape->move(offset); }

	inline sf::ConvexShape* getShape() { return shape; }

private:
	sf::ConvexShape *shape;
};