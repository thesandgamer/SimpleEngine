#pragma once
#include <string>
#include "Renderer.h"
using std::string;

class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	bool load(Renderer& rendererP, const string& filenamepP);
	inline SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void updateInfo(int& widthOut, int& heighOut);

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

private:
	string filename;
	SDL_Texture* SDLTexture;
	int width;
	int height;
};

