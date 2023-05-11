#pragma once
#include "GLTexture.h"
#include <map>
#include <string>

using namespace std;

class TextureCache {
	//Atributos
	map<string, GLTexture> textureMap;

//M�todos
public:
	//Constructor
	TextureCache();

	//Destructor
	~TextureCache();

	//Funci�n: Obtener la textura en base a su direcci�n
	GLTexture getTexture(string texturePath);
};

