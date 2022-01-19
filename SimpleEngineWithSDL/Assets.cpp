#include "Assets.h"
#include "Log.h"
#include <sstream>

//Ensemble de fonctions pour les textures

map<string, Texture> Assets::textures; //Map pour stoquer toutes les textures avec comme clé un nom


//Fonction pour lead un texture
Texture Assets::loadTexture(Renderer& renderer, const string& filename, const string& name)
{
	textures[name] = loadTextureFromFile(renderer, filename.c_str());
	return textures[name];
}

//Fonction pour obtenir une texture en fonction de son nom
Texture& Assets::getTexture(const string& name)
{
	if (textures.find(name) == end(textures))//Si on trouve pas la texture
	{
		std::ostringstream loadError;
		loadError << "Texture " << name << " does not exist in assets manager";
		Log::error(LogCategory::Application, loadError.str());
	}
	return textures[name];//Sinon on retourne la texture la la map avec ce nom
}

//Clear toutes les texture stoqués
void Assets::clear()
{
	//Delete all textures
	for (auto iter : textures)
	{
		iter.second.unload();
	}
	textures.clear();
}

//Fonction pour Load une texture dans le renderer 
Texture Assets::loadTextureFromFile(Renderer& renderer, const string& filename)
{
	Texture texture;
	texture.load(renderer, filename);
	return texture;
}
