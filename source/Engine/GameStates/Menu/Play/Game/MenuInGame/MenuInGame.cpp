#include "MenuInGame.hpp"

#include "../../../../../../Manager/Texture.hpp"
#include "../../../../../../Manager/renderSprites.hpp"

MenuInGame::MenuInGame(const sf::Vector2u &windowSize) : window(Game::Instance().getWindow())
{
	state = new States(States::Map);

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

	headersButton[0]->setEnabled();

	// set WSK

	cooldownEscapeButton = 0;
	cooldownChangeStates = 1;
}

MenuInGame::~MenuInGame()
{
	delete leftArrow;
	delete rightArrow;
	delete grandKillerText;
	delete background;
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

void MenuInGame::setPosition(const sf::Vector2f & menuPos)
{
	background->setPosition(menuPos);

	grandKillerText->text->setPosition(menuPos.x + window->getSize().x *0.2f, menuPos.y + window->getSize().y * 0.1f);

	leftArrow->setPosition(grandKillerText->text->getPosition().x - leftArrow->getGlobalBounds().width - 5, grandKillerText->text->getPosition().y + grandKillerText->text->getGlobalBounds().height + leftArrow->getGlobalBounds().height + 10.f);

	headersButton[0]->setPosition(sf::Vector2f(grandKillerText->text->getPosition().x, leftArrow->getPosition().y - 2.5f));

	for(size_t i=1;i<headersButton.size();++i)
		headersButton[i]->setPosition(sf::Vector2f(headersButton[i-1]->getButtonSprite()->getPosition().x + headersButton[i - 1]->getButtonSprite()->getGlobalBounds().width + 2,
			leftArrow->getPosition().y - 2.5f));

	rightArrow->setPosition(headersButton[headersButton.size() - 1]->getButtonSprite()->getPosition().x + headersButton[headersButton.size() - 1]->getButtonSprite()->getGlobalBounds().width + 5.f,
		leftArrow->getPosition().y);
}

const int & MenuInGame::getCooldownValue()
{
	return cooldownEscapeButton;
}

void MenuInGame::draw()
{
	update();
	
	renderSprites::Instance().addToRender(background);
	renderSprites::Instance().addToRender(grandKillerText->text);
	renderSprites::Instance().addToRender(leftArrow);
	renderSprites::Instance().addToRender(rightArrow);
	
	for (const auto &i : headersButton)
		i->draw();
}

void MenuInGame::update()
{
	checkArrowIsPressed(1); // right
	checkArrowIsPressed(-1); // left

	for (size_t i = 0;i<headersButton.size();++i)
	{
		if (headersButton[i]->isHover() && headersButton[i]->mouseOnClick())
		{
			headersButton[static_cast<int>(*state)]->setDisabled();

			*state = static_cast<States>(i);

			headersButton[static_cast<int>(*state)]->setEnabled();

			//change WSK
		}
	}
}

void MenuInGame::checkArrowIsPressed(const int &side)
{
	States first, last;
	sf::Keyboard::Key keyFirst, keySecond; // left arrow or right; A or D
	sf::Sprite *arrowSide;

	if (side == 1) // right
	{
		first = States::Game;
		last = States::Map;
		keyFirst = sf::Keyboard::Right;
		keySecond = sf::Keyboard::D;
		arrowSide = rightArrow;
	}
	else // left
	{
		first = States::Map;
		last = States::Game;
		keyFirst = sf::Keyboard::Left;
		keySecond = sf::Keyboard::A;
		arrowSide = leftArrow;
	}

	if (!cooldownChangeStates && (mouseOnClickArrow(arrowSide) ||
		sf::Keyboard::isKeyPressed(keyFirst) ||
		sf::Keyboard::isKeyPressed(keySecond)))
	{
		headersButton[static_cast<int>(*state)]->setDisabled();

		if (*state == first)
		{
			*state = last;
			// change WSK
		}
		else
		{
			*state = static_cast<States>(static_cast<int>(*state) + side);
			// change WSK
		}
		cooldownChangeStates = 1;
		timeChangeStates.clock->restart();
		*timeChangeStates.time = sf::Time::Zero;
		headersButton[static_cast<int>(*state)]->setEnabled();
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
