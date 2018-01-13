#include "mapInMenu.hpp"

#include "../../../../../../../Manager/Texture.hpp"
#include "../../../../../../../Manager/renderSprites.hpp"

mapInMenu::mapInMenu()
{
	textureManager::load("mapInMenu", "data/Map/Minimap/minimap.png");
	map = new sf::RectangleShape;
	player = new sf::CircleShape(5);
	player->setFillColor(sf::Color::Green);
	player->setOrigin(5, 5);

	target = new sf::RectangleShape(sf::Vector2f(10,10));
	target->setOrigin(5,5);
	target->setFillColor(sf::Color(132,0,255));

	for (int i = 0;i < 4;++i)
	{
		sf::RectangleShape *buf = new sf::RectangleShape(sf::Vector2f(1, 10));
		buf->setFillColor(sf::Color::White);
		buf->setOutlineThickness(1);
		buf->setOutlineColor(sf::Color::Black);
		buf->setOrigin(0.5, 0);
		tag.push_back(buf);
	}

	tag[1]->setRotation(90);
	tag[2]->setRotation(180);
	tag[3]->setRotation(270);

	targetIsSet = false;
	canSetTarget = false;

	active = false;
	mapRect = sf::IntRect(0, 0, window->getSize().x, window->getSize().x);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "PUNKT TRASY"), Keyboard::Instance().getKeySprite(Keyboard::Keys::Enter)));
	navigation[0].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "WROC"), Keyboard::Instance().getKeySprite(Keyboard::Keys::Esc)));
	navigation[1].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), Keyboard::Instance().getKeySprite(Keyboard::Keys::D)));
	navigation[2].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), Keyboard::Instance().getKeySprite(Keyboard::Keys::A)));
	navigation[3].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), Keyboard::Instance().getKeySprite(Keyboard::Keys::S)));
	navigation[4].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "PORUSZANIE KAMERA"), Keyboard::Instance().getKeySprite(Keyboard::Keys::W)));
	navigation[5].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), Keyboard::Instance().getKeySprite(Keyboard::Keys::PageDown)));
	navigation[6].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "ZOOM"), Keyboard::Instance().getKeySprite(Keyboard::Keys::PageUp)));
	navigation[7].second->setScale(0.9f, 0.9f);
}

mapInMenu::~mapInMenu()
{
	delete map;
	delete player;

	for (const auto &i : navigation)
	{
		delete i.first;
		delete i.second;
	}

	for (const auto &i : tag)
		delete i;
}

void mapInMenu::setPosition(const sf::Vector2f &menuPos, const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange)
{
	this->menuPos = menuPos;
	if (!active)
	{
		map->setSize(sf::Vector2f(borderXrange.y - borderXrange.x, borderYrange.y - borderYrange.x));
		map->setPosition(borderXrange.x, borderYrange.x);
	}
	else
	{
		map->setSize(sf::Vector2f(borderXrange.y - borderXrange.x, borderYrange.y - borderYrange.x + 50));
		map->setPosition(borderXrange.x, borderYrange.x - 50);
	}

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
	navigation[4].second->setPosition(navigation[3].second->getPosition().x - 33,
		navigation[3].second->getPosition().y);
	navigation[5].second->setPosition(navigation[4].second->getPosition().x - 33,
		navigation[4].second->getPosition().y);
	navigation[5].first->text->setPosition(navigation[5].second->getPosition().x - navigation[5].first->text->getGlobalBounds().width,
		navigation[5].second->getPosition().y + navigation[5].second->getGlobalBounds().height / 2 - navigation[5].first->text->getGlobalBounds().height);

	navigation[6].second->setPosition(navigation[5].first->text->getPosition().x - 40,
		navigation[5].second->getPosition().y);
	navigation[7].second->setPosition(navigation[6].second->getPosition().x - 33,
		navigation[6].second->getPosition().y);
	navigation[7].first->text->setPosition(navigation[7].second->getPosition().x - navigation[7].first->text->getGlobalBounds().width - 5,
		navigation[7].second->getPosition().y + navigation[7].second->getGlobalBounds().height / 2 - navigation[7].first->text->getGlobalBounds().height);

	map->setTexture(dynamic_cast<const sf::Texture*>(textureManager::get("mapInMenu")));
}

bool mapInMenu::exit()
{
	return !active;
}

void mapInMenu::drawActive()
{
	toControl();

	draw();

	for (const auto &i : navigation)
	{
		renderSprites::Instance().addToRender(i.first->text);
		renderSprites::Instance().addToRender(i.second);
	}

	for (const auto &i : tag)
		renderSprites::Instance().addToRender(i);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || (mouseOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Right) && !sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		map->setTexture(dynamic_cast<const sf::Texture*>(textureManager::get("mapInMenu")), true);
		mapRect = sf::IntRect(0, 0, window->getSize().x, window->getSize().y);
		active = false;
	}
}

void mapInMenu::drawUnactive()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || (mouseOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)))
	{
		active = true;
		mapRect = sf::IntRect(static_cast<int>(playerPosition.x - window->getSize().x /2), static_cast<int>(playerPosition.y - window->getSize().y / 2), window->getSize().x, window->getSize().y);
		canSetTarget = false;

		for(const auto &i:tag)
			i->setPosition(menuPos.x + window->getSize().x / 2.f, menuPos.y + window->getSize().y / 2.f);
	}

	draw();
}

void mapInMenu::setPlayerPosition(const sf::Vector2f & pos)
{
	playerPosition = pos;
	setPlayer();
	
	if (targetIsSet)
		setTarget();
}

bool mapInMenu::isActive()
{
	return active;
}

void mapInMenu::toControl()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mapRect.top > 0)
		mapRect.top -= 10;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mapRect.top + mapRect.height< 6000)
		mapRect.top += 10;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && mapRect.left > 0)
		mapRect.left -= 10;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && mapRect.left + mapRect.width < 6000)
		mapRect.left += 10;

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		canSetTarget = true;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && canSetTarget)
	{
		if (targetIsSet)
			targetIsSet = false;
		else if (!targetIsSet)
		{
			targetIsSet = true;

			targetPosition = sf::Vector2f((window->mapPixelToCoords(sf::Mouse::getPosition()).x - map->getPosition().x) * (6000.f / (map->getSize().x * (6000.f / map->getTextureRect().width))) + map->getTextureRect().left,
				(window->mapPixelToCoords(sf::Mouse::getPosition()).y - map->getPosition().y) * (6000.f / (map->getSize().y * (6000.f / map->getTextureRect().height))) + map->getTextureRect().top);
			
			setTarget();
		
		}
		canSetTarget = false;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && canSetTarget)
	{
		if (targetIsSet)
			targetIsSet = false;
		else if (!targetIsSet)
		{
			targetIsSet = true;

			targetPosition = sf::Vector2f((menuPos.x + window->getSize().x / 2 - map->getPosition().x) * (6000.f / (map->getSize().x * (6000.f / map->getTextureRect().width))) + map->getTextureRect().left,
				(menuPos.y + window->getSize().y / 2 - map->getPosition().y) * (6000.f / (map->getSize().y * (6000.f / map->getTextureRect().height))) + map->getTextureRect().top);

			setTarget();

		}
		canSetTarget = false;
	}

	if ((*Game::getScrollValue() > 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) && mapRect.width > static_cast<int>(window->getSize().x) && mapRect.height > static_cast<int>(window->getSize().y))
	{
		mapRect.height -= 40;
		mapRect.width -= 40;
		if (mapRect.top + mapRect.height < 6000)
			mapRect.top += 20;
		if(mapRect.left + mapRect.width < 6000)
			mapRect.left += 20;
	}
	else if((*Game::getScrollValue() < 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) && mapRect.width < 6000 && mapRect.height < 6000)
	{
		mapRect.height += 40;
		mapRect.width += 40;

		if (mapRect.top + mapRect.height < 6000 && mapRect.top > 0)
			mapRect.top -= 20;
		else if (mapRect.top > 0)
			mapRect.top -= 40;

		if (mapRect.left + mapRect.width < 6000 && mapRect.left > 0)
			mapRect.left -= 20;
		else if (mapRect.left > 0)
			mapRect.left -= 40;
	}
	*Game::getScrollValue() = 0;
	map->setTextureRect(mapRect);
}

bool mapInMenu::mouseOnMap()
{
	if (map->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition())))
		return true;
	return false;
}

void mapInMenu::draw()
{
	renderSprites::Instance().addToRender(map);
	renderSprites::Instance().addToRender(player);

	if (targetIsSet)
		renderSprites::Instance().addToRender(target);
}

void mapInMenu::setPlayer()
{
	player->setPosition(map->getPosition().x + (playerPosition.x * (map->getSize().x * (6000.f / map->getTextureRect().width) / 6000.f)) - (mapRect.left * (map->getSize().x * (6000.f / map->getTextureRect().width) / 6000.f)),
		map->getPosition().y + (playerPosition.y * (map->getSize().y * (6000.f / map->getTextureRect().height) / 6000.f)) - (mapRect.top * (map->getSize().y * (6000.f / map->getTextureRect().height) / 6000.f)));
}

void mapInMenu::setTarget()
{
	target->setPosition(targetPosition.x * (map->getSize().x * (6000.f / map->getTextureRect().width) / 6000.f) + map->getPosition().x - (mapRect.left * (map->getSize().x * (6000.f / map->getTextureRect().width) / 6000.f)),
		targetPosition.y * (map->getSize().y * (6000.f / map->getTextureRect().height) / 6000.f) + map->getPosition().y - (mapRect.top * (map->getSize().y * (6000.f / map->getTextureRect().height) / 6000.f)));
}
