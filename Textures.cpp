#include "Textures.h"

std::array<sf::Texture*, Textures::Ids::META_TEXTURE_COUNT> Textures::textures;

sf::Texture& Textures::get(Textures::Ids id)
{
	return *textures.at(id);
}

void Textures::load()
{
	textures[Textures::Ids::Boat] = new sf::Texture();
	textures[Textures::Ids::Boat]->create(32, 16);
	textures[Textures::Ids::Boat]->loadFromFile("Textures\\Boat.png");
}
void Textures::unload()
{
	for(unsigned int i = 0; i < textures.size(); i++)
	{
		delete textures[i];
	}
}