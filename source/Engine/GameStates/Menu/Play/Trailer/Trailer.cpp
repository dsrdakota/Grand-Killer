#include "Trailer.hpp"
#include "../../../../../Game.hpp"
#include "../../../../../Manager/Texture.hpp"
#include "../../../../../Manager/Text.hpp"

Trailer::Trailer()
{
}

Trailer::~Trailer()
{
}

void Trailer::play()
{
	sf::Time time;
	sf::Clock clock;

	Text text(sf::Color::White, 50, "Trailer ( to change )");

	text.text->setPosition(window->getSize().x / 2 - text.text->getGlobalBounds().width / 2,
		window->getSize().y / 2 - text.text->getGlobalBounds().height / 2);

	while (game.getStatus() != Game::status::CleaningUp && time.asSeconds() < 2)
	{
		game.events();

		window->clear();

		window->draw(*text.text);

		window->display();

		time = clock.getElapsedTime();
	}
}