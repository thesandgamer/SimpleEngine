#include "Actor.h"
#include <algorithm>
#include "Game.h"
#include "Component.h"
#include "Maths.h"


Actor::Actor() :
	state(Actor::ActorState::Active), //Quand l'acteur est créer il est actif
	position(Vector3::zero),
	scale(1.0f),
	rotation(Quaternion::identity),
	mustRecomputeWorldTransform(true),
	game(Game::instance())
{
	game.addActor(this);
}

Actor::~Actor()
{
	game.removeActor(this);//Remove l'actor de la liste des acteurs du game
	while (!components.empty())
	{
		delete components.back();
	}
}

//Calcul le forward vector 
const Vector3 Actor::getForward() const
{
	return Vector3::transform(Vector3::unitX, rotation);
}

void Actor::setPosition(Vector3 positionP)
{
	position = positionP;
	mustRecomputeWorldTransform = true;
}

void Actor::setScale(float scaleP)
{
	scale = scaleP;
	mustRecomputeWorldTransform = true;

}

void Actor::setRotation(Quaternion rotationP)
{
	rotation = rotationP;
	mustRecomputeWorldTransform = true;
}

void Actor::SetState(ActorState newState)
{
	state = newState;
}

void Actor::update(float dt)
{
	if (state == Actor::ActorState::Active)
	{
		updateComponents(dt);//Update ses components
		updateActor(dt);
	}
}

//On va récupérer tous les components de l'acteur pour les update les uns à la suite des autres
void Actor::updateComponents(float dt)
{
	for (auto component : components)
	{
		component->update(dt);
	}
}

void Actor::updateActor(float dt)
{

}


//Fonction pour ajouter un component à l'acteur
void Actor::addComponent(Component* component)
{
	int myOrder = component->getUpdateOrder();//Get l'ordre d'update du componenent
	auto iter = begin(components);
	for (; iter != end(components); iter++)//On va parcourir tous les componenets
	{
		if (myOrder < (*iter)->getUpdateOrder()) //si l'ordre du compoenent x est supérieur à celui du C à ajouter
		{
			break;
		}
	}
	//Insère le component dans l'ordre d'éxécution
	components.insert(iter, component);


}

void Actor::removeComponent(Component* component)
{
	auto iter = std::find(begin(components), end(components), component); //Cherche le componenent dans la liste
	if (iter != end(components))//Si on le trouve
	{
		components.erase(iter);//On l'erase
	}
}

//Processing input de l'acteur et de tous ses componenets
void Actor::processInput(const Uint8* keyState)
{
	if (state == Actor::ActorState::Active)//Si l'acteur est actif
	{
		for (auto component : components)//On va process les inputs de tous ses componenets
		{
			component->processInput(keyState);
		}
		actorInput(keyState);

	}
}

void Actor::actorInput(const Uint8* keystate)
{
}

void Actor::computeWorldTransform()
{
	if (mustRecomputeWorldTransform)
	{
		mustRecomputeWorldTransform = false;
		worldTransform = Matrix4::createScale(scale);
		worldTransform = Matrix4::createFromQuaternion(rotation);
		worldTransform = Matrix4::createTranslation(Vector3(position.x,position.y,0.0f));

		for (auto component : components)
		{
			component->onUpdateWorldTransfom();
		}
	}
}
