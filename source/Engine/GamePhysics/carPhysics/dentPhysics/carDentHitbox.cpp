#include "carDentHitbox.hpp"

#include "../../../../Manager/renderSprites.hpp"

carDentHitbox::carDentHitbox(Car * car)
{
	this->car = car;

	auto allHitboxes = car->getAllHitboxes();

	setHitbox(sf::Vector2f(0, 50), sf::Vector2f(0, 1), 10.f);
	setHitbox(sf::Vector2f(50, 80), sf::Vector2f(-1, 1), 5.f);
	setHitbox(sf::Vector2f(80, 230), sf::Vector2f(-1, 0), 1.f);
	setHitbox(sf::Vector2f(230, 250), sf::Vector2f(-1, -1), 5.f);
	setHitbox(sf::Vector2f(250, 310), sf::Vector2f(0, 1), 5.f);
	setHitbox(sf::Vector2f(310, 330), sf::Vector2f(1, -1), 5.f);
	setHitbox(sf::Vector2f(330, 485), sf::Vector2f(0, 1), 1.f);
	setHitbox(sf::Vector2f(485, static_cast<unsigned>(allHitboxes.size())), sf::Vector2f(1, 1), 5.f);
}

carDentHitbox::~carDentHitbox()
{
	for (const auto &i : hitboxes)
		delete i.second.second;
}

std::vector<std::pair<sf::CircleShape*, std::pair<sf::Vector2f, float*>>> carDentHitbox::getVector()
{
	return hitboxes;
}

void carDentHitbox::draw()
{
	for (const auto&i : hitboxes)
		renderSprites::Instance().addToRender(i.first);
}

void carDentHitbox::setHitbox(const sf::Vector2f & range, const sf::Vector2f &moveOffset, const float & bufValue, const sf::Color & color)
{
	auto allHitboxes = car->getAllHitboxes();

	for (size_t i = static_cast<size_t>(range.x);i < static_cast<size_t>(range.y);i++)
	{
		float *buf = new float(bufValue);
		hitboxes.push_back(std::make_pair(allHitboxes[i], std::make_pair(moveOffset, buf)));
		hitboxes[hitboxes.size() - 1].first->setFillColor(color);
	}
}
