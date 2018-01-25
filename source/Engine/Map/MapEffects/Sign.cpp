#include "Sign.hpp"

#include "../../../Manager/Texture.hpp"
#include "../../GameStates/Menu/Play/Game/mGame.hpp"

Sign::Sign(const sf::Vector2f &startPos, const float &rotation)
{
	state = drawState::On;
	startPosition = startPos;
	startRotation = rotation;

	sign = new sf::Sprite(*textureManager::get("sign"));
	hitboxSign = new sf::CircleShape(5);

	sign->setOrigin(30, 72);
	hitboxSign->setOrigin(sign->getOrigin().x - 33,sign->getOrigin().y-60);
	
	sign->setPosition(startPos);
	hitboxSign->setPosition(startPos);

	hitboxSign->setRotation(rotation);
	sign->setRotation(rotation);

	animation = false;
	speedAnimation = 0;
	moveOffset = sf::Vector2f(0, 0);
	timeOfAnimation = 6;
}

Sign::~Sign()
{
	delete sign;
	delete hitboxSign;
}

void Sign::setPosition(const sf::Vector2f & startPos, const float & rotation)
{
	sign->setPosition(startPos);
	hitboxSign->setPosition(startPos);

	hitboxSign->setRotation(rotation);
	sign->setRotation(rotation);

	startPosition = startPos;
	startRotation = rotation;
}

sf::Sprite * Sign::getSignSprite()
{
	return sign;
}

sf::CircleShape * Sign::getSignHitbox()
{
	return hitboxSign;
}

int Sign::getDrawState()
{
	return static_cast<int>(state);
}

void Sign::checkCollision()
{
	auto allCars = mGame::Instance().getAllCars();

	for (const auto &i : allCars)
	{
		auto allHitboxOfCar = i->getAllHitboxes();
		for (const auto &j : allHitboxOfCar)
		{
			if (hitboxSign->getGlobalBounds().intersects(j->getGlobalBounds()) && !animation)
			{
				state = drawState::Under;

				moveOffset = i->getMovementVector();
				speedAnimation = static_cast<float>(i->getSpeed());

				if(i->getSpeed() > 5)
					i->setSpeed(static_cast<float>(i->getSpeed()) - 2.f);

				sign->move(moveOffset.x * speedAnimation,moveOffset.y * speedAnimation);
				hitboxSign->move(moveOffset.x * speedAnimation, moveOffset.y * speedAnimation);

				rotateSpeed = static_cast<float>(*i->getOverSteerValue()) / 8.f * -1.f;

				sign->rotate(rotateSpeed);
				hitboxSign->rotate(rotateSpeed);
			}
			else if (moveOffset != sf::Vector2f(0, 0) && speedAnimation != 0)
				animation = true;
		}
	}

	if (animation)
		playAnimation();
}

void Sign::playAnimation()
{
	if (speedAnimation > 0)
	{
		sign->move(moveOffset.x * speedAnimation, moveOffset.y * speedAnimation);
		hitboxSign->move(moveOffset.x * speedAnimation, moveOffset.y * speedAnimation);

		sign->rotate(rotateSpeed);
		hitboxSign->rotate(rotateSpeed);

		speedAnimation -= 0.5f;
	}

	if (clockOfAnimation.time->asSeconds() >= 1)
	{
		if (timeOfAnimation > 0)
			timeOfAnimation--;
		clockOfAnimation.clock->restart();
		*clockOfAnimation.time = sf::Time::Zero;
	}

	if (speedAnimation <= 0 && timeOfAnimation <=0 &&
		Map::isOutsideView(sf::Vector2f(sign->getGlobalBounds().left,sign->getGlobalBounds().top)) && // left-up corner
		Map::isOutsideView(sf::Vector2f(sign->getGlobalBounds().left + sign->getGlobalBounds().width, sign->getGlobalBounds().top)) && // right-up corner
		Map::isOutsideView(sf::Vector2f(sign->getGlobalBounds().left + sign->getGlobalBounds().width, sign->getGlobalBounds().top + sign->getGlobalBounds().height)) && // right-down corner
		Map::isOutsideView(sf::Vector2f(sign->getGlobalBounds().left, sign->getGlobalBounds().top + sign->getGlobalBounds().height)) && // left-down corner
		Map::isOutsideView(startPosition))
	{
		state = drawState::On;
		animation = false;
		speedAnimation = 0;
		moveOffset = sf::Vector2f(0, 0);
		timeOfAnimation = 6;

		sign->setPosition(startPosition);
		hitboxSign->setPosition(startPosition);

		hitboxSign->setRotation(startRotation);
		sign->setRotation(startRotation);
	}
}
