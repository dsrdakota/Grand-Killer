#include "Intro.hpp"

#include "../../Engine/Engine.hpp"

bool Intro::play()
{
	sf::Time time;
	sf::Clock clock;

	Text text(sf::Color::White, 50, "Intro ( to change )");

	text.text->setPosition(window->getSize().x / 2 - text.text->getGlobalBounds().width / 2,
		window->getSize().y / 2 - text.text->getGlobalBounds().height / 2);

	while (game.getStatus() != Game::status::CleaningUp && time.asSeconds() < 1.5)
	{
		game.events();

		window->clear();

		window->draw(*text.text);

		window->display();

		time = clock.getElapsedTime();
	}

	return true;
}
