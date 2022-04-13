#include "InputSystem.h"
#include <SDL_keyboard.h>
#include <cstring>

InputSystem::InputSystem(): inputState(), isCursorDisplayed(true)
{
}

bool InputSystem::initialize()
{
	//Clavier
	inputState.keyboard.currentState = SDL_GetKeyboardState(nullptr); // On va dire à l'inputState que l'état du clavier c'est celui de clavier(physique)
	memset(inputState.keyboard.previousState, 0, SDL_NUM_SCANCODES); //Set à vide l'état précédant du clacier de l'inputState

	//Souris
	inputState.mouse.currentButtons = 0;
	inputState.mouse.previousButtons = 0;

	return true;
}

void InputSystem::close()
{
}

bool InputSystem::processEvent(SDL_Event& event)
{
	bool isRunning = true;
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_MOUSEWHEEL:
		inputState.mouse.scrollWheel = Vector2(static_cast<float>(event.wheel.x), static_cast<float>(event.wheel.y));
		break;

	default:
		break;
	}
	return isRunning;
}

void InputSystem::preUpdate()
{
	//Copie l'état actuel dans l'état précédant
	memcpy(inputState.keyboard.previousState, inputState.keyboard.currentState, SDL_NUM_SCANCODES);

	//Souris
	inputState.mouse.isRelativeMode = false;
	inputState.mouse.scrollWheel = Vector2::zero;

}

void InputSystem::update()
{
	//Souris
	int x = 0;
	int y = 0;
	if (inputState.mouse.isRelativeMode)
	{
		inputState.mouse.currentButtons = SDL_GetRelativeMouseState(&x, &y);

	}
	else
	{
		inputState.mouse.currentButtons = SDL_GetMouseState(&x, &y);
	}
	inputState.mouse.position.x = static_cast<float>(x);
	inputState.mouse.position.y = static_cast<float>(y);
}

void InputSystem::setMouseCursor(bool isCursorDisplayedP)
{
	isCursorDisplayed = isCursorDisplayedP;
	if (isCursorDisplayedP)
	{
		SDL_ShowCursor(SDL_TRUE);
	}
	else
	{
		SDL_ShowCursor(SDL_FALSE);
	}
}

void InputSystem::setMouseRelativeMode(bool isMouseRelativeOnP)
{
	SDL_bool set = isMouseRelativeOnP ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);
	inputState.mouse.isRelativeMode = isMouseRelativeOnP;
}
