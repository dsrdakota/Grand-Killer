#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

class textureManager
{
public:
	~textureManager();

	textureManager(const textureManager &Other) = delete;

	void operator=(const textureManager &Other) = delete;

	static sf::Texture* load(const std::string &textureName, const std::string &texturePath);

	static bool unload(const std::string &textureName);

	static std::size_t cleanUp();

	static sf::Texture* get(const std::string &textureName);

	inline static bool Exists(const std::string &textureName) { return textureManager::get(textureName) != nullptr; }

private:

	textureManager() {};

	inline static textureManager& Instance()
	{
		static textureManager instance;
		return instance;
	}

	std::unordered_map<std::string,sf::Texture*> textures;
};