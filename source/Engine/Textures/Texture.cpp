#include "Texture.hpp"

TextureManager::~TextureManager()
{
	for (auto data : textures)
		delete data.second;
}

sf::Texture * TextureManager::load(const std::string & textureName, const std::string & texturePath)
{

	sf::Texture* result = new sf::Texture;

	if (!result->loadFromFile(texturePath))
		return nullptr;

	result->setSmooth(true);

	Instance().textures[textureName] = result;

	return result;
}

bool TextureManager::unload(const std::string & textureName)
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

std::size_t TextureManager::cleanUp()
{
	auto &instance = Instance();

	std::size_t textureCount = instance.textures.size();

	for (auto textureData : instance.textures)
		delete (textureData.second);

	return textureCount;
}

sf::Texture * TextureManager::get(const std::string & textureName)
{
	auto &instance = Instance();

	auto textureIt = instance.textures.find(textureName);

	if (textureIt == instance.textures.end())
		return nullptr;

	return textureIt->second;
}