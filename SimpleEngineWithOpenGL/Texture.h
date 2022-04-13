#pragma once
#include <string>
#include "RendererSDL.h"
#include "RendererOGL.h"

using std::string;

class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	//bool loadSDL(RendererSDL& rendererP, const string& filenamepP);
	bool loadOGL(RendererOGL& rendererP, const string& filenamepP);

	inline SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void updateInfo(int& widthOut, int& heighOut);
	void setActive() const;

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

private:
	unsigned int textureID;
	string filename;
	int width;
	int height;
	SDL_Texture* SDLTexture = nullptr;

};

