#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

class TextureManager
{
public:
	~TextureManager();

	TextureManager(const TextureManager &) = delete;

	void operator=(const TextureManager &) = delete;

	static void save(sf::Texture* texture, const std::string &textureName);

	static sf::Texture* load(const std::string &textureName, const std::string &texturePath);

	static bool unload(const std::string &textureName);

	static std::size_t cleanUp();

	static sf::Texture* get(const std::string &textureName);

	inline static bool Exists(const std::string &textureName) { return TextureManager::get(textureName) != nullptr; }

private:

	TextureManager() {};

	inline static TextureManager& Instance()
	{
		static TextureManager instance;
		return instance;
	}

	std::unordered_map<std::string,sf::Texture*> textures;
};