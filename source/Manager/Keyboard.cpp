#include "Keyboard.hpp"

#include "Texture.hpp"
#include "renderSprites.hpp"

#include <iostream>

Keyboard::Keyboard()
{
	// 35 x 28

	auto keyboard = textureManager::load("keyboard", "data/Game/keyboard.png");

	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(25, 24, 35, 36))); // ESC

	cutRegularKeys(91, 24, 4);
	cutRegularKeys(266, 24, 4);
	cutRegularKeys(440, 24, 4);
	cutRegularKeys(614, 24, 3);
	cutRegularKeys(25, 97, 13);

	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(520, 97, 70, 36))); // Backspace

	cutRegularKeys(614, 97, 3);
	cutRegularKeys(749, 97, 4);

	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(25, 138, 53, 36))); // Tab

	cutRegularKeys(81, 138, 12);

	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(538, 138, 62, 36))); // Backslash

	cutRegularKeys(614, 138, 3);
	cutRegularKeys(749, 138, 3);

	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(863, 138, 36, 76))); // Add

	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(25, 177, 64, 36))); // Caps

	cutRegularKeys(92, 177, 11);

	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(511, 177, 79, 36))); // Enter

	cutRegularKeys(749, 177, 3);

	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(25, 216, 90, 36))); // Shift

	cutRegularKeys(119, 216, 10);

	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(25, 216, 90, 36))); // Shift

	cutRegularKeys(652, 216, 1);
	cutRegularKeys(749, 216, 3);

	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(25, 256, 54, 36))); // LCtrl
	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(81, 256, 47, 36))); // LSystem
	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(131, 256, 46, 36))); // LAlt

	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(180, 256, 206, 36))); // Space

	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(131, 256, 46, 36))); // RAlt
	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(81, 256, 47, 36))); // RSystem
	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(487, 256, 47, 36))); // Menu
	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(25, 256, 54, 36))); // RCtrl

	cutRegularKeys(615, 256, 3);

	keysSprite.push_back(new sf::Sprite(*keyboard, sf::IntRect(749, 256, 73, 36))); // 0

	cutRegularKeys(825, 256, 1);
}

Keyboard::~Keyboard()
{
	for (const auto &i : keysSprite)
		delete i;
}

sf::Sprite* Keyboard::getKeySprite(const Keys & key)
{
	sf::Sprite* newKey = new sf::Sprite;
	*newKey = *keysSprite[static_cast<int>(key)];
	return newKey;
}

void Keyboard::cutRegularKeys(const int & Left, const int & Top, const size_t & count)
{
	for (size_t i = 0;i<count;++i)
		keysSprite.push_back(new sf::Sprite(*textureManager::get("keyboard"), sf::IntRect(Left + i * 38, Top, 35, 36)));
}
