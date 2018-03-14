#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

class GlobalSteerage
{
public:

	~GlobalSteerage();

	GlobalSteerage(const GlobalSteerage &) = delete;
	void operator=(const GlobalSteerage &) = delete;

	inline static GlobalSteerage& Instance()
	{
		static GlobalSteerage steerage;
		return steerage;
	}

	enum class Sections
	{
		Car,
		Walk,
		Fight,
		Guns
	};

	enum class Rodzaj
	{
		Gas,
		Break,
		HandBreak,
		TurnLeft,
		TurnRight
	};

	static const sf::Keyboard::Key &getKey(const Sections &section, const Rodzaj &rodzaj);

private:

	GlobalSteerage();

	void loadDefaultCarSteerage();
	void loadDefaultWalkSteerage();
	void loadDefaultFightSteerage();
	void loadDefaultGunsSteerage();

	std::unordered_map<Sections, std::unordered_map<Rodzaj, sf::Keyboard::Key>> steerage;
};