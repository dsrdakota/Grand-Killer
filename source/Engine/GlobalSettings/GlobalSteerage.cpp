#include "GlobalSteerage.hpp"

const sf::Keyboard::Key & GlobalSteerage::getKey(const Sections & section, const Rodzaj & rodzaj)
{
	return Instance().steerage[section][rodzaj];
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
	steerage[Sections::Car][Rodzaj::Gas] = sf::Keyboard::W;
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
