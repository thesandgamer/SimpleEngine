#include "Component.h"
#include "Actor.h"
#include "InputSystem.h"

Component::Component(Actor* ownerP, int updateOrderP) : owner(*ownerP)
{
	owner.addComponent(this);
}

Component::~Component()
{
	owner.removeComponent(this);
}

void Component::update(float dt)
{

}

void Component::processInput(const struct InputState& inputState)
{
}
