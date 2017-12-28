#pragma once

#include <SFML/Graphics.hpp>

#include "../../../../../../Manager/Time.hpp"

class Light
{
public:

	Light(const sf::Vector2f &startPos = sf::Vector2f(0, 0), const float &rotation = 0);
	~Light();

	void setPosition(const sf::Vector2f &startPos, const float &rotation = 0);

	sf::Sprite *getStakeSprite();
	sf::Sprite *getLightSprite();
	sf::CircleShape *getLightHitbox();
	int getDrawState();

	void checkCollision();

private:

	enum class drawState
	{
		Under = -1,
		On = 1
	};

	sf::Sprite *stake;
	sf::Sprite *light;
	sf::CircleShape *hitboxLight;
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