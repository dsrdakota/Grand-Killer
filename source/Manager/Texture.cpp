#include "Texture.hpp"

textureManager::~textureManager()
{
	for (auto data : textures)
		delete data.second;
}

sf::Texture * textureManager::load(const std::string & textureName, const std::string & texturePath)
{
	sf::Texture *result = textureManager::get(textureName);

	if (result)
		result->loadFromFile(texturePath);

	else
	{
		result = new sf::Texture();

		result->loadFromFile(texturePath);

		Instance().textures[textureName] = result;
	}

	return result;
}

bool textureManager::unload(const std::string & textureName)
{
	auto &instance = Instance();

	auto textureIt = instance.textures.find(textureName);

	if (textureIt != instance.textures.end())
	{
		delete (textureIt->second);

		instance.textures.erase(textureIt);

		return true;
	}
	return false;
}

std::size_t textureManager::cleanUp()
{
	auto &instance = Instance();

	std::size_t textureCount = instance.textures.size();

	for (auto textureData : instance.textures)
		delete (textureData.second);

	return textureCount;
}

sf::Texture * textureManager::get(const std::string & textureName)
{
	auto &instance = Instance();

	auto textureIt = instance.textures.find(textureName);

	if (textureIt == instance.textures.end())
		return nullptr;

	return textureIt->second;
}
