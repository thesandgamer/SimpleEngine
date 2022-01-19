#include "InputComponent.h"
#include <SDL_scancode.h>
#include "Log.h"

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

void InputComponent::processInput(const Uint8* keyState)
{
	float forwardSpeed = 0.0f;
	if (keyState[forwardKey])
	{
		forwardSpeed += maxForwardSpeed;
	}
	if (keyState[backKey])
	{
		forwardSpeed -= maxForwardSpeed;
	}
	setForwardSpeed(forwardSpeed);

	float angularSpeed = 0.0f;
	if (keyState[clockWiseKey])
	{
		angularSpeed -= maxAngularSpeed;
	}
	if (keyState[counterClockWiseKey])
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

void InputComponent::setForwardKey(int key)
{
	forwardKey = key;
}

void InputComponent::setBackKey(int key)
{
	backKey = key;
}

void InputComponent::setClockWiseKey(int key)
{
	clockWiseKey = key;
}

void InputComponent::setCounterClockWiseKey(int key)
{
	counterClockWiseKey = key;
}
