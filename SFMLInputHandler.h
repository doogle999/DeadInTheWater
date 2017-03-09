#pragma once

#include "SFML\Window.hpp"

#include <array>

#include "Field.h"
#include "World.h"
#include "Game.h"
#include "PVector.h"

class SFMLInputHandler : public Field
{
	public:
		enum Func // Functionality, mouse and keyboard states are converted to these
		{
			left,
			right,
			up,
			down,
			META_FUNC_COUNT
		};

		enum Eve // Game events, input events (key presses/releases, mouse movements, mouse presses/releases), not events like close or resize
		{
			select
		};

		SFMLInputHandler();

		~SFMLInputHandler();

		virtual void input();

		bool checkFunc(Func f);
		int popEve();

		PVector<int, 2> getMousePos();
		PVector<int, 2> getMousePosRelWin();

		std::vector<Attribute::Ids> getNecessaryProperties();

	private:
		void handleSFMLInput();

		PVector<int, 2> mousePos;
		PVector<int, 2> mousePosRelWin;

		std::array<bool, Func::META_FUNC_COUNT> funcs; // What is currently active
		std::vector<Eve> eves; // What has been triggered this input cycle

		std::array<std::vector<Func>, sf::Keyboard::KeyCount> keyFuncMap; // Key states bound to funcionality
		std::array<std::vector<Func>, sf::Mouse::ButtonCount> mouseFuncMap; // Mouse button states bound to functionality

		std::array<std::vector<Eve>, sf::Keyboard::KeyCount> keyPressedEveMap; // Key events bound to game events
		std::array<std::vector<Eve>, sf::Keyboard::KeyCount> keyReleasedEveMap; // Key events bound to game events
		std::array<std::vector<Eve>, sf::Mouse::ButtonCount> mousePressedEveMap; // Mouse events bound to game events
		std::array<std::vector<Eve>, sf::Mouse::ButtonCount> mouseReleasedEveMap; // Mouse events bound to game events

		// Key states - recorded at the start of every input step
		// Key events
		// Mouse states - recorded at the start of every input step
		// Mouse events

		// Key states and Mouse states map (used by asking if the functionality has been activated)
		// Key events and Mouse events map (used by processing the events)
};