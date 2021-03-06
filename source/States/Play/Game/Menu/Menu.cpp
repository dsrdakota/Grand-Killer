#include "Menu.hpp"

#include "../../../../Map/Minimap.hpp"

#include <ctime>

Menu::Menu() : window(Game::Instance().getWindow())
{
	state = new States(States::Mapa);

	background = new sf::RectangleShape(static_cast<sf::Vector2f>(window->getSize()));

	background->setFillColor(sf::Color(1, 36, 3, 200));

	grandKillerText = new Text(sf::Color::White, 50, "Grand Killer", "italic");

	leftArrow = new sf::Sprite(*TextureManager::get("leftArrow"));
	rightArrow = new sf::Sprite(*TextureManager::get("rightArrow"));

	name = new Text(sf::Color::White, 17, "Bohater", "italic");
	time = new Text(sf::Color::White, 17, "Niedziela 13:52", "italic");
	cash = new Text(sf::Color::White, 17, "$000,00", "italic");

	headersButton.push_back(new Button(sf::Vector2f((window->getSize().x - window->getSize().x * 0.4f) / 5.f, leftArrow->getGlobalBounds().height + 8.f), 15, "MAPA", Button::State::header));
	headersButton.push_back(new Button(sf::Vector2f((window->getSize().x - window->getSize().x * 0.4f) / 5.f, leftArrow->getGlobalBounds().height + 8.f), 15, "DZIENNIK", Button::State::header));
	headersButton.push_back(new Button(sf::Vector2f((window->getSize().x - window->getSize().x * 0.4f) / 5.f, leftArrow->getGlobalBounds().height + 8.f), 15, "STATYSTYKI", Button::State::header));
	headersButton.push_back(new Button(sf::Vector2f((window->getSize().x - window->getSize().x * 0.4f) / 5.f, leftArrow->getGlobalBounds().height + 8.f), 15, "USTAWIENIA", Button::State::header));
	headersButton.push_back(new Button(sf::Vector2f((window->getSize().x - window->getSize().x * 0.4f) / 5.f, leftArrow->getGlobalBounds().height + 8.f), 15, "GRA", Button::State::header));

	options.push_back(new MapInMenu());
	options.push_back(new Diary());
	options.push_back(new Statistics());
	options.push_back(new Steerage());
	options.push_back(new GameInMenu());

	headersButton[0]->setEnabled();

	wsk = options[static_cast<int>(States::Mapa)];

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "WYBIERZ"), KeysManager::Instance().getKeySprite(KeysManager::Keys::Enter)));
	navigation[0].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "WROC"), KeysManager::Instance().getKeySprite(KeysManager::Keys::Esc)));
	navigation[1].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), KeysManager::Instance().getKeySprite(KeysManager::Keys::E)));
	navigation[2].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "PRZEWIJANIE"), KeysManager::Instance().getKeySprite(KeysManager::Keys::Q)));
	navigation[3].second->setScale(0.9f, 0.9f);

	cooldownEscapeButton = 0;
	cooldownChangeStates = 1;
	optionIsActive = false;
	escapeWasRelased = true;
}

Menu::~Menu()
{
	delete leftArrow;
	delete rightArrow;
	delete grandKillerText;
	delete background;

	for (const auto &i : headersButton)
		delete i;

	for (const auto &i : options)
		delete i;

	for (const auto &i : navigation)
	{
		delete i.first;
		delete i.second;
	}
}

void Menu::updateCooldown()
{
	if (cooldownEscapeButton && timeEscapeButton.time->asSeconds() >= 0.25f)
	{
		cooldownEscapeButton--;
		timeEscapeButton.clock->restart();
		*timeEscapeButton.time = sf::Time::Zero;
	}

	if (cooldownChangeStates && timeChangeStates.time->asSeconds() >= 0.2f)
	{
		cooldownChangeStates = 0;
		timeChangeStates.clock->restart();
		*timeChangeStates.time = sf::Time::Zero;
	}
}

void Menu::restartCooldownValue()
{
	cooldownEscapeButton = 2;
	timeEscapeButton.clock->restart();
	*timeEscapeButton.time = sf::Time::Zero;
}

void Menu::setPosition(const sf::Vector2f &playerPos, const float &playerRot)
{
	this->playerPos = playerPos;
	this->playerRot = playerRot;

	grandKillerText->text->setPosition(window->getSize().x *0.2f,window->getSize().y * 0.1f);

	leftArrow->setPosition(grandKillerText->text->getPosition().x - leftArrow->getGlobalBounds().width - 5, grandKillerText->text->getPosition().y + grandKillerText->text->getGlobalBounds().height + leftArrow->getGlobalBounds().height + 10.f);

	headersButton[0]->setPosition(sf::Vector2f(grandKillerText->text->getPosition().x, leftArrow->getPosition().y - 2.5f));

	for (size_t i = 1;i<headersButton.size();++i)
		headersButton[i]->setPosition(sf::Vector2f(headersButton[i - 1]->getButtonSprite()->getPosition().x + headersButton[i - 1]->getButtonSprite()->getGlobalBounds().width + 2,
			leftArrow->getPosition().y - 2.5f));

	cash->text->setPosition(headersButton[headersButton.size() - 1]->getButtonSprite()->getPosition().x,
		headersButton[headersButton.size() - 1]->getButtonSprite()->getPosition().y - cash->text->getGlobalBounds().height - 7);

	time->text->setPosition(headersButton[headersButton.size() - 1]->getButtonSprite()->getPosition().x,
		cash->text->getPosition().y - time->text->getGlobalBounds().height - 4);

	name->text->setPosition(headersButton[headersButton.size() - 1]->getButtonSprite()->getPosition().x,
		time->text->getPosition().y - name->text->getGlobalBounds().height - 4);

	rightArrow->setPosition(headersButton[headersButton.size() - 1]->getButtonSprite()->getPosition().x + headersButton[headersButton.size() - 1]->getButtonSprite()->getGlobalBounds().width + 5.f,
		leftArrow->getPosition().y);

	navigation[0].second->setPosition(window->getSize().x - navigation[0].second->getGlobalBounds().width - 40,
		window->getSize().y - navigation[0].second->getGlobalBounds().height - 15);
	navigation[0].first->text->setPosition(navigation[0].second->getPosition().x - navigation[0].first->text->getGlobalBounds().width,
		navigation[0].second->getPosition().y + navigation[0].second->getGlobalBounds().height / 2 - navigation[0].first->text->getGlobalBounds().height);

	navigation[1].second->setPosition(navigation[0].first->text->getPosition().x - 40,
		navigation[0].second->getPosition().y);
	navigation[1].first->text->setPosition(navigation[1].second->getPosition().x - navigation[1].first->text->getGlobalBounds().width,
		navigation[1].second->getPosition().y + navigation[1].second->getGlobalBounds().height / 2 - navigation[1].first->text->getGlobalBounds().height);

	navigation[2].second->setPosition(navigation[1].first->text->getPosition().x - 40,
		navigation[1].second->getPosition().y);

	navigation[3].second->setPosition(navigation[2].second->getPosition().x - 33,
		navigation[2].second->getPosition().y);
	navigation[3].first->text->setPosition(navigation[3].second->getPosition().x - navigation[3].first->text->getGlobalBounds().width,
		navigation[3].second->getPosition().y + navigation[3].second->getGlobalBounds().height / 2 - navigation[3].first->text->getGlobalBounds().height);

	auto firstButton = headersButton[0]->getButtonSprite();

	const auto &allTiles = TilesManager::getTilesVector();
	Tile* tile = allTiles[static_cast<size_t>(playerPos.x / TilesManager::getTileSize())][static_cast<size_t>(playerPos.y / TilesManager::getTileSize())];
	sf::Vector2f lenght = playerPos - tile->getTileMapSprite()->getPosition();
	
	Minimap::Instance().setPosition();
	Minimap::Instance().setPlayerPosition(tile, lenght, playerRot);

	for (const auto &i : options)
		i->setPosition(sf::Vector2f(firstButton->getPosition().x,
			firstButton->getPosition().x + window->getSize().x * 0.8f - window->getSize().x * 0.2f + 10),
			sf::Vector2f(firstButton->getPosition().y + firstButton->getGlobalBounds().height + 10,
				firstButton->getPosition().y + firstButton->getGlobalBounds().height + window->getSize().y * 0.6f));
}

const int & Menu::getCooldownValue()
{
	return cooldownEscapeButton;
}

bool Menu::canExitMenu()
{
	return escapeWasRelased && wsk->exit();
}

void Menu::draw()
{
	update();

	Painter::Instance().addToInterfaceDraw(background);

	if (!(wsk == options[static_cast<int>(States::Mapa)] && optionIsActive))
	{
		Painter::Instance().addToInterfaceDraw(grandKillerText->text);
		Painter::Instance().addToInterfaceDraw(leftArrow);
		Painter::Instance().addToInterfaceDraw(rightArrow);
		for (const auto &i : headersButton)
			i->draw();

		Painter::Instance().addToInterfaceDraw(name->text);
		Painter::Instance().addToInterfaceDraw(time->text);
		Painter::Instance().addToInterfaceDraw(cash->text);
	}

	if (optionIsActive)
		wsk->drawActive();
	else
	{
		for (const auto &i : navigation)
		{
			Painter::Instance().addToInterfaceDraw(i.first->text);
			Painter::Instance().addToInterfaceDraw(i.second);
		}
		wsk->drawUnactive();
	}
}

void Menu::update()
{
	optionIsActive = wsk->isActive();

	std::string newerTime = updateTime();

	if (time->text->getString() != newerTime)
		time->text->setString(newerTime);

	if (!wsk->exit())
		escapeWasRelased = false;

	if (!optionIsActive)
	{
		if (!escapeWasRelased && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !sf::Mouse::isButtonPressed(sf::Mouse::Right))
			escapeWasRelased = true;

		checkArrowIsPressed(1); // right
		checkArrowIsPressed(-1); // left

		for (size_t i = 0;i < headersButton.size();++i)
		{
			headersButton[i]->Hover();
			if (headersButton[i]->mouseOnClick())
			{
				headersButton[static_cast<int>(*state)]->setDisabled();

				*state = static_cast<States>(i);

				headersButton[static_cast<int>(*state)]->setEnabled();

				wsk = options[static_cast<int>(*state)];
			}
		}
	}
}

std::string Menu::updateTime()
{
#pragma warning(disable : 4996)

	time_t czas;
	std::time(&czas);
	std::string s(ctime(&czas));

	std::string days[] = {
		"Mon",
		"Tue",
		"Wed",
		"Thu",
		"Fri",
		"Sat",
		"Sun"
	};

	std::string dni[] = {
		"Poniedzialek",
		"Wtorek",
		"Sroda",
		"Czwartek",
		"Piatek",
		"Sobota",
		"Niedziela"
	};

	auto function = [&](const std::string &day) {
		for (size_t i = 0;i < 7;++i)
			if (days[i] == day)
				return i;

		return static_cast<size_t>(0);
	};

	std::string day = s.substr(0, 3);
	std::string time = s.substr(s.find(':') - 2, 8);

	return dni[function(day)] + ' ' + time;
}

void Menu::checkArrowIsPressed(const int &side)
{
	States first, last;
	sf::Keyboard::Key keyQE; // Q or E
	sf::Keyboard::Key keyAD;
	sf::Keyboard::Key keyArrow;
	sf::Sprite *arrowSide;

	if (side == 1) // right
	{
		first = States::Gra;
		last = States::Mapa;
		keyQE = sf::Keyboard::E;
		keyAD = sf::Keyboard::D;
		keyArrow = sf::Keyboard::Right;
		arrowSide = rightArrow;
	}
	else // left
	{
		first = States::Mapa;
		last = States::Gra;
		keyQE = sf::Keyboard::Q;
		keyAD = sf::Keyboard::A;
		keyArrow = sf::Keyboard::Left;
		arrowSide = leftArrow;
	}

	if (!cooldownChangeStates && (mouseOnClickArrow(arrowSide) ||
		sf::Keyboard::isKeyPressed(keyQE) ||
		sf::Keyboard::isKeyPressed(keyAD) ||
		sf::Keyboard::isKeyPressed(keyArrow)))
	{
		headersButton[static_cast<int>(*state)]->setDisabled();

		if (*state == first)
			*state = last;
		else
			*state = static_cast<States>(static_cast<int>(*state) + side);

		cooldownChangeStates = 1;
		timeChangeStates.clock->restart();
		*timeChangeStates.time = sf::Time::Zero;
		headersButton[static_cast<int>(*state)]->setEnabled();

		wsk = options[static_cast<int>(*state)];

		return;
	}
}

bool Menu::mouseOnClickArrow(sf::Sprite * arrow)
{
	if (mouseOnArrow(arrow) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}

bool Menu::mouseOnArrow(sf::Sprite * arrow)
{
	if (arrow->getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition())))
	{
		arrow->setScale(sf::Vector2f(1.1f, 1.1f));
		return true;
	}
	else
		arrow->setScale(sf::Vector2f(1.f, 1.f));
	return false;
}