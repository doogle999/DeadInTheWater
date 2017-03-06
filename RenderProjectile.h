#pragma once

#include "SFML\Graphics.hpp"

#include <vector>

#include "Entity.h"
#include "Field.h"
#include "Camera2D.h"
#include "Textures.h"

class Entity;
class Camera2D;

class RenderProjectile : public Field
{
	public:
		RenderProjectile();

		~RenderProjectile();

		virtual void render();

		virtual std::vector<Attribute::Ids> getNecessaryProperties();

	private:
		static const std::vector<Attribute::Ids> necessaryProperties;
};