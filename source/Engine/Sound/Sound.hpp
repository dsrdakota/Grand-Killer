#pragma once

#include <SFML/Audio.hpp>

#include <unordered_map>

class soundManager
{
public:
	~soundManager();

	void operator=(const soundManager &Other) = delete;

	static sf::SoundBuffer* load(const std::string &soundName, const std::string &soundPath);

	static bool unload(const std::string &soundName);

	static std::size_t cleanUp();

	static sf::SoundBuffer* get(const std::string &soundName);

	inline static bool Exists(const std::string &soundName) { return soundManager::get(soundName) != nullptr; }

private:

	soundManager() {};

	inline static soundManager& Instance()
	{
		static soundManager instance;
		return instance;
	}

	std::unordered_map<std::string, sf::SoundBuffer*>sounds;
};