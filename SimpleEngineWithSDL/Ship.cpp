#include "Ship.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "InputComponent.h"
#include "Maths.h"
#include "Laser.h"

Ship::Ship(): Actor(), laserCooldown(0.0f)
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Ship"));
	InputComponent* ic = new InputComponent(this);
	ic->setMaxForwardSpeed(300.0f);
	ic->setMaxAngularSpeed(Maths::twoPi);
}

//Process les inputs
void Ship::actorInput(const Uint8* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && laserCooldown <= 0.0f) //Si on appui sur barre espace et que le cooldown est à 0
	{
		Laser* laser = new Laser();//Créer un lase
		laser->setPosition(getPosition());//On le place à la position du vaisseau
		laser->setRotation(getRotation());
		laserCooldown = 0.2f;


	}
}

void Ship::updateActor(float dt)
{
	laserCooldown -= dt;
}
