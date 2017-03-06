#pragma once

#include <vector>

#include "Entity.h"
#include "Field.h"
#include "Fields.h"
#include "Controller.h"

class Entity;

class Player : public Field // Handles the switching and calls to controllers
{
	public:
		Player();

		~Player();

		virtual void input();

		virtual std::vector<Attribute::Ids> getNecessaryProperties();

	private:
		Fields::Ids currentController; 
};