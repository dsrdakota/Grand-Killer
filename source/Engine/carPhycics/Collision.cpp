#include "Collision.hpp"

#include "../../Manager/renderSprites.hpp"

#include <iostream>

Collision::Collision(Car * car)
{
	this->car = car;
	auto allHitboxes = car->getAllHitboxes();
	for (auto i = 15;i <= 80;++i)
	{
		upRightHitboxes.push_back(allHitboxes[i]);
		upRightHitboxes[upRightHitboxes.size() - 1]->setFillColor(sf::Color::Green);
	}

	for (auto i = 81;i <= 190;++i)
	{
		rightHitboxes.push_back(allHitboxes[i]);
		rightHitboxes[rightHitboxes.size() - 1]->setFillColor(sf::Color::Blue);
	}

	for (auto i = 191;i <= 250;++i)
	{
		downRightHitboxes.push_back(allHitboxes[i]);
		downRightHitboxes[downRightHitboxes.size() - 1]->setFillColor(sf::Color::Red);
	}

	for (auto i = 251;i <= 300;++i)
	{
		downHitboxes.push_back(allHitboxes[i]);
		downHitboxes[downHitboxes.size() - 1]->setFillColor(sf::Color::Yellow);
	}

	for (auto i = 301;i <= 360;++i)
	{
		downLeftHitboxes.push_back(allHitboxes[i]);
		downLeftHitboxes[downLeftHitboxes.size() - 1]->setFillColor(sf::Color::Magenta);
	}

	for (auto i = 361;i <= 460;++i)
	{
		leftHitboxes.push_back(allHitboxes[i]);
		leftHitboxes[leftHitboxes.size() - 1]->setFillColor(sf::Color(83,47,40));
	}

	for (auto i = 461;i <= 523;++i)
	{
		upLeftHitboxes.push_back(allHitboxes[i]);
		upLeftHitboxes[upLeftHitboxes.size() - 1]->setFillColor(sf::Color(255,165,0));
	}

	for (auto i = allHitboxes.size()-1;i >= allHitboxes.size()-10;--i)
	{
		upLeftHitboxes.push_back(allHitboxes[i]);
		upLeftHitboxes[upLeftHitboxes.size() - 1]->setFillColor(sf::Color(255, 165, 0));
	}

	for (auto i = 524;i <= allHitboxes.size()-11;++i)
	{
		upHitboxes.push_back(allHitboxes[i]);
		upHitboxes[upHitboxes.size() - 1]->setFillColor(sf::Color(75,0,130));
	}
	for (auto i = 0;i <= 14;++i)
	{
		upHitboxes.push_back(allHitboxes[i]);
		upHitboxes[upHitboxes.size() - 1]->setFillColor(sf::Color(75, 0, 130));
	}

	// i know... i will optimise it tomorrow
}

Collision::~Collision()
{
}

void Collision::draw()
{
	for (const auto &i : upRightHitboxes)
		renderSprites::Instance().addToRender(i);

	for (const auto &i : rightHitboxes)
		renderSprites::Instance().addToRender(i);

	for (const auto &i : downRightHitboxes)
		renderSprites::Instance().addToRender(i);

	for (const auto &i : downHitboxes)
		renderSprites::Instance().addToRender(i);

	for (const auto &i : downLeftHitboxes)
		renderSprites::Instance().addToRender(i);

	for (const auto &i : leftHitboxes)
		renderSprites::Instance().addToRender(i);

	for (const auto &i : upLeftHitboxes)
		renderSprites::Instance().addToRender(i);

	for (const auto &i : upHitboxes)
		renderSprites::Instance().addToRender(i);
}
