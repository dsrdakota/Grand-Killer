#include "MenuInGame.hpp"

#include "../../../../../../Manager/Texture.hpp"
#include "../../../../../../Manager/renderSprites.hpp"

MenuInGame::MenuInGame(const sf::Vector2u &windowSize) : window(Game::Instance().getWindow())
{
	state = new States(States::Mapa);

	background = new sf::RectangleShape(static_cast<sf::Vector2f>(window->getSize()));
	background->setFillColor(sf::Color(1, 36, 3, 220));

	grandKillerText = new Text(sf::Color::White, 50, "Grand Killer", "data/Font/italic.ttf");

	leftArrow = new sf::Sprite(*textureManager::load("leftArrow","data/Game/MenuInGame/leftArrow.png"));
	rightArrow = new sf::Sprite(*textureManager::load("rightArrow", "data/Game/MenuInGame/rightArrow.png"));

	headersButton.push_back(new Button(sf::Vector2f((window->getSize().x - window->getSize().x * 0.4f) / 5.f, leftArrow->getGlobalBounds().height + 8.f), 15, "MAPA", Button::State::header));
	headersButton.push_back(new Button(sf::Vector2f((window->getSize().x - window->getSize().x * 0.4f) / 5.f, leftArrow->getGlobalBounds().height + 8.f), 15, "DZIENNIK", Button::State::header));
	headersButton.push_back(new Button(sf::Vector2f((window->getSize().x - window->getSize().x * 0.4f) / 5.f, leftArrow->getGlobalBounds().height + 8.f), 15, "STATYSTYKI", Button::State::header));
	headersButton.push_back(new Button(sf::Vector2f((window->getSize().x - window->getSize().x * 0.4f) / 5.f, leftArrow->getGlobalBounds().height + 8.f), 15, "USTAWIENIA", Button::State::header));
	headersButton.push_back(new Button(sf::Vector2f((window->getSize().x - window->getSize().x * 0.4f) / 5.f, leftArrow->getGlobalBounds().height + 8.f), 15, "GRA", Button::State::header));

	map = new mapInMenu;
	options.push_back(map);
	options.push_back(new Diary()); 
	options.push_back(new Statistics()); 
	options.push_back(new Steerage()); 
	options.push_back(new gameInMenu()); 

	headersButton[0]->setEnabled();

	wsk = options[static_cast<int>(States::Mapa)];

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "WYBIERZ"), Keyboard::Instance().getKeySprite(Keyboard::Keys::Enter)));
	navigation[0].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "WROC"), Keyboard::Instance().getKeySprite(Keyboard::Keys::Esc)));
	navigation[1].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), Keyboard::Instance().getKeySprite(Keyboard::Keys::E)));
	navigation[2].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "PRZEWIJANIE"), Keyboard::Instance().getKeySprite(Keyboard::Keys::Q)));
	navigation[3].second->setScale(0.9f, 0.9f);

	cooldownEscapeButton = 0;
	cooldownChangeStates = 1;
	mapActive = false;
	optionsAreActive = false;
	escapeWasRelased = true;
}

MenuInGame::~MenuInGame()
{
	delete leftArrow;
	delete rightArrow;
	delete grandKillerText;
	delete background;

	for (const auto &i : options)
		delete i;

	for (const auto &i : navigation)
	{
		delete i.first;
		delete i.second;
	}
}

void MenuInGame::updateCooldown()
{
	if (cooldownEscapeButton && timeEscapeButton.time->asSeconds() >= 1.f)
	{
		cooldownEscapeButton--;
		timeEscapeButton.clock->restart();
		*timeEscapeButton.time = sf::Time::Zero;
	}

	if(cooldownChangeStates && timeChangeStates.time->asSeconds() >=0.2f)
	{
		cooldownChangeStates = 0;
		timeChangeStates.clock->restart();
		*timeChangeStates.time = sf::Time::Zero;
	}
}

void MenuInGame::restartCooldownValue()
{
	cooldownEscapeButton = 2;
	timeEscapeButton.clock->restart();
	*timeEscapeButton.time = sf::Time::Zero;
}

void MenuInGame::setPosition(const sf::Vector2f & menuPos, const sf::Vector2f &playerPos)
{
	background->setPosition(menuPos);
	this->playerPos = playerPos;

	grandKillerText->text->setPosition(menuPos.x + window->getSize().x *0.2f, menuPos.y + window->getSize().y * 0.1f);

	leftArrow->setPosition(grandKillerText->text->getPosition().x - leftArrow->getGlobalBounds().width - 5, grandKillerText->text->getPosition().y + grandKillerText->text->getGlobalBounds().height + leftArrow->getGlobalBounds().height + 10.f);

	headersButton[0]->setPosition(sf::Vector2f(grandKillerText->text->getPosition().x, leftArrow->getPosition().y - 2.5f));

	for(size_t i=1;i<headersButton.size();++i)
		headersButton[i]->setPosition(sf::Vector2f(headersButton[i-1]->getButtonSprite()->getPosition().x + headersButton[i - 1]->getButtonSprite()->getGlobalBounds().width + 2,
			leftArrow->getPosition().y - 2.5f));

	rightArrow->setPosition(headersButton[headersButton.size() - 1]->getButtonSprite()->getPosition().x + headersButton[headersButton.size() - 1]->getButtonSprite()->getGlobalBounds().width + 5.f,
		leftArrow->getPosition().y);

	navigation[0].second->setPosition(menuPos.x + window->getSize().x - navigation[0].second->getGlobalBounds().width - 40,
		menuPos.y + window->getSize().y - navigation[0].second->getGlobalBounds().height - 15);
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
}

const int & MenuInGame::getCooldownValue()
{
	return cooldownEscapeButton;
}

bool MenuInGame::canExitMenu()
{
	return escapeWasRelased && wsk->exit();
}

void MenuInGame::draw()
{
	update();
	
	renderSprites::Instance().addToRender(background);
	renderSprites::Instance().addToRender(grandKillerText->text);

	if (!(wsk == options[static_cast<int>(States::Mapa)] && mapActive))
	{
		renderSprites::Instance().addToRender(leftArrow);
		renderSprites::Instance().addToRender(rightArrow);
		for (const auto &i : headersButton)
			i->draw();
	}

	if (optionsAreActive || mapActive)
		wsk->drawActive();
	else
	{
		for (const auto &i : navigation)
		{
			renderSprites::Instance().addToRender(i.first->text);
			renderSprites::Instance().addToRender(i.second);
		}
		wsk->drawUnactive();
	}
}

void MenuInGame::update()
{
	auto firstButton = headersButton[0]->getButtonSprite();

	wsk->setPosition(background->getPosition(),sf::Vector2f(firstButton->getPosition().x,
		firstButton->getPosition().x + window->getSize().x * 0.8f - window->getSize().x * 0.2f),
		sf::Vector2f(firstButton->getPosition().y + firstButton->getGlobalBounds().height + 10,
			firstButton->getPosition().y + firstButton->getGlobalBounds().height + window->getSize().y * 0.6f));

	if (*state == States::Mapa)
	{
		map->setPlayerPosition(playerPos);
		mapActive = map->isActive();
	}

	if (!wsk->exit())
		escapeWasRelased = false;

	if (!mapActive)
	{
		if (!escapeWasRelased && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
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

void MenuInGame::checkArrowIsPressed(const int &side)
{
	States first, last;
	sf::Keyboard::Key key; // Q or E
	sf::Sprite *arrowSide;

	if (side == 1) // right
	{
		first = States::Gra;
		last = States::Mapa;
		key = sf::Keyboard::E;
		arrowSide = rightArrow;
	}
	else // left
	{
		first = States::Mapa;
		last = States::Gra;
		key = sf::Keyboard::Q;
		arrowSide = leftArrow;
	}

	if (!cooldownChangeStates && (mouseOnClickArrow(arrowSide) ||
		sf::Keyboard::isKeyPressed(key)))
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

bool MenuInGame::mouseOnClickArrow(sf::Sprite * arrow)
{
	if (mouseOnArrow(arrow) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}

bool MenuInGame::mouseOnArrow(sf::Sprite * arrow)
{
	if (arrow->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition())))
	{
		arrow->setScale(sf::Vector2f(1.1f, 1.1f));
		return true;
	}
	else
		arrow->setScale(sf::Vector2f(1.f, 1.f));
	return false;
}
