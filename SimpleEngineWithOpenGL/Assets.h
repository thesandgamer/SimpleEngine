#pragma once
#include <map>
#include <string>
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"

using std::map;
using std::string;


class Assets
{
public:
	static map<std::string, Texture> textures;
	static map<std::string, Shader> shaders;
	static map<std::string, Mesh> meshes;

	//Loads et génère a shader program form file loadinbg vertex, fragment(and tesselation cobntrol, evaluation, geometry...
	static Shader loadShader(const std::string& vShaderFIle, const std::string& fShaderFile,
		const std::string& tcShaderFile, const std::string& teShaderFile,
		const std::string& gShaderFile, const std::string& name);

	//Retrives a stored shader
	static Shader& getShader(const std::string& name);


	//Loads a texture from a file
	static Texture loadTexture(IRenderer& renderer, const string& filename, const string& name);

	//Retrieves a stored texture
	static Texture& getTexture(const std::string& name);

	//Properly de-allocates all loaded resources
	static void clear();

	//Load mesh from file
	static Mesh loadMesh(const string& filename, const string& name);

	//Retrieves a stored mesh
	static Mesh& getMesh(const std::string& name);

private:
	Assets(){}

	//Loads a single texture from file
	static Texture loadTextureFromFile(IRenderer& renderer, const string& filename);

	//Load and generate a shader from file
	static Shader loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderFile,
		const std::string& tcShaderFile = "", const std::string& teShaderFile = "",
		const std::string& gShaderFile = "");

	static Mesh loadMeshFromFile(const string& filename);

};

