#include "levellev.hpp"

#include "game.hpp"
#include "gfx.hpp"
#include "gfx/color.hpp"
#include "filesystem.hpp"

#include <cstring>

void LevelLev::resetPalette(Common &common, Settings const &settings)
{
	origpal.resetPalette(common.exepal, settings);
}

void LevelLev::resize(int width_new, int height_new)
{
	width = width_new;
	height = height_new;
	data.resize(width * height);
	materials.resize(width * height);
}

PalIdx& LevelLev::palette() {
	return data[0];
}

Palette LevelLev::originalPalette() {
	return origpal;
}