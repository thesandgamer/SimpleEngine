#include "Game.h"
#include "Timer.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include "BackgroundSpriteComponent.h"
#include "MeshComponent.h"

#include "Cube.h"
#include "Sphere.h"
#include "Plane.h"



bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	return isWindowInit && isRendererInit; // Return bool && bool && bool ...to detect error
}

void Game::load()
{
	//Load Shader _______________________________________________
	Assets::loadShader("Res\\Shaders\\Sprite.vert", "Res\\Shaders\\Sprite.frag", "", "", "", "Sprite");
	Assets::loadShader("Res\\Shaders\\BasicMesh.vert", "Res\\Shaders\\BasicMesh.frag", "", "", "", "BasicMesh");
	Assets::loadShader("Res\\Shaders\\Phong.vert", "Res\\Shaders\\Phong.frag", "", "", "", "Phong");
	//_____________________________________________________________________
	

	//Load Textures _______________________________________________
	Assets::loadTexture(renderer, "Res\\Textures\\Default.png", "Default");
	Assets::loadTexture(renderer, "Res\\Textures\\Cube.png", "Cube");
	Assets::loadTexture(renderer, "Res\\Textures\\HealthBar.png", "HealthBar");
	Assets::loadTexture(renderer, "Res\\Textures\\Plane.png", "Plane");
	Assets::loadTexture(renderer, "Res\\Textures\\Radar.png", "Radar");
	Assets::loadTexture(renderer, "Res\\Textures\\Sphere.png", "Sphere");
	//_____________________________________________________________________

	

	//Load Meshes______________________________________________________
	Assets::loadMesh("Res\\Meshes\\Cube.gpmesh", "Mesh_Cube");
	Assets::loadMesh("Res\\Meshes\\Plane.gpmesh", "Mesh_Plane");
	Assets::loadMesh("Res\\Meshes\\Sphere.gpmesh", "Mesh_Sphere");
	//________________________________________________________________________________




	camera = new Camera();
	
	//Créer le cube
	Cube* a = new Cube();
	a->setPosition(Vector3(100.0f, 105.0f, 0.0f)); //Set sa position
	a->setScale(90.0f); //Set sa scale
	Quaternion q(Vector3::unitY, -Maths::piOver2); 
	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::pi + Maths::pi / 4.0f));
	a->setRotation(q); //Set sa rotation
	/*
	MeshComponent* mc = new MeshComponent(a); //Set son meshcomponent
	mc->setMesh(Assets::getMesh("Mesh_Cube"));//Set son mesh à son mesh component*/

	//Créer la sphère
	Sphere* b = new Sphere();
	b->setPosition(Vector3(200.0f, -75.0f, 0.0f));
	b->setScale(3.0f);
	/*
	MeshComponent* mcb = new MeshComponent(b);
	mcb->setMesh(Assets::getMesh("Mesh_Sphere"));*/

	//Sol et murs
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Plane* p = new Plane();
			p->setPosition(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}
	//Murs
	q = Quaternion(Vector3::unitX, Maths::piOver2);
	for (int i = 0; i < 10; i++)
	{
		Plane* p = new Plane();
		p->setPosition(Vector3(start + i * size, start - size, 0.0f));
		p->setRotation(q);

		p = new Plane();
		p->setPosition(Vector3(start + i * size, -start + size, 0.0f));
		p->setRotation(q);
	}
	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::piOver2));
	for (int i = 0; i < 10; i++)
	{
		Plane* p = new Plane();
		p->setPosition(Vector3(start - size, start + i* size, 0.0f));
		p->setRotation(q);

		p = new Plane();
		p->setPosition(Vector3(-start + size, start + i * size, 0.0f));
		p->setRotation(q);
	}

	//Setup lights
	renderer.setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = renderer.getDirectionalLight();
	dir.direction = Vector3(0.0f, 0.707f, 0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	//Ui Elements		
	Actor* ui = new Actor();
	ui->setPosition(Vector3(-350.0f, -350.0f, 0.0f));
	SpriteComponent* sc = new SpriteComponent(ui, Assets::getTexture("HealthBar"));

	ui = new Actor();
	ui->setPosition(Vector3(375.0f, -275.0f, 0.0f));
	ui->setScale(0.75f);
	sc = new SpriteComponent(ui, Assets::getTexture("Radar"));
	
}
	


//Check des InputsS
void Game::processInput()
{
	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	// Keyboard state
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	// Escape: quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}

	//Check tous les actors et process leurs inputs
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->processInput(keyboardState);
	}
	isUpdatingActors = false;


}

void Game::update(float dt)
{
	//Update les acteurs
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	//Fait que les actors en attente ne le soit plus
	for (auto pendingActor : pendingActors)
	{
		pendingActor->computeWorldTransform();
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();


	//Ajoute les acteur mort dans un liste d'acteur morts
	vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);//Place les acteurs mort à la fin de la liste
		}
	}
	//Delete tous les acteurs morts
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}


}

//Dessin 
void Game::render()
{
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}

//Loop du jeu
void Game::loop()
{
	Timer timer;//Créer l'objet de class timer
	float dt = 0;//Setup un delta time à 0
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;//Calcul de delta time du timer
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

//Quand on va unload le jeu
void Game::unload()
{
	//Delete actors tant qu'il en reste stoqué dans le game
	while (!actors.empty())
	{
		delete actors.back();
	}
	//Ressources
	Assets::clear();

}

//Quand on ferme le jeu
void Game::close()
{
	renderer.close();
	window.close();
	SDL_Quit();
}


//Ajoute un acteur au jeu
void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)//Si on est en train d'updater les acteurs on ajoute l'acteur à la liste des acteurs en attente
	{
		pendingActors.emplace_back(actor);
	}
	else//Sinon on l'ajoute à la liste des acteurs
	{
		actors.emplace_back(actor);
	}
}

//Enlève un acteur
void Game::removeActor(Actor* actor)
{
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))//Si l'acteur demandé est trouvé dasn la liste des acteurs en attente
	{
		std::iter_swap(iter, end(pendingActors) - 1);//Remplace l'objet actuel par le dernier
		pendingActors.pop_back(); //on l'enlève de la liste le dernier objet
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))//Si l'acteur demandé est trouvé dans la liste des acteurs
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}


//______Game Specific__________________________
