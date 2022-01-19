#include "RendererSDL.h"
#include "Log.h"
#include "Texture.h"
#include "Maths.h"
#include "SpriteComponent.h"

RendererSDL::RendererSDL() : SDLRenderer(nullptr)
{
}

RendererSDL::~RendererSDL()
{
}

//
bool RendererSDL::initialize(Window& window)
{
	//Créer la fenètre
	SDLRenderer = SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!SDLRenderer)
	{
		Log::error(LogCategory::Video, "Failed to create renderer");
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		Log::error(LogCategory::Video, "Unable to initialize SDL_image");
	}
	return true;
}


void RendererSDL::beginDraw()
{
	SDL_SetRenderDrawColor(SDLRenderer, 120, 120, 255, 255); //Draw le background color
	SDL_RenderClear(SDLRenderer);
}

void RendererSDL::draw()
{
	drawSprites(); //Dessines tous les sprites 
}

void RendererSDL::endDraw()
{
	SDL_RenderPresent(SDLRenderer);
}


//Fonction pour dessiner un rectangle blanc
void RendererSDL::drawRect(Rectangle& rect)
{
	SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 255, 255);
	SDL_Rect SDLRect = rect.toSDLRect();
	SDL_RenderFillRect(SDLRenderer, &SDLRect);
}

//Fonction pour ajouter le sprites à la liste de sprites à dessiner
void RendererSDL::addSprite(SpriteComponent* sprite)
{
	//Insert the sprite at the right place in function of draw order
	int spriteDrawOrder = sprite->getDrawOrder();
	auto iter = begin(sprites);
	for (; iter != end(sprites); ++iter)
	{
		if (spriteDrawOrder < (*iter)->getDrawOrder()) break;
	}
	sprites.insert(iter, sprite);
}

void RendererSDL::removeSprite(SpriteComponent* sprite)
{
	auto iter = std::find(begin(sprites), end(sprites), sprite);
	sprites.erase(iter);
}

//Dessiner tous les sprites de la liste de sprites à dessiner
void RendererSDL::drawSprites()
{
	for (auto sprite : sprites)
	{
		sprite->draw(*this);
	}
}

//Fonction pour dessiner un sprite d'un actor
void RendererSDL::drawSprite(const Actor& actor, const Texture& tex, Rectangle scrRect, Vector3 origin, Flip flip) const
{
	//Où et comment dessiner le sprite en fonction de l'acteur qui le possède
	SDL_Rect dstRect;
	Vector3 position = actor.getPosition();
	Quaternion rotation = actor.getRotation();
	float scale = actor.getScale();

	//set les information de taille du sprite
	dstRect.w = static_cast<int>(tex.getWidth() * scale);
	dstRect.h = static_cast<int>(tex.getHeight() * scale);

	//set les informations de position du sprite
	dstRect.x = static_cast<int>(position.x - origin.x);
	dstRect.y = static_cast<int>(position.y - origin.y);

	//Créer le rectangle où dessiner le rpite
	SDL_Rect* scrSDL = nullptr;
	if (scrRect != Rectangle::nullRect)
	{
		scrSDL = new SDL_Rect{
			Maths::round(scrRect.x),
			Maths::round(scrRect.y),
			Maths::round(scrRect.width),
			Maths::round(scrRect.height)
		};
	}

	
	//Draw le sprite
	SDL_RenderCopyEx(
		SDLRenderer,
		tex.toSDLTexture(),
		scrSDL,
		&dstRect,
		-Maths::toDegrees(rotation),
		nullptr,
		SDL_FLIP_NONE
	);
	
	delete scrSDL;

}

void RendererSDL::close()
{
	SDL_DestroyRenderer(SDLRenderer);
}
