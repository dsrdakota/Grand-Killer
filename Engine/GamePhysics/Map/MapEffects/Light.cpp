#include "Light.hpp"

#include "../../../../Manager/Texture.hpp"
#include "../../../GameStates/Menu/Play/Game/mGame.hpp"

Light::Light(const sf::Vector2f & startPos, const float & rotation)
{
	state = drawState::On;
	startPosition = startPos;
	startRotation = rotation;
	
	stake = new sf::Sprite(*textureManager::get("stake"));
	light = new sf::Sprite(*textureManager::get("light1"));
	hitboxLight = new sf::CircleShape(5);

	stake->setOrigin(123, 53);
	light->setOrigin(stake->getOrigin().x - 15, stake->getOrigin().y + 2);
	hitboxLight->setOrigin(stake->getOrigin().x - 119, stake->getOrigin().y - 50);

	stake->setPosition(startPos);
	light->setPosition(startPos);
	hitboxLight->setPosition(startPos);

	stake->setRotation(rotation);
	hitboxLight->setRotation(rotation);
	light->setRotation(rotation);

	animation = false;
	speedAnimation = 0;
	moveOffset = sf::Vector2f(0, 0);
	timeOfAnimation = 6;
}

Light::~Light()
{
	delete light;
	delete hitboxLight;
}

void Light::setPosition(const sf::Vector2f & startPos, const float & rotation)
{
	stake->setPosition(startPos);
	light->setPosition(startPos);
	hitboxLight->setPosition(startPos);

	stake->setRotation(rotation);
	hitboxLight->setRotation(rotation);
	light->setRotation(rotation);

	startPosition = startPos;
	startRotation = rotation;
}

sf::Sprite * Light::getStakeSprite()
{
	return stake;
}

sf::Sprite * Light::getLightSprite()
{
	return light;
}

sf::CircleShape * Light::getLightHitbox()
{
	return hitboxLight;
}

int Light::getDrawState()
{
	return static_cast<int>(state);
}

void Light::checkCollision()
{
	auto allCars = mGame::Instance().getAllCars();

	for (const auto &i : allCars)
	{
		auto allHitboxOfCar = i->getAllHitboxes();
		for (const auto &j : allHitboxOfCar)
		{
			if (hitboxLight->getGlobalBounds().intersects(j->getGlobalBounds()) && !animation)
			{
				state = drawState::Under;
				light->setTexture(*textureManager::get("light4"));

				moveOffset = i->getMovementVector();
				speedAnimation = static_cast<float>(i->getSpeed());
				
				if(i->getSpeed() > 5)
					i->setSpeed(static_cast<float>(i->getSpeed()) - 2.f);

				stake->move(moveOffset.x * speedAnimation, moveOffset.y * speedAnimation);
				light->move(moveOffset.x * speedAnimation, moveOffset.y * speedAnimation);
				hitboxLight->move(moveOffset.x * speedAnimation, moveOffset.y * speedAnimation);

				rotateSpeed = static_cast<float>(*i->getOverSteerValue()) / 8.f * -1.f;

				stake->rotate(rotateSpeed);
				light->rotate(rotateSpeed);
				hitboxLight->rotate(rotateSpeed);
			}
			else if (moveOffset != sf::Vector2f(0, 0) && speedAnimation != 0)
				animation = true;
		}
	}

	if (animation)
		playAnimation();
}

void Light::playAnimation()
{
	if (speedAnimation > 0)
	{
		stake->move(moveOffset.x * speedAnimation, moveOffset.y * speedAnimation);
		light->move(moveOffset.x * speedAnimation, moveOffset.y * speedAnimation);
		hitboxLight->move(moveOffset.x * speedAnimation, moveOffset.y * speedAnimation);

		stake->rotate(rotateSpeed);
		light->rotate(rotateSpeed);
		hitboxLight->rotate(rotateSpeed);

		speedAnimation -= 0.8f;
	}

	if (clockOfAnimation.time->asSeconds() >= 1)
	{
		if (timeOfAnimation > 0)
			timeOfAnimation--;
		clockOfAnimation.clock->restart();
		*clockOfAnimation.time = sf::Time::Zero;
	}

	if (speedAnimation <= 0 && timeOfAnimation <= 0 &&
		(Map::isOutsideView(sf::Vector2f(stake->getGlobalBounds().left, stake->getGlobalBounds().top)) && // left-up corner
		Map::isOutsideView(sf::Vector2f(stake->getGlobalBounds().left + stake->getGlobalBounds().width, stake->getGlobalBounds().top)) && // right-up corner
		Map::isOutsideView(sf::Vector2f(stake->getGlobalBounds().left + stake->getGlobalBounds().width, stake->getGlobalBounds().top + stake->getGlobalBounds().height)) && // right-down corner
		Map::isOutsideView(sf::Vector2f(stake->getGlobalBounds().left, stake->getGlobalBounds().top + stake->getGlobalBounds().height)) && // left-down corner
		Map::isOutsideView(startPosition)))
	{
		state = drawState::On;
		animation = false;
		speedAnimation = 0;
		moveOffset = sf::Vector2f(0, 0);
		timeOfAnimation = 6;

		stake->setPosition(startPosition);
		light->setPosition(startPosition);
		hitboxLight->setPosition(startPosition);

		stake->setRotation(startRotation);
		hitboxLight->setRotation(startRotation);
		light->setRotation(startRotation);

		light->setTexture(*textureManager::get("light1"));
	}
}
