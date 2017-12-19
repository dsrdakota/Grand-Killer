#include "Part1.hpp"
#include "../../../../../../Manager/Texture.hpp"
#include "../../../../../../Manager/Sound.hpp"

Part1::Part1()
{
	textureManager::cleanUp();
	soundManager::cleanUp();
	
	player = new sf::Sprite(*textureManager::load("player", "data/Trailer/Part1/Textures/playerSite.png"));

	backgroundImg = new sf::Sprite(*textureManager::load("background", "data/Trailer/Part1/Textures/background.png"));

	phone = new sf::Sprite(*textureManager::load("phone", "data/Trailer/Part1/Textures/phone.png"));

	player->setOrigin(61, 98);
	player->setPosition(334, 428);

	phone->setOrigin(14, 14);
	phone->setPosition(575, 469);

	talk.setBuffer(*soundManager::load("talk", "data/Trailer/Part1/Sound/talk.wav"));

	phoneRing.setBuffer(*soundManager::load("ring", "data/Trailer/Part1/Sound/phoneRing.wav"));

	phoneRing.setVolume(150);
	talk.setVolume(150);

	sf::Listener::setPosition(player->getPosition().x,0,player->getPosition().y);

	sf::Listener::setDirection(0, 0, 0);

	phoneRing.setPosition(phone->getPosition().x,0,phone->getPosition().y);
}

Part1::~Part1()
{
	textureManager::unload("player");
	textureManager::unload("background");
	textureManager::unload("phone");

	soundManager::unload("talk");
	soundManager::unload("ring");

	delete player;
}

void Part1::play(sf::RenderWindow *window, const sf::Time &time, Music &background, bool &changePart)
{
	if (time.asSeconds() >= 0.13)
	{
		++frame;
		trailerTime::reset();
	}

	if (frame <= 30)
		reduceTransparencyBackground(2);

	else 
	{
		boostTransparencyBackground(2);

		if (background.music->getVolume() + 2 < 120)
			background.music->setVolume(background.music->getVolume() + 2);
		else
			background.music->setVolume(120);
	}

		dark->setFillColor(sf::Color(0, 0, 0, transparency));

		switch (frame)
		{
		case 11:
			if(phoneRing.getStatus() == sf::Sound::Status::Stopped )
				phoneRing.play();
			break;
		case 12:
			if (textureManager::unload("phone"))
				phone->setTexture(*textureManager::load("phone", "data/Trailer/Part1/Textures/phoneCall.png"));
			break;
		case 16:
			if (textureManager::unload("player"))
				player->setTexture(*textureManager::load("player", "data/Trailer/Part1/Textures/playerStand.png"));

			player->setOrigin(91,99);
			player->setPosition(418, 425);

			break;
		case 17:
			if (textureManager::unload("player"))
				player->setTexture(*textureManager::load("player", "data/Trailer/Part1/Textures/playerRotate.png"));

			player->setOrigin(92, 96);
			player->setPosition(432, 435);
			break;
		case 18:
			if (textureManager::unload("player"))
				player->setTexture(*textureManager::load("player", "data/Trailer/Part1/Textures/playerTakingPhone.png"));

			player->setOrigin(59,95);
			break;
		case 19:
			if (textureManager::unload("phone"))
				phone->setTexture(*textureManager::load("phone", "data/Trailer/Part1/Textures/phoneRotate.png"));

			phone->setOrigin(13,13);
			phone->setPosition(548,457);
			break;
		case 20:
			phoneRing.stop();

			textureManager::unload("phone");
			if (textureManager::unload("player"))
				player->setTexture(*textureManager::load("player", "data/Trailer/Part1/Textures/playerTalking.png"));
			player->setOrigin(83,90);
			player->setPosition(439,481);

			if(talk.getStatus() == sf::Sound::Status::Stopped)
				talk.play();

			sf::Listener::setPosition(player->getPosition().x, 0, player->getPosition().y);
			sf::Listener::setDirection(0, 0, 1);

			talk.setPosition(468, 0, 472);
			talk.setAttenuation(0);

			break;
		case 21:
			player->setPosition(444, 499);
			talk.setPosition(474, 0, 490);

			break;
		case 45:
			changePart = true; // Part 2

			break;
		}
	frames(window);
}

void Part1::frames(sf::RenderWindow *window)
{

	window->clear();
	
	window->draw(*backgroundImg);

	window->draw(*player);

	if(frame<20)
		window->draw(*phone);

	window->draw(*dark);

	window->display();
}