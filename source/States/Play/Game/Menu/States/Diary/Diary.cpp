#include "Diary.hpp"

Diary::Diary()
{
	buttons.push_back(new Button(sf::Vector2f(225, 30), 15, "Misja"));
	buttons.push_back(new Button(sf::Vector2f(225, 30), 15, "Pomoc"));
	buttons.push_back(new Button(sf::Vector2f(225, 30), 15, "Dialog"));

	hitboxClick = new sf::RectangleShape;
	backgroundRight = new sf::RectangleShape;
	backgroundRight->setFillColor(buttons[0]->getButtonSprite()->getFillColor());

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "WROC"), KeysManager::Instance().getKeySprite(KeysManager::Keys::Esc)));
	navigation[0].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), KeysManager::Instance().getKeySprite(KeysManager::Keys::S)));
	navigation[1].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "PRZEWIJANIE"), KeysManager::Instance().getKeySprite(KeysManager::Keys::W)));
	navigation[2].second->setScale(0.9f, 0.9f);

	state = new optionState(optionState::Mission);

	cooldownChangeStates = 1;

	active = false;
	isMousePressed = false;

	centerTextOfOption.push_back(std::make_pair(new Text(sf::Color::White, 70, "Misja"), new Text(sf::Color::White, 16, "Obecnie nie rozgrywasz misji. Podczas misji beda tu wyswietlane\ninformacje na temat twoich postepow i aktualnych celow.")));
	centerTextOfOption.push_back(std::make_pair(new Text(sf::Color::White, 70, "Pomoc"), new Text(sf::Color::White, 16, "Zagladaj tutaj, by przejrzec teksty pomocnicze wyswietlane w grze.")));
	centerTextOfOption.push_back(std::make_pair(new Text(sf::Color::White, 70, "Dialog"), new Text(sf::Color::White, 16, "Zagladaj tu, aby przypomniec sobie przebieg rozmow.")));
}

Diary::~Diary()
{
	delete state;

	for (const auto &i : buttons)
		delete i;

	for (const auto &i : navigation)
	{
		delete i.first;
		delete i.second;
	}

	for (const auto &i : centerTextOfOption)
	{
		delete i.first;
		delete i.second;
	}
}

void Diary::setPosition(const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange)
{
	hitboxClick->setSize(sf::Vector2f(borderXrange.y - borderXrange.x, borderYrange.y - borderYrange.x));
	hitboxClick->setPosition(borderXrange.x,borderYrange.x);

	backgroundRight->setSize(sf::Vector2f(hitboxClick->getSize().x - buttons[0]->getButtonSprite()->getSize().x, hitboxClick->getSize().y));

	buttons[0]->setPosition(sf::Vector2f(borderXrange.x, borderYrange.x));
	buttons[1]->setPosition(sf::Vector2f(borderXrange.x, buttons[0]->getButtonSprite()->getPosition().y + buttons[0]->getButtonSprite()->getGlobalBounds().height + 3.f));
	buttons[2]->setPosition(sf::Vector2f(borderXrange.x, buttons[1]->getButtonSprite()->getPosition().y + buttons[1]->getButtonSprite()->getGlobalBounds().height + 3.f));

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
	
	*state = optionState::Mission;
}

bool Diary::exit()
{
	return !active;
}

bool Diary::isActive()
{
	return active;
}

void Diary::drawActive()
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
	}
}

void Diary::drawUnactive()
{
	for (const auto &i : buttons)
	{
		i->setDisabled();
		i->draw();
	}

	Painter::Instance().addToInterfaceDraw(backgroundRight);

	centerTextOfOption[0].first->text->setPosition(backgroundRight->getPosition().x + 25, backgroundRight->getPosition().y + 25);

	centerTextOfOption[0].second->text->setPosition(centerTextOfOption[0].first->text->getPosition().x,
		centerTextOfOption[0].first->text->getPosition().y + /*centerTextOfOption[index].first->text->getGlobalBounds().height*/ 50 + 50);

	Painter::Instance().addToInterfaceDraw(centerTextOfOption[static_cast<int>(*state)].first->text);
	Painter::Instance().addToInterfaceDraw(centerTextOfOption[static_cast<int>(*state)].second->text);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseClickOnHitbox()))
	{
		active = true;
		isMousePressed = true;
	}
}

void Diary::toControl()
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
		if (*state == optionState::Mission)
			*state = optionState::Dialog;
		else
			*state = static_cast<optionState>(static_cast<int>(*state) - 1);

		resetCooldown();
	}

	else if (!cooldownChangeStates && (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
	{
		buttons[static_cast<int>(*state)]->setDisabled();
		if (*state == optionState::Dialog)
			*state = optionState::Mission;
		else
			*state = static_cast<optionState>(static_cast<int>(*state) + 1);

		resetCooldown();
	}

	if (isMousePressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		isMousePressed = false;

	size_t index = static_cast<size_t>(*state);
	centerTextOfOption[index].first->text->setPosition(backgroundRight->getPosition().x + 25, backgroundRight->getPosition().y + 25);

	centerTextOfOption[index].second->text->setPosition(centerTextOfOption[index].first->text->getPosition().x,
		centerTextOfOption[index].first->text->getPosition().y + /*centerTextOfOption[index].first->text->getGlobalBounds().height*/ 50 + 50);

	Painter::Instance().addToInterfaceDraw(centerTextOfOption[index].first->text);
	Painter::Instance().addToInterfaceDraw(centerTextOfOption[index].second->text);

	if (cooldownChangeStates && timeChangeStates.time->asSeconds() >= 0.2f)
	{
		cooldownChangeStates = 0;
		timeChangeStates.clock->restart();
		*timeChangeStates.time = sf::Time::Zero;
	}
}

bool Diary::isMouseClickOnHitbox()
{
	if (hitboxClick->getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition())))
		return true;
	return false;
}

void Diary::resetCooldown()
{
	cooldownChangeStates = 1;
	timeChangeStates.clock->restart();
	*timeChangeStates.time = sf::Time::Zero;
}
