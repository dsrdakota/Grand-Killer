#include "DoorTrailer.hpp"
#include "../../../../../../Manager/Texture.hpp"

DoorTrailer::DoorTrailer()
{
	center = new sf::Sprite(*textureManager::load("CenterBL", "data/Trailer/Part3/Textures/centerBackL.png"));

	MAX_DOOR_OPEN_ANGLE = new const double (0.14);

	angleOpen = new double(0);
	angleClose = new double(0);

	door = new sf::ConvexShape(5);

	door->setPoint(0, sf::Vector2f(0, 0));
	door->setPoint(1, sf::Vector2f(4, 1));
	door->setPoint(2, sf::Vector2f(8, 2));
	door->setPoint(3, sf::Vector2f(8, 31));
	door->setPoint(4, sf::Vector2f(1, 53));

	const sf::Texture *textureDoor = textureManager::load("BackL", "data/Trailer/Part3/Textures/BackL.png");
	door->setTexture(textureDoor);
}

DoorTrailer::~DoorTrailer()
{
	textureManager::unload("CenterBL");
	textureManager::unload("BackL");

	delete door;
	delete center;

	delete MAX_DOOR_OPEN_ANGLE;
}

void DoorTrailer::open(const float &angle, sf::ConvexShape &door)
{
	if (*angleOpen < *MAX_DOOR_OPEN_ANGLE)
	{
		*angleOpen += 0.01;
		for (int i = 0;i < 5;++i)
		{
			if (i == 0 || i == 1 || i == 2)
				continue;
			door.setPoint(i, sf::Vector2f((door.getPoint(i).x - door.getPoint(1).x)*cos(angle) - (door.getPoint(i).y - door.getPoint(1).y)*sin(angle) + door.getPoint(1).x,
				(door.getPoint(i).x - door.getPoint(1).x)*sin(angle) + (door.getPoint(i).y - door.getPoint(1).y)*cos(angle) + door.getPoint(1).y));
		}

		if (*angleOpen == 0.16)angleClose = 0;
		else *angleClose = -(0.16 - *angleOpen);
	}
}

void DoorTrailer::close(const float &angle, sf::ConvexShape &door)
{
	if (*angleClose > -0.16 && angleOpen > 0)
	{
		*angleClose -= 0.01;

		for (int i = 0;i < 5;++i)
		{
			if (i == 0 || i == 1 || i == 2)
				continue;
			door.setPoint(i, sf::Vector2f((door.getPoint(i).x - door.getPoint(1).x)*cos(angle) - (door.getPoint(i).y - door.getPoint(1).y)*sin(angle) + door.getPoint(1).x,
				(door.getPoint(i).x - door.getPoint(1).x)*sin(angle) + (door.getPoint(i).y - door.getPoint(1).y)*cos(angle) + door.getPoint(1).y));
		}

		if (*angleClose == -0.16) angleOpen = 0;
		else *angleOpen = -(-0.16 - *angleClose);
	}
}