#ifndef LIERO_LEVELPNG_HPP
#define LIERO_LEVELPNG_HPP

#include <vector>
#include <string>
#include <cstdio>
#include <utility>
#include "game.hpp"
#include "gfx.hpp"
#include "gfx/palette.hpp"
#include "material.hpp"
#include "common.hpp"
#include "level.hpp"
#include <gvl/math/vec.hpp>
#include <gvl/math/rect.hpp>

struct Game;
struct Settings;
struct Rand;
struct Common;

struct LevelPng : Level
{
	LevelPng(Common& common, Settings const& settings, std::string const& path)
	: Level(common)
	{
		resize(504, 350);
		bool resetPalette = true;
		uint8_t *pngdata;
		uint32_t width;
		uint32_t height;
		if (!Game::loadPng(path.c_str(), &pngdata, width, height))
		{
			throw std::runtime_error("Could not load png file");
		}
		if (width != 504 || height != 350)
		{
			throw std::runtime_error("PNG has wrong size");
		}
		for (std::size_t i = 0; i < width * height; i++)
		{
			//data[i] = pngdata[i];
			//materials[i] = common.materials[pngdata[i]];
		}
		//origpal.resetPalette(common.exepal, settings);
	}
};

#endif // LIERO_LEVELPNG_HPP
