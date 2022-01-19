#include "Game.h"
#include "Timer.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include "BackgroundSpriteComponent.h"
#include "Astroid.h"
#include "Ship.h"

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);

	int windowWidth = window.getWidth();
	int windowHeight = window.getHeight();


	return isWindowInit && isRendererInit; // Return bool && bool && bool ...to detect error
}

void Game::load()
{
	//Load Textures_______________________________________________
	Assets::loadTexture(renderer, "Res\\Ship01.png", "ship01");
	Assets::loadTexture(renderer, "Res\\Ship02.png", "ship02");
	Assets::loadTexture(renderer, "Res\\Ship03.png", "ship03");
	Assets::loadTexture(renderer, "Res\\Ship04.png", "ship04");
	Assets::loadTexture(renderer, "Res\\Farback01.png", "FarBack01");
	Assets::loadTexture(renderer, "Res\\Farback02.png", "FarBack02");
	Assets::loadTexture(renderer, "Res\\Stars.png", "Stars");
	Assets::loadTexture(renderer, "Res\\Astroid.png", "Astroid");
	Assets::loadTexture(renderer, "Res\\Ship.png", "Ship");
	Assets::loadTexture(renderer, "Res\\Laser.png", "Laser");
	//_____________________________________________________________________

	//Single SPrite
	/*
	auto actor = new Actor();
	auto sprite = new SpriteComponent(actor, Assets::getTexture("ship01"));
	actor->setPosition(Vector2{ 100,100 });
	*/

	//Animated Sprite_________________________________
	vector<Texture*> animShipTextures{
		&Assets::getTexture("ship01"),
		&Assets::getTexture("ship02"),
		&Assets::getTexture("ship03"),
		&Assets::getTexture("ship04"),
	};
	//_________________________________________

	Actor* ship = new Actor(); //Créer un acteur
	AnimSpriteComponent* animatedSprite = new AnimSpriteComponent(ship, animShipTextures);
	ship->setPosition(Vector2(100, 300));

	//BackGround
	//Create the "far back" background
	vector<Texture*>bgTexsFar{
		&Assets::getTexture("FarBack01"),
		&Assets::getTexture("FarBack02"),
	};
	Actor* bgFar = new Actor();
	BackgroundSpriteComponent* bgSpritesFar = new BackgroundSpriteComponent(bgFar, bgTexsFar);
	bgSpritesFar->setScrollSpeed(-100.0f);

	//Create the closer background
	Actor* bgClose = new Actor();
	std::vector<Texture*>bgTexsClose{
		&Assets::getTexture("Stars"),
		&Assets::getTexture("Stars"),

	};
	BackgroundSpriteComponent* bgSpritesClose = new BackgroundSpriteComponent(bgFar, bgTexsFar);
	bgSpritesClose->setScrollSpeed(-200.0f);

	//Astéroides: On créer un certain nombre d'objet de classe Astéroide
	const int astroidNumber = 20;
	for (int i = 0; i < astroidNumber; i++)
	{
		new Astroid();
	}

	//Player Ship
	Ship* controlledShip = new Ship(); //Créer un objet de classe vaisseau
	controlledShip->setPosition(Vector2{ 100,300 });//Set sa position de départ


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

vector<Astroid*>& Game::getAstroids()
{
	return astroids;
}

void Game::addAstroid(Astroid* astroid)
{
	astroids.emplace_back(astroid);
}

void Game::removeAstroid(Astroid* astroid)
{
	auto iter = std::find(begin(astroids), end(astroids), astroid);
	if (iter != astroids.end())
	{
		astroids.erase(iter);
	}
}