#pragma once
#include "Rectangle.h"
#include "IRenderer.h"
#include <SDL.h>
#include "Window.h"
#include <SDL_image.h>
#include "Vector2.h"
#include "Actor.h"

class RendererSDL : public IRenderer
{
public:

	RendererSDL();
	~RendererSDL();
	RendererSDL(const RendererSDL&) = delete;
	RendererSDL& operator=(const RendererSDL&) = delete;

	bool initialize(Window& window);

	void beginDraw();
	void draw();
	void endDraw();
	         
	IRenderer::Type type(){ return Type::SDL; }
	

	void drawRect(Rectangle& rect);
	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void drawSprite(const class Actor&, const class Texture&, struct Rectangle scrRect, Vector2 origin, Flip flip) const;

	inline SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }

	void close();


private:
	void drawSprites();

	std::vector<class SpriteComponent*> sprites;

	SDL_Renderer* SDLRenderer = nullptr;

};

