#ifndef LIERO_LEVEL_HPP
#define LIERO_LEVEL_HPP

#include <vector>
#include <string>
#include <cstdio>
#include <utility>
#include "gfx/palette.hpp"
#include "material.hpp"
#include "common.hpp"
#include <gvl/math/vec.hpp>
#include <gvl/math/rect.hpp>
#include "filesystem.hpp"
#include "settings.hpp"

struct Game;
struct Rand;
struct Common;

struct Level
{
protected:
	Level(Common& common)
	: width(0)
	, height(0)
	{
		zeroMaterial = common.materials[0];
	}
public:
	static Level *createFromFile(Common& common, Settings const& settings, std::string const& path);
	static Level *generateFromSettings(Common& common, Settings const& settings, Rand& rand);

	void generateDirtPattern(Common& common, Rand& rand);
	void generateRandom(Common& common, Settings const& settings, Rand& rand);
	void makeShadow(Common& common);
	bool selectSpawn(Rand& rand, int w, int h, gvl::ivec2& selected);
	void drawMiniature(Bitmap& dest, int mapX, int mapY, int step);

	virtual void resetPalette(Common &common, Settings const &settings) = 0;
		
	virtual unsigned char pixel(int x, int y) = 0;

	virtual unsigned char pixel(fixedvec pos) = 0;

	virtual unsigned char* pixelp(int x, int y) = 0;

	virtual void setPixel(int x, int y, PalIdx w, Common& common) = 0;

	virtual void setPixel(fixedvec pos, PalIdx w, Common& common) = 0;

	virtual Material& mat(int x, int y) = 0;

	virtual Material& mat(fixedvec pos) = 0;

	virtual Material* matp(int x, int y) = 0;
	
	virtual unsigned char checkedPixelWrap(int x, int y) = 0;

	virtual Material checkedMatWrap(int x, int y) = 0;

	virtual void resize(int width_new, int height_new) = 0;

	virtual PalIdx &palette() = 0;

	virtual Palette originalPalette() = 0;

	bool inside(int x, int y)
	{
		return static_cast<unsigned int>(x) < static_cast<unsigned int>(width)
		    && static_cast<unsigned int>(y) < static_cast<unsigned int>(height);
	}

	bool inside(fixedvec pos)
	{
		return static_cast<unsigned int>(pos.x) < static_cast<unsigned int>(width)
		    && static_cast<unsigned int>(pos.y) < static_cast<unsigned int>(height);
	}
	
	gvl::rect rect()
	{
		return gvl::rect(0, 0, width, height);
	}
	
	Material zeroMaterial;
	int width, height;
	bool oldRandomLevel;
	std::string oldLevelFile;
};

#endif // LIERO_LEVEL_HPP
