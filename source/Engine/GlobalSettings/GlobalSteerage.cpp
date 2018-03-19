#include "GlobalSteerage.hpp"

const sf::Keyboard::Key & GlobalSteerage::getKey(const Sections & section, const Type & type)
{
	return Instance().steerage[section][type];
}

GlobalSteerage::GlobalSteerage()
{
	loadDefaultCarSteerage();
	loadDefaultFightSteerage();
	loadDefaultGunsSteerage();
	loadDefaultWalkSteerage();
}

void GlobalSteerage::loadDefaultCarSteerage()
{
	steerage[Sections::Car][Type::Gas] = sf::Keyboard::W;
	steerage[Sections::Car][Type::Break] = sf::Keyboard::S;
	steerage[Sections::Car][Type::HandBreak] = sf::Keyboard::Space;
	steerage[Sections::Car][Type::TurnLeft] = sf::Keyboard::A;
	steerage[Sections::Car][Type::TurnRight] = sf::Keyboard::D;
}

void GlobalSteerage::loadDefaultWalkSteerage()
{
}

void GlobalSteerage::loadDefaultFightSteerage()
{
}

void GlobalSteerage::loadDefaultGunsSteerage()
{
}

GlobalSteerage::~GlobalSteerage()
{
}
