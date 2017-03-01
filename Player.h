#pragma once

#include <vector>

#include "Properties.h"
#include "Entity.h"
#include "Field.h"
#include "Fields.h"
#include "Controller.h"

class Entity;

class Player : public Field // Handles the switching and calls to controllers
{
	public:
		Player();
		Player(const Player& p);

		~Player();

		Player& operator=(Player p);

		virtual void input();

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		Fields::Ids currentController; 
};