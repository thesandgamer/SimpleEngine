#include "FPSActor.h"

#include "MoveComponent.h"
#include "Game.h"
#include "FPSCameraComponent.h"
#include "MeshComponent.h"
#include "Assets.h"

FPSActor::FPSActor() : Actor(), moveComponent{ nullptr }, meshComponent{ nullptr }, cameraComponent{ nullptr }
{
	moveComponent = new MoveComponent(this); //On lui rajoute un déplacement
	cameraComponent = new FPSCameraComponent(this); // Et une camera

	//Là on va setup le modèle 3d pour notre acteur, on le fait dans un acteur à part pour pouvoir set sa taille et son offset
	FPSModel = new Actor(); //On créer donc un acteur
	FPSModel->setScale(0.75f); //On le réduit de taille

	meshComponent = new MeshComponent(FPSModel); //On créer un mesh component qu'on rajoute dans l'acteur pour le modèle 3d
	meshComponent->setMesh(Assets::getMesh("Mesh_Rifle"));//Et on lui set le mesh de flingue
}

void FPSActor::updateActor(float dt)
{
	Actor::updateActor(dt);//On update l'acteur

	//Update la position et rotation du modèle 
	Vector3 modelPosition = getPosition();
	modelPosition += getForward() * MODEL_OFFSET.x; //On décale le modèle juste sur l'axe x(c'est à ça que sert le getForward()* ) d'un offset, tout ça par rapport à la position de l'acteur 
	modelPosition += getRight() * MODEL_OFFSET.y;	//Pareil pour la profondeur: axe y
	modelPosition += getUp() * MODEL_OFFSET.z;	//Et on change juste la hauteur: axe z
	FPSModel->setPosition(modelPosition); //Et on le replace
	Quaternion q = getRotation(); //On récupère la rotation de l'acteur
	q = Quaternion::concatenate(q, Quaternion(getRight(), cameraComponent->getPitch())); //comme la rotation de l'acteur n'est qu'en horizontal, on va lui rajouter la rotation (pitch) de la camera
	FPSModel->setRotation(q); //On on applique sa rotation	
}

void FPSActor::actorInput(const InputState& inputState)
{
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;
	// wasd movement
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_W))
	{
		forwardSpeed += 400.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_S))
	{
		forwardSpeed -= 400.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_A))
	{
		strafeSpeed -= 400.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_D))
	{
		strafeSpeed += 400.0f;
	}
	moveComponent->setForwardSpeed(forwardSpeed);
	moveComponent->setStrafeSpeed(strafeSpeed);

	//----------Mouse mouvement
	Vector2 mousePosition = inputState.mouse.getPosition();
	float x = mousePosition.x;
	float y = mousePosition.y;

	const int maxMouseSpeed = 300; //Sensibilité: plus c'est petit plus la camera tournera vite

	//Tourne l'acteur en yaw en fonction de la souris
	const float maxAngularSpeed = Maths::pi * 8;
	float angularSpeed = 0.0f;
	if (x != 0)
	{
		angularSpeed = x / maxMouseSpeed;
		angularSpeed *= maxAngularSpeed;
	}
	moveComponent->setAngularSpeed(angularSpeed);

	//Tourne la camera en pitch en fonction de la souris
	const float maxPitchSpeed = Maths::pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		pitchSpeed = y / maxMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	cameraComponent->setPitchSpeed(pitchSpeed);


}

void FPSActor::setVisible(bool isVisible)
{
	meshComponent->setVisible(isVisible);
}
