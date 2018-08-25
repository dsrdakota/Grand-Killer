#include "MinimapIcons.hpp"

MinimapIcons::MinimapIcons()
{
	icons = std::vector<MinimapIcon*> {
		new MinimapIcon(MinimapIconType::Player),
		new MinimapIcon(MinimapIconType::Target),
		new MinimapIcon(MinimapIconType::MissionTarget),
	};

	icons[(int)MinimapIconType::Player]->blink = true;
}

MinimapIcons::~MinimapIcons()
{
	for (auto &icon : icons)
		delete icon;
}

std::vector<MinimapIcon*>& MinimapIcons::getIcons()
{
	return icons;
}
