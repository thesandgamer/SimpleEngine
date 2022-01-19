#pragma once
#include "Component.h"


class MoveComponent: public Component
{
public:
	MoveComponent(Actor* ownerP, int updateOrderP = 10);//Par défaut update avant les autres componenets
	MoveComponent() = delete; //Delete constructeur par défaut
	MoveComponent(const MoveComponent&) = delete; //
	MoveComponent& operator=(const MoveComponent&) = delete;//Delte operateur =

	float getForwardSpeed() const { return forwardSpeed; }
	float getAngularSpeed() const { return angularSpeed; }

	void setForwardSpeed(float forwardSpeedP);
	void setAngularSpeed(float angularSpeedP);

	void update(float dt) override;

private:
	float forwardSpeed; //Speed
	float angularSpeed; //Rotation

};
