#ifndef LIERO_LEVELLEV_HPP
#define LIERO_LEVELLEV_HPP

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
#include "level.hpp"

struct Game;
struct Rand;
struct Common;

struct LevelLev : Level
{
public:
	LevelLev(Common& common)
	: Level(common)
	{
	}

	LevelLev(Common& common, Settings const& settings, gvl::octet_reader r)
	: Level(common)
	{
		resize(504, 350);

		//std::size_t len = f.len;
		bool resetPalette = true;

		r.get(reinterpret_cast<uint8_t*>(&data[0]), width * height);

		if (settings.extensions && settings.loadPowerlevelPalette)
		{
			uint8_t buf[10];
			if (r.try_get(buf, 10))
			{
				if (!std::memcmp("POWERLEVEL", buf, 10))
				{
					Palette pal;
					pal.read(r);
					origpal.resetPalette(pal, settings);

					resetPalette = false;
				}
			}
		}

		for (std::size_t i = 0; i < data.size(); ++i)
			materials[i] = common.materials[data[i]];

		if (resetPalette)
			origpal.resetPalette(common.exepal, settings);
	}

	void resetPalette(Common &common, Settings const &settings);
	void resize(int width_new, int height_new);
	PalIdx &palette();
	Palette originalPalette();
		
	unsigned char pixel(int x, int y)
	{
		return data[x + y*width];
	}

	unsigned char pixel(fixedvec pos)
	{
		return data[pos.x + pos.y*width];
	}

	unsigned char* pixelp(int x, int y)
	{
		return &data[x + y*width];
	}

	void setPixel(int x, int y, PalIdx w, Common& common)
	{
		data[x + y*width] = w;
		materials[x + y*width] = common.materials[w];
	}

	void setPixel(fixedvec pos, PalIdx w, Common& common)
	{
		data[pos.x + pos.y*width] = w;
		materials[pos.x + pos.y*width] = common.materials[w];
	}

	Material& mat(int x, int y)
	{
		return materials[x + y*width];
	}

	Material& mat(fixedvec pos)
	{
		return materials[pos.x + pos.y*width];
	}

	Material* matp(int x, int y)
	{
		return &materials[x + y*width];
	}
	
	unsigned char checkedPixelWrap(int x, int y)
	{
		unsigned int idx = static_cast<unsigned int>(x + y*width);
		if(idx < data.size())
			return data[idx];
		return 0;
	}

	Material checkedMatWrap(int x, int y)
	{
		unsigned int idx = static_cast<unsigned int>(x + y*width);
		if(idx < materials.size())
			return materials[idx];
		return zeroMaterial;
	}
	
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

	std::vector<unsigned char> data;
	std::vector<Material> materials;
	
	Palette origpal;
};

#endif // LIERO_LEVELLEV_HPP
