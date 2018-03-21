#include "gameInMenu.hpp"

GameInMenu::GameInMenu()
{
	buttons.push_back(new Button(sf::Vector2f(225, 30), 15, "Szybki zapis"));
	buttons.push_back(new Button(sf::Vector2f(225, 30), 15, "Wczytaj gre"));
	buttons.push_back(new Button(sf::Vector2f(225, 30), 15, "Nowa gra"));
	buttons.push_back(new Button(sf::Vector2f(225, 30), 15, "Autorzy"));
	buttons.push_back(new Button(sf::Vector2f(225, 30), 15, "Wyjdz z gry"));

	hitboxClick = new sf::RectangleShape;
	backgroundRight = new sf::RectangleShape;
	backgroundRight->setFillColor(buttons[0]->getButtonSprite()->getFillColor());

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "WROC"), KeysManager::Instance().getKeySprite(KeysManager::Keys::Esc)));
	navigation[0].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), KeysManager::Instance().getKeySprite(KeysManager::Keys::S)));
	navigation[1].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "PRZEWIJANIE"), KeysManager::Instance().getKeySprite(KeysManager::Keys::W)));
	navigation[2].second->setScale(0.9f, 0.9f);

	state = new optionState(optionState::Save);

	cooldownChangeStates = 1;

	active = false;
	isMousePressed = false;

	centerTextOfOption = new Text(sf::Color::White, 70, "Wkrotce");
}

GameInMenu::~GameInMenu()
{
	delete state;

	for (const auto &i : buttons)
		delete i;

	for (const auto &i : navigation)
	{
		delete i.first;
		delete i.second;
	}

	delete centerTextOfOption;
}

void GameInMenu::setPosition(const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange)
{
	hitboxClick->setSize(sf::Vector2f(borderXrange.y - borderXrange.x, borderYrange.y - borderYrange.x));
	hitboxClick->setPosition(borderXrange.x, borderYrange.x);

	backgroundRight->setSize(sf::Vector2f(hitboxClick->getSize().x - buttons[0]->getButtonSprite()->getSize().x, hitboxClick->getSize().y));

	buttons[0]->setPosition(sf::Vector2f(borderXrange.x, borderYrange.x));
	for (size_t i = 1;i<buttons.size();++i)
		buttons[i]->setPosition(sf::Vector2f(borderXrange.x, buttons[i - 1]->getButtonSprite()->getPosition().y + buttons[i - 1]->getButtonSprite()->getGlobalBounds().height + 3.f));

	backgroundRight->setPosition(buttons[0]->getButtonSprite()->getPosition().x + buttons[0]->getButtonSprite()->getGlobalBounds().width + 8, buttons[0]->getButtonSprite()->getPosition().y);

	navigation[0].second->setPosition(window->getSize().x - navigation[0].second->getGlobalBounds().width - 40,
		window->getSize().y - navigation[0].second->getGlobalBounds().height - 15);
	navigation[0].first->text->setPosition(navigation[0].second->getPosition().x - navigation[0].first->text->getGlobalBounds().width,
		navigation[0].second->getPosition().y + navigation[0].second->getGlobalBounds().height / 2 - navigation[0].first->text->getGlobalBounds().height);

	navigation[1].second->setPosition(navigation[0].first->text->getPosition().x - 40,
		navigation[0].second->getPosition().y);

	navigation[2].second->setPosition(navigation[1].second->getPosition().x - 33,
		navigation[1].second->getPosition().y);
	navigation[2].first->text->setPosition(navigation[2].second->getPosition().x - navigation[2].first->text->getGlobalBounds().width,
		navigation[2].second->getPosition().y + navigation[2].second->getGlobalBounds().height / 2 - navigation[2].first->text->getGlobalBounds().height);
}

bool GameInMenu::exit()
{
	return !active;
}

bool GameInMenu::isActive()
{
	return active;
}

void GameInMenu::drawActive()
{
	buttons[static_cast<int>(*state)]->setEnabled();

	Painter::Instance().addToInterfaceDraw(backgroundRight);

	toControl();

	for (const auto &i : buttons)
	{
		i->Hover();
		i->draw();
	}

	for (const auto &i : navigation)
	{
		Painter::Instance().addToInterfaceDraw(i.first->text);
		Painter::Instance().addToInterfaceDraw(i.second);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
		sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		cooldownChangeStates = 0;
		active = false;
		*state = optionState::Save;
	}
}

void GameInMenu::drawUnactive()
{
	for (const auto &i : buttons)
	{
		i->setDisabled();
		i->draw();
	}

	Painter::Instance().addToInterfaceDraw(backgroundRight);

	centerTextOfOption->text->setPosition(backgroundRight->getPosition().x + 25, backgroundRight->getPosition().y + 25);

	Painter::Instance().addToInterfaceDraw(centerTextOfOption->text);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseClickOnHitbox()))
	{
		active = true;
		isMousePressed = true;
	}
}

void GameInMenu::toControl()
{
	for (size_t i = 0;i < buttons.size();++i)
	{
		if (buttons[i]->getEnabled() == Button::Enabled::False && buttons[i]->mouseOnClick() && !isMousePressed)
		{
			buttons[static_cast<int>(*state)]->setDisabled();
			*state = static_cast<optionState>(i);
			isMousePressed = true;
		}
	}

	if (!cooldownChangeStates && (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
	{
		buttons[static_cast<int>(*state)]->setDisabled();
		if (*state == optionState::Save)
			*state = optionState::Close;
		else
			*state = static_cast<optionState>(static_cast<int>(*state) - 1);

		resetCooldown();
	}

	else if (!cooldownChangeStates && (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
	{
		buttons[static_cast<int>(*state)]->setDisabled();
		if (*state == optionState::Close)
			*state = optionState::Save;
		else
			*state = static_cast<optionState>(static_cast<int>(*state) + 1);

		resetCooldown();
	}

	if (isMousePressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		isMousePressed = false;

	centerTextOfOption->text->setPosition(backgroundRight->getPosition().x + 25, backgroundRight->getPosition().y + 25);

	Painter::Instance().addToInterfaceDraw(centerTextOfOption->text);

	if (cooldownChangeStates && timeChangeStates.time->asSeconds() >= 0.2f)
	{
		cooldownChangeStates = 0;
		timeChangeStates.clock->restart();
		*timeChangeStates.time = sf::Time::Zero;
	}
}

bool GameInMenu::isMouseClickOnHitbox()
{
	if (hitboxClick->getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition())))
		return true;
	return false;
}

void GameInMenu::resetCooldown()
{
	cooldownChangeStates = 1;
	timeChangeStates.clock->restart();
	*timeChangeStates.time = sf::Time::Zero;
}