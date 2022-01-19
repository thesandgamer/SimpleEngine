#include "Texture.h"
#include "Log.h"
#include <SDL_image.h>

Texture::Texture(): filename(""),width(0),height(0), SDLTexture(nullptr)
{
}

Texture::~Texture()
{
}

void Texture::unload()
{
	if (SDLTexture)
	{
		SDL_DestroyTexture(SDLTexture);
	}
}

//Fonction pour load la texture
bool Texture::load(Renderer& rendererP, const string& filenamepP)
{
	filename = filenamepP;
	//Load from file
	SDL_Surface* surf = IMG_Load(filename.c_str());//Load l'image en fonction de son nom
	if (!surf) //Si on à pas de texture
	{
		Log::error(LogCategory::Application, "Failed to load texture file " + filename);
		return false;
	}
	//Setup la taille de la texture
	width = surf->w;
	height = surf->h;

	//Create texture from surface
	SDLTexture = SDL_CreateTextureFromSurface(rendererP.toSDLRenderer(), surf);
	SDL_FreeSurface(surf);
	if (!SDLTexture)
	{
		Log::error(LogCategory::Render, "Failed to convert surface to texture for " + filename);
		return false;
	}
	Log::info("Loaded texture " + filename);

	return true;
}

void Texture::updateInfo(int& widthOut, int& heighOut)
{
	widthOut = width;
	heighOut = height;
}
