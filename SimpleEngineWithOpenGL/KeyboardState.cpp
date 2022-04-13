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
		if (currentState[key] == 0) //Si la touche n'est pr�ss� en ce moment ni n'a �t� press� avant
		{
			return ButtonState::None;
		}
		else //Si la touche n'a �t� pr�ss� avant mais la touche est press�
		{
			return ButtonState::Pressed;

		}
	}
	else
	{
		if (currentState[key] == 0) //Si la touche �t� pr�ss� avant et qu'elle ne l'est plus
		{
			return ButtonState::Released;
		}
		else //Si elle est toujours press�
		{
			return ButtonState::Held;

		}
	}
}
