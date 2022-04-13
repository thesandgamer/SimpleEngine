#include "Texture.h"
#include "Log.h"
#include <SDL_image.h>
#include <sstream>

Texture::Texture():textureID(0), filename(""),width(0),height(0), SDLTexture(nullptr)
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
	else
	{
		glDeleteTextures(1, &textureID);
	}
}

/*
//Fonction pour load la texture
bool Texture::loadSDL(RendererSDL& rendererP, const string& filenamepP)
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
}*/


bool Texture::loadOGL(RendererOGL& rendererP, const string& filenamepP)
{
	filename = filenamepP;
	//Load from file
	SDL_Surface* surf = IMG_Load(filename.c_str()); //Load l'image/la surface avec le nom
	if (!surf)//Si elle n'exite pas
	{
		Log::error(LogCategory::Application, "Faiuled to load texture file " + filename);
		return false;
	}
	//Definit la taille de la texture
	width = surf->w;
	height = surf->h;
	//Va définir le format de la texture(si c'est juste RGB ou RGBA)
	int format = 0;
	if (surf->format->format == SDL_PIXELFORMAT_RGB24)
	{
		format = GL_RGB;
	}
	else if (surf->format->format == SDL_PIXELFORMAT_RGBA32)
	{
		format = GL_RGBA;
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, surf->pixels);
	SDL_FreeSurface(surf);

	Log::info("Loaded texture " + filename);
	//Enable bilenear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void Texture::updateInfo(int& widthOut, int& heighOut)
{
	widthOut = width;
	heighOut = height;
}

void Texture::setActive() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}
