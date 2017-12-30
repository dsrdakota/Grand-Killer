#include "Collision.hpp"

#include "../../Manager/renderSprites.hpp"

#include <iostream>

Collision::Collision(Car * car)
{
	this->car = car;

	auto allHitboxes = car->getAllHitboxes();

	setHitbox(upRightHitboxes, sf::Vector2f(15, 80), sf::Color::Green);
	setHitbox(rightHitboxes, sf::Vector2f(81, 190), sf::Color::Blue);
	setHitbox(downRightHitboxes, sf::Vector2f(191, 250), sf::Color::Red);
	setHitbox(downHitboxes, sf::Vector2f(251, 300), sf::Color::Yellow);
	setHitbox(downLeftHitboxes, sf::Vector2f(301, 360), sf::Color::Magenta);
	setHitbox(leftHitboxes, sf::Vector2f(361, 460), sf::Color(83, 47, 40));
	setHitbox(upLeftHitboxes, sf::Vector2f(461, 523), sf::Color(255, 165, 0));
	setHitbox(upLeftHitboxes, sf::Vector2f(allHitboxes.size() - 10, allHitboxes.size()-1), sf::Color(255, 165, 0));
	setHitbox(upHitboxes, sf::Vector2f(524, allHitboxes.size()-11), sf::Color(75, 0, 130));
	setHitbox(upHitboxes, sf::Vector2f(0, 14), sf::Color(75, 0, 130));
}

Collision::~Collision()
{
}

void Collision::draw()
{
	/*for (const auto &i : upRightHitboxes)
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
		renderSprites::Instance().addToRender(i);*/
}

void Collision::setHitbox(std::vector<sf::CircleShape*>& hitbox, const sf::Vector2f & range, const sf::Color & color)
{
	auto allHitboxes = car->getAllHitboxes();

	for (auto i = range.x;i <= range.y;++i)
	{
		hitbox.push_back(allHitboxes[i]);
		hitbox[hitbox.size() - 1]->setFillColor(color);
	}
}
