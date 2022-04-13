#include "InputComponent.h"
#include <SDL_scancode.h>
#include "Log.h"
#include "InputSystem.h"

InputComponent::InputComponent(Actor* ownerP) :
	MoveComponent(ownerP),
	maxForwardSpeed(100.0f), 
	maxAngularSpeed(1.0f),
	forwardKey(SDL_SCANCODE_W),
	backKey(SDL_SCANCODE_S),
	clockWiseKey(SDL_SCANCODE_D),
	counterClockWiseKey(SDL_SCANCODE_A)
{
}

void InputComponent::processInput(const struct InputState& inputState)
{
	float forwardSpeed = 0.0f;
	if (inputState.keyboard.getKeyState(forwardKey) == ButtonState::Held)
	{
		forwardSpeed += maxForwardSpeed;
	}
	if (inputState.keyboard.getKeyState(backKey) == ButtonState::Held)
	{
		forwardSpeed -= maxForwardSpeed;
	}
	setForwardSpeed(forwardSpeed);

	float angularSpeed = 0.0f;
	if (inputState.keyboard.getKeyState(clockWiseKey) == ButtonState::Held)
	{
		angularSpeed -= maxAngularSpeed;
	}
	if (inputState.keyboard.getKeyState(counterClockWiseKey) == ButtonState::Held)
	{
		angularSpeed += maxAngularSpeed;
	}
	setAngularSpeed(angularSpeed);
}

void InputComponent::setMaxForwardSpeed(float maxForwardSpeedP)
{
	maxForwardSpeed = maxForwardSpeedP;
}

void InputComponent::setMaxAngularSpeed(float maxAngularSpeedP)
{
	maxAngularSpeed = maxAngularSpeedP;
}

void InputComponent::setForwardKey(SDL_Scancode key)
{
	forwardKey = key;
}

void InputComponent::setBackKey(SDL_Scancode key)
{
	backKey = key;
}

void InputComponent::setClockWiseKey(SDL_Scancode key)
{
	clockWiseKey = key;
}

void InputComponent::setCounterClockWiseKey(SDL_Scancode key)
{
	counterClockWiseKey = key;
}
