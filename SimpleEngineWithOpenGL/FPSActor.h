#pragma once
#include "Actor.h"
#include "Vector3.h"

class FPSActor: public Actor
{
public:
	FPSActor();

	void updateActor(float dt) override;
	void actorInput(const struct InputState& inputState) override;

	void setVisible(bool isVisible);

private:
	class MoveComponent* moveComponent;
	class MeshComponent* meshComponent;
	class FPSCameraComponent* cameraComponent;
	class Actor* FPSModel;

		

};

const Vector3 MODEL_OFFSET = Vector3(10.0f, 10.0f, -10.0f);

