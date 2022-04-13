#pragma once
#include <SDL_keyboard.h>

class KeyboardState
{
	friend class InputSystem;

public:
	bool getKeyValue(SDL_Scancode key) const; //Rentre une cl� et on regarde si elle est pr�ss� 
	enum class ButtonState getKeyState(SDL_Scancode key) const; //Rentre une cl� et on regarde son �tat

private:
	const Uint8* currentState; //stoque la touche appuy�
	Uint8 previousState[SDL_NUM_SCANCODES];
};

