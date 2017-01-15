#pragma once

#include "SFML\Graphics.hpp"

#include <vector>

#include "Properties.h"
#include "Entity.h"
#include "Field.h"
#include "Camera2D.h"
#include "Textures.h"

class Entity;
class Camera2D;

class RenderBoat : public Field
{
	public:
		RenderBoat();

		~RenderBoat();

		virtual void render();

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;
};