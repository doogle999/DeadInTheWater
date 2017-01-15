#pragma once

#include "SFML\Graphics.hpp"

#include <array>

class Textures
{
	public:
		enum Ids
		{
			Boat,
			META_TEXTURE_COUNT
		};

		static sf::Texture& get(Textures::Ids id);

		static void load();
		static void unload();
		
	private:
		static std::array<sf::Texture*, META_TEXTURE_COUNT> textures;
};