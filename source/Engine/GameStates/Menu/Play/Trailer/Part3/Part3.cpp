#include "Part3.hpp"
#include "../../../../../../Manager/Texture.hpp"
#include "../../../../../../Manager/Sound.hpp"
#include "../../../../../../Game.hpp"

#define M_PI 3.14159265359
Part3::Part3()
{
	backgroundImg = new sf::Sprite(*textureManager::load("background", "data/Trailer/Part3/Textures/background.png"));

	dark = new sf::RectangleShape(sf::Vector2f((float)backgroundImg->getTexture()->getSize().x,(float)backgroundImg->getTexture()->getSize().y));

	taxi = new TaxiTrailer;

	actualTarget = new sf::Sprite;

	view = new sf::View(sf::Vector2f(taxi->sprite->getPosition().x,taxi->sprite->getPosition().y), sf::Vector2f(1366, 768));

	playerSite = new sf::Sprite(*textureManager::load("playerSite", "data/Trailer/Part3/Textures/playerSite.png"));

	for (int i = 0;i < 20;++i)
	{
		textureManager::load("walkBody" + std::to_string(i), "data/Trailer/Part3/Textures/Walk/body/" + std::to_string(i) + ".png");
		textureManager::load("walkFeet" + std::to_string(i), "data/Trailer/Part3/Textures/Walk/feet/" + std::to_string(i) + ".png");
	}
	textureManager::load("walkBody20", "data/Trailer/Part3/Textures/Walk/body/20.png");

	player = new sf::Sprite(*textureManager::get("walkBody0"));
	player->setOrigin(134, 145);
	player->rotate(90);
	feet = new sf::Sprite(*textureManager::get("walkFeet0"));

	frameOfImagePlayer = new unsigned(0);

	head = new sf::Sprite(*textureManager::load("head", "data/Trailer/Part3/Textures/Walk/head.png"));

	soundManager::load("suppressing","data/Trailer/Part3/Sound/Car/suppressing/1.wav");
	soundManager::load("accelerating","data/Trailer/Part3/Sound/Car/accelerating/1.wav");
	soundManager::load("stop", "data/Trailer/Part3/Sound/Car/stop/stop.wav");

	carSound = new sf::Sound(*soundManager::get("suppressing"));

	carSound->setVolume(150);
	carSound->setAttenuation(70);
	carSound->setMinDistance(500);

	sf::Listener::setDirection(0, 0, -1);
}

Part3::~Part3()
{
	textureManager::unload("background");

	textureManager::unload("playerSite");

	for (int i = 0;i < 20;++i)
	{
		textureManager::unload("walkBody" + std::to_string(i));
		textureManager::unload("walkFeet" + std::to_string(i));
	}
	textureManager::unload("walkBody20");


	textureManager::unload("head");

	soundManager::unload("suppressing");
	soundManager::unload("accelerating");
	soundManager::unload("stop");

	delete view;
	delete taxi;
	delete player;
	delete playerSite;
	delete feet;
	delete frameOfImagePlayer;
	delete head;
}

void Part3::play(sf::RenderWindow * window, const sf::Time & time, Music & background, bool & changePart)
{
	carSound->setPosition(taxi->sprite->getPosition().x, 0.f, taxi->sprite->getPosition().y);
	sf::Listener::setPosition(head->getPosition().x,0.f,head->getPosition().y);

	if (frame < 30)
		*actualTarget = *playerSite;
	else
		*actualTarget = *player;

	view->setCenter(actualTarget->getPosition().x, actualTarget->getPosition().y);

	if (time.asSeconds() >= 0.2)
	{
		++frame;
		trailerTime::reset();
	}
	if (player->getPosition().y < 1100)
	{
		if (time.asSeconds() > 0.00090 && time.asSeconds() < 0.13555)
		{
			if (*frameOfImagePlayer < 20)
				++*frameOfImagePlayer;
			else
				*frameOfImagePlayer = 0;
		}
		if (frame <= 37)
			reduceTransparencyBackground();
	}

	else
	{
	boostTransparencyBackground();

	if (transparency >= 225)
	{
		if (background.music->getVolume() - 1 > 0)
			background.music->setVolume(background.music->getVolume() - 1);
		else
			background.music->setVolume(0);
	}

	if (background.music->getVolume() <= 0)
		changePart = true;
	}

	dark->setFillColor(sf::Color(0, 0, 0, transparency));


	if (frame >= 32)
	{
		if (frame <= 33)
			taxi->Rotate(1.15f);
		taxi->boostSpeed();
		taxi->Move(sf::Vector2f(-*taxi->actualSpeed, -0.45f));
	}
	else if (taxi->sprite->getPosition().y + taxi->sprite->getGlobalBounds().height / 2 < 990)
	{
		taxi->boostSpeed();
		taxi->Move(sf::Vector2f(-3, *taxi->actualSpeed));
	}
	
	if (view->getCenter().x - view->getSize().x / 2 < 0)
		view->setCenter(sf::Vector2f(view->getSize().x/2, view->getCenter().y));
		

	if (view->getCenter().y - view->getSize().y / 2 < 0)
		view->setCenter(sf::Vector2f(view->getCenter().x,view->getSize().y/2));

	if (view->getCenter().x + view->getSize().x / 2 > backgroundImg->getTexture()->getSize().x)
		view->setCenter(sf::Vector2f(backgroundImg->getTexture()->getSize().x - view->getSize().x / 2, view->getCenter().y));


	if (view->getCenter().y + view->getSize().y / 2 > backgroundImg->getTexture()->getSize().y)
		view->setCenter(sf::Vector2f(view->getCenter().x, backgroundImg->getTexture()->getSize().y - view->getSize().y / 2));
	if (frame < 24)
	{
		playerSite->setPosition(taxi->sprite->getPosition());
		playerSite->setRotation(taxi->sprite->getRotation());
		playerSite->setOrigin(taxi->sprite->getOrigin().x - 60.8f, taxi->sprite->getOrigin().y - 110);
	}
	// Open door

	if (frame >= 23 && frame < 27)
	{
		taxi->door->open(0.08f, *taxi->door->door);
	}
	else if (frame >= 27 && frame < 30)
		taxi->door->close(-0.08f, *taxi->door->door);

	if (frame >= 24 && frame < 26)
	{
		playerSite->rotate(-2.7f);
		playerSite->move(0, 1.3f);
	}
	
	if (frame == 26)
	{
		player->setPosition(playerSite->getGlobalBounds().left + playerSite->getGlobalBounds().width,
			playerSite->getGlobalBounds().top + playerSite->getGlobalBounds().height);
		playerSite->setOrigin(playerSite->getGlobalBounds().width/2, playerSite->getGlobalBounds().height/2);
	}
	if (frame > 26)
		playerSite->setPosition(taxi->sprite->getPosition().x, taxi->sprite->getPosition().y);

	feet->setOrigin(player->getOrigin().x+8,player->getOrigin().y);
	feet->setPosition(player->getPosition());
	feet->setRotation(player->getRotation());

	head->setOrigin(player->getOrigin().x, player->getOrigin().y);
	head->setPosition(player->getPosition());
	head->setRotation(player->getRotation());

	if (carSound->getStatus() == sf::Sound::Status::Stopped)
		carSound->play();

	if (frame >= 29)
	{
		if (player->getPosition().x < 570)
			player->move(1, 0);
		if (player->getPosition().y < 1100)
			player->move(0, 1);
		
		sf::Vector2f point;
		if (player->getPosition().x < 570)
			point = sf::Vector2f(567, 1056);
		else
			point = sf::Vector2f(565, 1168);

		sf::Vector2f norm = point - player->getPosition();
		float rot = atan2(norm.y, norm.x);
		rot = rot * 180.f / (float)(M_PI);
		player->setRotation(rot);

		player->setTexture(*textureManager::get("walkBody" + std::to_string(*frameOfImagePlayer)));

		if(*frameOfImagePlayer < 20)
			feet->setTexture(*textureManager::get("walkFeet" + std::to_string(*frameOfImagePlayer)));
		else 
			feet->setTexture(*textureManager::get("walkFeet19"));
	}

	switch (frame)
	{
	case 18:
		taxi->Rotate(2.25);
		carSound->setBuffer(*soundManager::get("stop"));
		break;
	case 31:
		*taxi->actualSpeed = 0;
		carSound->setBuffer(*soundManager::get("accelerating"));
		break;
	}

	window->setView(*view);

	taxi->updatePosition();

	frames(window);
}

void Part3::frames(sf::RenderWindow * window)
{
	window->clear();

	window->draw(*backgroundImg);

	window->draw(*taxi->door->center);

	window->draw(*playerSite);

	window->draw(*taxi->sprite);

	window->draw(*taxi->door->door);

	window->draw(*feet);

	window->draw(*player);

	window->draw(*head);

	window->draw(*dark);

	window->display();
}
