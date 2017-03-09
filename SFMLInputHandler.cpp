#include "SFMLInputHandler.h"

SFMLInputHandler::SFMLInputHandler() 
{
	std::fill(funcs.begin(), funcs.end(), false);

	keyFuncMap[sf::Keyboard::Key::A] = { Func::left };
	keyFuncMap[sf::Keyboard::Key::D] = { Func::right };
	keyFuncMap[sf::Keyboard::Key::S] = { Func::down };
	keyFuncMap[sf::Keyboard::Key::W] = { Func::up };

	mousePressedEveMap[sf::Mouse::Button::Left] = { Eve::select };
}

SFMLInputHandler::~SFMLInputHandler() {}

void SFMLInputHandler::input()
{
	handleSFMLInput();
}

bool SFMLInputHandler::checkFunc(Func f)
{
	return funcs[f];
}
int SFMLInputHandler::popEve()
{
	if(eves.size() > 0)
	{
		int returnVal = eves.back();
		eves.pop_back();
		return returnVal;
	}

	return -1;
}

PVector<int, 2> SFMLInputHandler::getMousePos()
{
	return mousePos;
}
PVector<int, 2> SFMLInputHandler::getMousePosRelWin()
{
	return mousePosRelWin;
}

std::vector<Attribute::Ids> SFMLInputHandler::getNecessaryProperties()
{
	return { };
}

void SFMLInputHandler::handleSFMLInput()
{
	mousePos = sf::Mouse::getPosition();
	mousePosRelWin = sf::Mouse::getPosition(*Game::window);

	eves.clear();

	sf::Event event;

	while(Game::window->pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::KeyPressed:
			{
				eves.insert(eves.end(), keyPressedEveMap[event.key.code].begin(), keyPressedEveMap[event.key.code].end());

				for(unsigned int i = 0; i < keyFuncMap[event.key.code].size(); i++)
				{
					funcs[keyFuncMap[event.key.code][i]] = true;
				}
				break;
			}
			case sf::Event::KeyReleased:
			{
				eves.insert(eves.end(), keyReleasedEveMap[event.key.code].begin(), keyReleasedEveMap[event.key.code].end());
				for(unsigned int i = 0; i < keyFuncMap[event.key.code].size(); i++)
				{
					funcs[keyFuncMap[event.key.code][i]] = false;
				}
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				eves.insert(eves.end(), mousePressedEveMap[event.mouseButton.button].begin(), mousePressedEveMap[event.mouseButton.button].end());
				for(unsigned int i = 0; i < mouseFuncMap[event.mouseButton.button].size(); i++)
				{
					funcs[mouseFuncMap[event.mouseButton.button][i]] = true;
				}
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				eves.insert(eves.end(), mouseReleasedEveMap[event.mouseButton.button].begin(), mouseReleasedEveMap[event.mouseButton.button].end());
				for(unsigned int i = 0; i < mouseFuncMap[event.mouseButton.button].size(); i++)
				{
					funcs[mouseFuncMap[event.mouseButton.button][i]] = false;
				}
				break;
			}
			case sf::Event::Closed:
			{
				w->scheduleToClose();
				break;
			}
			default:
			{
				break;
			}
		}
	}
}
