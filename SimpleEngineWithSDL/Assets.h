#pragma once
#include <map>
#include <string>
#include "Texture.h"
using std::map;
using std::string;


class Assets
{
public:
	static map<std::string, Texture> textures;

	//Loads a texture from a file
	static Texture loadTexture(Renderer& renderer, const string& filename, const string& name);

	//Retrieves a stored texture
	static Texture& getTexture(const string& name);

	//Properly de-allocates all loaded resources
	static void clear();

private:
	Assets(){}

	//Loads a single texture from file
	static Texture loadTextureFromFile(Renderer& renderer, const string& filename);

};

