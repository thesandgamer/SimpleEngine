#include "KeyboardState.h"
#include "InputSystem.h"

bool KeyboardState::getKeyValue(SDL_Scancode key) const
{
	return currentState[key];
}

ButtonState KeyboardState::getKeyState(SDL_Scancode key) const
{
	if (previousState[key] == 0)
	{
		if (currentState[key] == 0) //Si la touche n'est préssé en ce moment ni n'a été pressé avant
		{
			return ButtonState::None;
		}
		else //Si la touche n'a été préssé avant mais la touche est pressé
		{
			return ButtonState::Pressed;

		}
	}
	else
	{
		if (currentState[key] == 0) //Si la touche été préssé avant et qu'elle ne l'est plus
		{
			return ButtonState::Released;
		}
		else //Si elle est toujours pressé
		{
			return ButtonState::Held;

		}
	}
}
