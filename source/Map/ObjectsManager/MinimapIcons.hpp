#pragma once

#include <SFML/Graphics.hpp>

#include "../Objects/MinimapIcon.hpp"

class MinimapIcons
{
public:

	~MinimapIcons();

	MinimapIcons(const MinimapIcons &) = delete;
	void operator=(const MinimapIcons &) = delete;

	inline static MinimapIcons& Instance()
	{
		static MinimapIcons minimapIcons;
		return minimapIcons;
	}

	std::vector<MinimapIcon*> &getIcons();

private:

	MinimapIcons();

	std::vector<MinimapIcon*> icons;
};