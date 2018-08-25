#include "Texture.hpp"

TextureManager::~TextureManager()
{
	for (auto data : textures)
		delete data.second;
}

void TextureManager::save(sf::Texture * texture, const std::string & textureName)
{
	Instance().textures[textureName] = texture;
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
	auto textureIt = Instance().textures.find(textureName);

	if (textureIt != Instance().textures.end())
	{
		delete (textureIt->second);

		Instance().textures.erase(textureIt);

		return true;
	}
	return false;
}

std::size_t TextureManager::cleanUp()
{
	std::size_t textureCount = Instance().textures.size();

	for (auto textureData : Instance().textures)
		delete (textureData.second);

	return textureCount;
}

sf::Texture * TextureManager::get(const std::string & textureName)
{
	auto textureIt = Instance().textures.find(textureName);

	if (textureIt == Instance().textures.end())
		return nullptr;

	return textureIt->second;
}