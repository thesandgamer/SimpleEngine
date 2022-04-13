#pragma once
class Actor;
#include <SDL_stdinc.h>

class Component
{
public:
	Component(Actor* ownerP, int updateOrderP = 100);
	Component() = delete;
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	int getUpdateOrder() const { return updateOrder; }

	virtual void update(float dt);

	virtual void processInput(const struct InputState& inputState);

	virtual void onUpdateWorldTransfom() {}

protected:
	Actor& owner;
	int updateOrder;
};

