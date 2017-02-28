#pragma once

#include "SFML/Window/Keyboard.hpp"

#include <vector>

class KeyMapper
{
	public:
		enum Func // Functionality, for example left (might be used to move a cursor left, move a ship left, move left in a textbox)
		{
			left,
			right,
			up,
			down
		};

		static bool checkFunc(Func f); // Checks if the key associated with a funcionality is down (true if down, false if up)

	private:
		static std::vector<sf::Keyboard::Key> KEY_FUNC_MAP; // Maps func to keys, added layer of mapping on order to allow keys to be switched, indexes are Funcs, keys are values
};

/*
HOW INPUT WORKS

The KeyMapper maps hardware to func
	Eg. W, A, S, and D map to Up, Left, Down, Right

The Player holds a list of switchable Controllers, if the current switchable Controller cedes control, it undergoes the process of selecting a new switchable Controller 
	Eg. player clicks outside ship while ShipController is current, ShipController broadcasts to cede control back to Player, next cycle player clicks the island, ShipController switches control to IslandController
The process for selecting a new switchable Controller is done by priority
	Eg. player clicks on the quit button which a ship happens to be under, Player gives control to MainMenuController not ShipController

A Controller (Eg. ShipController) can handle input commands and cede control upwards
*/