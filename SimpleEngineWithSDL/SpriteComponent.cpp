#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

//Definition du component du sprite
SpriteComponent::SpriteComponent(Actor* ownerP,Texture& textureP,int drawOrderP):
	Component(ownerP), //Définit les éléments venant du parent componenent
	texture(textureP), //La texture à utiliser
	drawOrder(drawOrderP), //Quand la dessiner
	texWidth(textureP.getWidth()),
	texHeight(textureP.getHeight())
{
	owner.getGame().getRenderer().addSprite(this); //Add le sprite à renderer du game(sa liste de sprite à draw)
}

SpriteComponent::~SpriteComponent()
{
	owner.getGame().getRenderer().removeSprite(this);
}

void SpriteComponent::setTexture(const Texture& textureP)
{
	texture = textureP;
	texture.updateInfo(texWidth, texHeight);
}

void SpriteComponent::draw(Renderer& renderer)
{
	Vector2 origin{ texWidth / 2.f,texHeight / 2.f };
	renderer.drawSprite(owner, texture, Rectangle::nullRect, origin, Renderer::Flip::None); //Draw le sprite
}
