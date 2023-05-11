#pragma once
#include "GLTexture.h"
#include <map>
#include <string>

using namespace std;

class TextureCache {
	//Atributos
	map<string, GLTexture> textureMap;

//Métodos
public:
	//Constructor
	TextureCache();

	//Destructor
	~TextureCache();

	//Función: Obtener la textura en base a su dirección
	GLTexture getTexture(string texturePath);
};

