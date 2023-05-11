#pragma once
#include "GLTexture.h"
#include "TextureCache.h"

class ResourceManager {
	//Atributos
	static TextureCache textureCache;

//Métodos
public:
	static GLTexture getTexture(string texturePath); 
};

