#pragma once

#include "../../Physics/Moveable/Moveable.hpp"

class World
{
public:

	static World &Instance()
	{
		static World world;
		return world;
	}

	std::vector<Moveable*> &getObjects();

	void addMoveableObject(Moveable *object);
	void simulate();

//private:

	std::vector<Moveable*>objects;
};