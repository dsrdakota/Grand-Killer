#include "Part2.hpp"
#include "../../../../../../Manager/Texture.hpp"
#include "../../../../../../Manager/Sound.hpp"

Part2::Part2()
{
	show = new bool(true);

	backgroundImg = new sf::Sprite(*textureManager::load("background", "data/Trailer/Part2/Textures/background.png"));

	nick = new Text(sf::Color(255, 162, 0), 150, "10kw10", "data/Font/italic.ttf");

	nick->text->setOutlineThickness(3);
	nick->text->setOutlineColor(sf::Color::White);

	nick->text->setPosition(1366 + nick->text->getGlobalBounds().width, 150);

	present = new Text(sf::Color(255, 162, 0), 150, "Present", "data/Font/italic.ttf");

	present->text->setOutlineThickness(3);
	present->text->setOutlineColor(sf::Color::White);

	present->text->setPosition(-present->text->getGlobalBounds().width - 500, 350);

	characterSize = new unsigned(0);

	gameName = new Text(sf::Color(255, 162, 0), 0, "Grand Killer", "data/Font/italic.ttf");

	gameName->text->setOutlineThickness(3);
	gameName->text->setOutlineColor(sf::Color::White);

	plane = new sf::Sprite(*textureManager::load("plane", "data/Trailer/Part2/Textures/plane.png"));
	plane->setPosition(Game::Instance().getWindow()->getSize().x + 10.f, -10.f);

	showGameName.setBuffer(*soundManager::load("bum", "data/Trailer/Part2/Sound/bum.wav"));
	showGameName.setLoop(false);

	planeSound.setBuffer(*soundManager::load("plane", "data/Trailer/Part2/Sound/plane.wav"));

	sf::Listener::setPosition(Game::Instance().getWindow()->getSize().x/2.f, 0.f , Game::Instance().getWindow()->getSize().y / 2.f);

	sf::Listener::setDirection(0, 0, -1);

	showGameName.setPosition(sf::Listener::getPosition());

	planeSound.setVolume(150);

	planeSound.setAttenuation(50);
	planeSound.setMinDistance(0);
}

Part2::~Part2()
{
	textureManager::unload("background");
	textureManager::unload("plane");

	soundManager::unload("plane");
	soundManager::unload("bum");

	delete show;
	delete nick;
	delete characterSize;
}

void Part2::play(sf::RenderWindow *window, const sf::Time &time, Music &background, bool &changePart)
{
	if (time.asSeconds() >= 0.2)
	{
		++frame;
		trailerTime::reset();
	}
	if (frame <= 33)
		reduceTransparencyBackground();

	else
	{
		boostTransparencyBackground();

		if (transparency >= 255)
			changePart = true;
	}

	dark->setFillColor(sf::Color(0, 0, 0, transparency));


	if (frame >= 20)
	{
		if (*characterSize + 7 <= 150)
			*characterSize += 7;
		else
			*characterSize = 150;
		if (*characterSize < 150)
		{
			gameName->text->setCharacterSize(*characterSize);
			gameName->text->setPosition(Game::Instance().getWindow()->getSize().x / 2 - gameName->text->getGlobalBounds().width / 2, Game::Instance().getWindow()->getSize().y / 2 - gameName->text->getGlobalBounds().height / 2 - 100);
		}

		if (*characterSize == 98)
			if (showGameName.getStatus() == sf::Sound::Status::Stopped)
			showGameName.play();

		if (frame == 20)
			if (planeSound.getStatus() == sf::Sound::Status::Stopped)
				planeSound.play();

		if (frame >= 27)
			plane->move(-18, 1.25);
	}

	if (planeSound.getStatus() == sf::Sound::Status::Playing)
		planeSound.setPosition(plane->getPosition().x + plane->getGlobalBounds().width / 2.f, 0.f, planeSound.getPosition().y + plane->getGlobalBounds().height / 2.f);

	if (show)
	{
		if (nick->text->getPosition().x >= 1366 / 2 - (nick->text->getGlobalBounds().width) / 2)
			nick->text->move(-10, 0);

		if (present->text->getPosition().x <= 1366 / 2 - (present->text->getGlobalBounds().width) / 2)
			present->text->move(10, 0);
	}
	else
	{
		if (nick->text->getPosition().x >= -nick->text->getGlobalBounds().width)
			nick->text->move(-15, 0);

		if (present->text->getPosition().x <= 1367)
			present->text->move(15, 0);
	}

	if (frame == 17)
		show = false;

	frames(window);
}

void Part2::frames(sf::RenderWindow *window)
{
	window->clear();

	window->draw(*backgroundImg);

	window->draw(*nick->text);

	window->draw(*present->text);

	window->draw(*gameName->text);

	window->draw(*plane);

	window->draw(*dark);

	window->display();
}