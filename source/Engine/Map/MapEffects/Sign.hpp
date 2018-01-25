#pragma once

#include <SFML/Graphics.hpp>

#include "../../../Manager/Time.hpp"

class Sign
{
public:

	Sign(const sf::Vector2f &startPos = sf::Vector2f(0,0), const float &rotation = 0);
	~Sign();

	void setPosition(const sf::Vector2f &startPos, const float &rotation = 0);

	sf::Sprite *getSignSprite();
	sf::CircleShape *getSignHitbox();
	int getDrawState();

	void checkCollision();

private:

	enum class drawState
	{
		Under = -1,
		On = 1
	};

	sf::Sprite *sign;
	sf::CircleShape *hitboxSign;
	drawState state;

	sf::Vector2f startPosition;
	float startRotation;

	bool animation;
	sf::Vector2f moveOffset;
	float rotateSpeed;
	float speedAnimation;
	Time clockOfAnimation;
	int timeOfAnimation;

	void playAnimation();
};