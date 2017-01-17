#include "Textures.h"

#define ADD_PATH(NAME) textures[Textures::Ids:: ## NAME] = new sf::Texture(); textures[Textures::Ids:: ## NAME]->loadFromFile("Textures\\" ## #NAME ##".png");

std::array<sf::Texture*, Textures::Ids::META_TEXTURE_COUNT> Textures::textures;

sf::Texture& Textures::get(Textures::Ids id)
{
	return *textures.at(id);
}

void Textures::load()
{
	ADD_PATH(Boat)
	ADD_PATH(Projectile)
}
void Textures::unload()
{
	for(unsigned int i = 0; i < textures.size(); i++)
	{
		delete textures[i];
	}
}

#undef ADD_PATH