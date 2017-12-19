#include "Sound.hpp"

soundManager::~soundManager()
{
	for (auto data : sounds)
		delete data.second;
}

sf::SoundBuffer * soundManager::load(const std::string & soundName, const std::string & soundPath)
{
	sf::SoundBuffer *result = soundManager::get(soundName);

	if (result)
		result->loadFromFile(soundPath);

	else
	{
		result = new sf::SoundBuffer();

		result->loadFromFile(soundPath);

		Instance().sounds[soundName] = result;
	}

	return result;
}

bool soundManager::unload(const std::string & soundName)
{
	auto &instance = Instance();

	auto textureIt = instance.sounds.find(soundName);

	if (textureIt != instance.sounds.end())
	{
		delete (textureIt->second);

		instance.sounds.erase(textureIt);

		return true;
	}
	return false;
}

std::size_t soundManager::cleanUp()
{
	auto &instance = Instance();

	std::size_t soundCount = instance.sounds.size();

	for (auto soundData : instance.sounds)
		delete (soundData.second);

	return soundCount;
}

sf::SoundBuffer * soundManager::get(const std::string & soundName)
{
	auto &instance = Instance();

	auto soundIt = instance.sounds.find(soundName);

	if (soundIt == instance.sounds.end())
		return nullptr;

	return soundIt->second;
}