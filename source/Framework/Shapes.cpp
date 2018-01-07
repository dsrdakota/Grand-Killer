#include "Shapes.hpp"

#include "../Manager/Texture.hpp"
#include <fstream>

Shape::Shape()
{
	shape = new sf::ConvexShape;
}

Shape::~Shape()
{
	delete shape;
}

void Shape::setShape(const std::string & pathToShape, const std::string & pathToTexture, const std::string &nameTexture)
{
	std::ifstream file(pathToShape, std::ios::binary);

	char* temp = new char[sizeof(unsigned)];
	file.read(temp, sizeof(unsigned));
	unsigned *countOfShapePoint = (unsigned*)(temp);

	shape->setPointCount(*countOfShapePoint);

	for (unsigned i = 0;i < *countOfShapePoint;++i)
	{
		sf::Vector2f pos;
		temp = new char[sizeof(unsigned)];
		file.read(temp, sizeof(unsigned));
		unsigned *x = (unsigned*)temp;
		pos.x = (float)*x;

		temp = new char[sizeof(unsigned)];
		file.read(temp, sizeof(unsigned));
		unsigned *y = (unsigned*)temp;
		pos.y = (float)*y;

		shape->setPoint(i, pos);
	}
	const sf::Texture *buf = textureManager::load(nameTexture, pathToTexture);
	shape->setTexture(buf);

	file.clear();
	file.close();
}

void Shape::setShape(const sf::ConvexShape * shape, const sf::Color &color)
{
	this->shape->setPointCount(shape->getPointCount());

	for (size_t i = 0;i < shape->getPointCount();++i)
		this->shape->setPoint(i, shape->getPoint(i));
	this->shape->setFillColor(color);
}
