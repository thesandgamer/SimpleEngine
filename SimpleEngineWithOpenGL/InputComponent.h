#pragma once
#include "MoveComponent.h"
#include <SDL_stdinc.h>
#include <SDL_scancode.h>

class InputComponent: public MoveComponent
{
public:
	InputComponent(Actor* ownerP);
	InputComponent() = delete;
	InputComponent(const InputComponent&) = delete;
	InputComponent& operator=(const InputComponent&) = delete;

	void processInput(const struct InputState& inputState);

	void setMaxForwardSpeed(float maxForwardSpeedP);
	void setMaxAngularSpeed(float maxAngularSpeedP);

	void setForwardKey(SDL_Scancode key);
	void setBackKey(SDL_Scancode key);
	void setClockWiseKey(SDL_Scancode key);
	void setCounterClockWiseKey(SDL_Scancode key);

private:
	float maxForwardSpeed;
	float maxAngularSpeed;

	SDL_Scancode forwardKey;
	SDL_Scancode backKey;
	SDL_Scancode clockWiseKey;
	SDL_Scancode counterClockWiseKey;

};

