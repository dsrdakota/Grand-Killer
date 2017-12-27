#include "Menu.hpp"

#include "../../../Manager/Text.hpp"
#include "../../../Manager/Texture.hpp"
#include "Play/Trailer/Trailer.hpp"
#include "Play/Game/mGame.hpp"

void Menu::play()
{
	sf::Time time;
	sf::Clock clock;

	Text menu(sf::Color::White, 50, "Menu ( to change )");
	Text play(sf::Color::Red, 50, "Play ( click )");
	Text settings(sf::Color::White, 50, "Settings");
	Text info(sf::Color::White, 50, "Help");
	Text exit(sf::Color::White, 50, "Exit");

	menu.text->setPosition(window->getSize().x / 2 - menu.text->getGlobalBounds().width / 2, 200);
	play.text->setPosition(menu.text->getPosition().x, menu.text->getPosition().y + menu.text->getGlobalBounds().height + 50);
	settings.text->setPosition(menu.text->getPosition().x, play.text->getPosition().y + play.text->getGlobalBounds().height + 50);
	info.text->setPosition(menu.text->getPosition().x, settings.text->getPosition().y + settings.text->getGlobalBounds().height + 50);
	exit.text->setPosition(menu.text->getPosition().x, info.text->getPosition().y + info.text->getGlobalBounds().height + 50);

	while (game.getStatus() != Game::status::CleaningUp && time.asSeconds() < 3)
	{
		game.events();

		window->clear();

		window->draw(*menu.text);
		window->draw(*play.text);
		window->draw(*settings.text);
		window->draw(*info.text);
		window->draw(*exit.text);

		window->display();

		time = clock.getElapsedTime();
	
	}
	Game::loadingScreen();

	smallerEngine *wsk;
	Trailer *trailer = new Trailer;
	//wsk = trailer;
	//wsk->play();

	wsk = nullptr;
	delete trailer;

	Game::loadingScreen();

	mGame *game = new mGame;
	wsk = game;
	wsk->play();

	wsk = nullptr;
	delete game;
	delete wsk;
}
