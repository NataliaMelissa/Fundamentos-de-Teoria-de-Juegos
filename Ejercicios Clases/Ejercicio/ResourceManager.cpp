#include "ResourceManager.h"

TextureCache ResourceManager::textureCache;

//Método: Obtener la textura en base a su TexturePath/dirección
GLTexture ResourceManager::getTexture(string texturePath) {
	return textureCache.getTexture(texturePath);
}