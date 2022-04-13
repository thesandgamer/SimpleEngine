#pragma once
#include <SDL_keyboard.h>

class KeyboardState
{
	friend class InputSystem;

public:
	bool getKeyValue(SDL_Scancode key) const; //Rentre une clé et on regarde si elle est préssé 
	enum class ButtonState getKeyState(SDL_Scancode key) const; //Rentre une clé et on regarde son état

private:
	const Uint8* currentState; //stoque la touche appuyé
	Uint8 previousState[SDL_NUM_SCANCODES];
};

